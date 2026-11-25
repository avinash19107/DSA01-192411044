
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif

#include "crow.h"
#include <openssl/evp.h>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <cctype>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>

namespace fs = std::filesystem;

// ==========================================
// EVIDENCE AND EVENT STRUCTURES
// ==========================================

struct Evidence {
    std::string id;
    std::string name;
    std::string type;
    std::string created;
    std::string originalHash;
};

struct Event {
    uint64_t seq;
    std::string id;
    std::string name;
    std::string kind;
    std::string when;
    std::string hash;
};

// ==========================================
// GLOBAL STORAGE
// ==========================================

static const fs::path base = "storage";

static std::mutex mu;

static std::deque<Evidence> evidence;
static std::deque<Event> events;

static std::unordered_map<std::string, std::string> observed;

static std::atomic<bool> monitoring{true};
static std::atomic<bool> running{true};

static uint64_t nextSeq = 1;

// ==========================================
// FILE READING
// ==========================================

static std::string readFile(const fs::path& p) {
    std::ifstream f(p, std::ios::binary);

    if (!f)
        return {};

    return std::string(
        std::istreambuf_iterator<char>(f),
        std::istreambuf_iterator<char>()
    );
}

// ==========================================
// FILE WRITING
// ==========================================

static bool writeFile(
    const fs::path& p,
    const std::string& s
) {
    std::ofstream f(
        p,
        std::ios::binary | std::ios::trunc
    );

    if (!f)
        return false;

    f.write(
        s.data(),
        static_cast<std::streamsize>(s.size())
    );

    f.close();

    return bool(f);
}

// ==========================================
// SHA-256 HASH GENERATION
// ==========================================

static std::string hashFile(const fs::path& p) {

    std::ifstream f(p, std::ios::binary);

    if (!f)
        return {};

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();

    if (!ctx)
        return {};

    if (EVP_DigestInit_ex(
            ctx,
            EVP_sha256(),
            nullptr
        ) != 1) {

        EVP_MD_CTX_free(ctx);
        return {};
    }

    char buffer[32768];

    while (
        f.read(buffer, sizeof(buffer)) ||
        f.gcount() > 0
    ) {
        if (EVP_DigestUpdate(
                ctx,
                buffer,
                static_cast<size_t>(f.gcount())
            ) != 1) {

            EVP_MD_CTX_free(ctx);
            return {};
        }
    }

    if (f.bad() || !f.eof()) {
        EVP_MD_CTX_free(ctx);
        return {};
    }

    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int length = 0;

    if (EVP_DigestFinal_ex(
            ctx,
            digest,
            &length
        ) != 1) {

        EVP_MD_CTX_free(ctx);
        return {};
    }

    EVP_MD_CTX_free(ctx);

    std::ostringstream output;

    for (unsigned int i = 0; i < length; ++i) {
        output << std::hex
               << std::setw(2)
               << std::setfill('0')
               << unsigned(digest[i]);
    }

    return output.str();
}

// ==========================================
// STRING AND FILE TYPE FUNCTIONS
// ==========================================

static std::string lower(std::string s) {

    std::transform(
        s.begin(),
        s.end(),
        s.begin(),
        [](unsigned char c) {
            return char(std::tolower(c));
        }
    );

    return s;
}

static std::string ext(const std::string& s) {
    return lower(
        fs::path(s).extension().string()
    );
}

static std::string mime(const std::string& s) {

    auto e = ext(s);

    if (e == ".pdf")
        return "application/pdf";

    if (e == ".txt" ||
        e == ".md" ||
        e == ".log")
        return "text/plain; charset=utf-8";

    if (e == ".csv")
        return "text/csv; charset=utf-8";

    if (e == ".json")
        return "application/json";

    if (e == ".png")
        return "image/png";

    if (e == ".jpg" || e == ".jpeg")
        return "image/jpeg";

    if (e == ".gif")
        return "image/gif";

    return "application/octet-stream";
}

// ==========================================
// SAFE FILE NAME
// ==========================================

static std::string safeName(std::string s) {

    s = fs::path(s).filename().string();

    for (char& c : s) {

        unsigned char u =
            static_cast<unsigned char>(c);

        if (!std::isalnum(u) &&
            c != '.' &&
            c != '_' &&
            c != '-' &&
            c != ' ') {

            c = '_';
        }
    }

    if (s.empty() || s == "." || s == "..")
        s = "evidence.bin";

    return s.substr(0, 150);
}

// ==========================================
// TIMESTAMP GENERATION
// ==========================================

static std::string timestamp() {

    auto t = std::chrono::system_clock::to_time_t(
        std::chrono::system_clock::now()
    );

    std::tm tm{};

#ifdef _WIN32
    gmtime_s(&tm, &t);
#else
    gmtime_r(&t, &tm);
#endif

    std::ostringstream output;

    output << std::put_time(
        &tm,
        "%Y-%m-%d %H:%M:%S UTC"
    );

    return output.str();
}

// ==========================================
// EVIDENCE FILE PATHS
// ==========================================

static fs::path original(const Evidence& e) {

    return base /
           "originals" /
           (e.id + ".bin");
}

static fs::path monitored(const Evidence& e) {

    return base /
           "monitored" /
           (e.id + ".bin");
}

// ==========================================
// SAVE EVIDENCE METADATA
// ==========================================

static void saveIndex() {

    std::ofstream f(
        base / "metadata" / "index.txt",
        std::ios::trunc
    );

    for (const auto& e : evidence) {

        f << std::quoted(e.id) << ' '
          << std::quoted(e.name) << ' '
          << std::quoted(e.type) << ' '
          << std::quoted(e.created) << ' '
          << std::quoted(e.originalHash)
          << '\n';
    }
}

// ==========================================
// LOAD EVIDENCE METADATA
// ==========================================

static void loadIndex() {

    std::ifstream f(
        base / "metadata" / "index.txt"
    );

    Evidence e;

    while (
        f >> std::quoted(e.id)
          >> std::quoted(e.name)
          >> std::quoted(e.type)
          >> std::quoted(e.created)
          >> std::quoted(e.originalHash)
    ) {
        evidence.push_back(e);
    }
}

// ==========================================
// LOAD MONITORING EVENTS
// ==========================================

static void loadEvents() {

    std::ifstream f(
        base / "metadata" / "events.txt"
    );

    Event e;

    while (
        f >> e.seq
          >> std::quoted(e.id)
          >> std::quoted(e.name)
          >> std::quoted(e.kind)
          >> std::quoted(e.when)
          >> std::quoted(e.hash)
    ) {
        events.push_back(e);

        nextSeq = std::max(
            nextSeq,
            e.seq + 1
        );
    }
}

// ==========================================
// RECORD MONITORING EVENT
// ==========================================

static void addEvent(
    const Evidence& e,
    const std::string& kind,
    const std::string& hash
) {
    Event event{
        nextSeq++,
        e.id,
        e.name,
        kind,
        timestamp(),
        hash
    };

    events.push_back(event);

    std::ofstream f(
        base / "metadata" / "events.txt",
        std::ios::app
    );

    f << event.seq << ' '
      << std::quoted(event.id) << ' '
      << std::quoted(event.name) << ' '
      << std::quoted(event.kind) << ' '
      << std::quoted(event.when) << ' '
      << std::quoted(event.hash)
      << '\n';
}

// ==========================================
// SEARCH EVIDENCE
// ==========================================

static Evidence* lookup(const std::string& id) {

    for (auto& e : evidence) {

        if (e.id == id)
            return &e;
    }

    return nullptr;
}

// ==========================================
// FILE INTEGRITY STATUS
// ==========================================

static std::string state(
    const Evidence& e,
    const std::string& hash
) {
    if (hash.empty())
        return "missing";

    if (hash == e.originalHash)
        return "verified";

    return "tampered";
}

// ==========================================
// EVIDENCE SUMMARY
// ==========================================

static crow::json::wvalue summary(
    const Evidence& e
) {
    crow::json::wvalue v;

    auto hash = hashFile(monitored(e));

    v["id"] = e.id;
    v["name"] = e.name;
    v["type"] = e.type;
    v["created"] = e.created;
    v["original_hash"] = e.originalHash;
    v["current_hash"] = hash;
    v["status"] = state(e, hash);

    std::error_code ec;

    auto size = fs::file_size(
        original(e),
        ec
    );

    v["size"] = ec
        ? uint64_t(0)
        : uint64_t(size);

    return v;
}

// ==========================================
// JSON RESPONSES
// ==========================================

static crow::response json(
    crow::json::wvalue v,
    int status = 200
) {
    crow::response response(
        status,
        v.dump()
    );

    response.set_header(
        "Content-Type",
        "application/json; charset=utf-8"
    );

    response.set_header(
        "Cache-Control",
        "no-store"
    );

    return response;
}

static crow::response fail(
    const std::string& message,
    int status = 400
) {
    crow::json::wvalue v;

    v["error"] = message;

    return json(std::move(v), status);
}

// ==========================================
// FILE RESPONSE
// ==========================================

static crow::response fileResponse(
    const fs::path& p,
    const std::string& contentType,
    bool website = false
) {
    if (!fs::exists(p))
        return fail("File not found", 404);

    crow::response response(
        200,
        readFile(p)
    );

    response.set_header(
        "Content-Type",
        contentType
    );

    response.set_header(
        "X-Content-Type-Options",
        "nosniff"
    );

    response.set_header(
        "Cache-Control",
        "no-store"
    );

    if (website) {

        response.set_header(
            "Content-Security-Policy",
            "default-src 'self'; "
            "style-src 'self' 'unsafe-inline'; "
            "script-src 'self' 'unsafe-inline'; "
            "connect-src 'self'; "
            "img-src 'self' blob: data:; "
            "frame-src 'self' blob:; "
            "object-src 'none'"
        );

    } else {

        response.set_header(
            "Content-Security-Policy",
            "default-src 'none'; sandbox"
        );
    }

    return response;
}

// ==========================================
// TEXT NORMALIZATION
// ==========================================

static std::string normalize(
    const std::string& s
) {
    std::string output;

    bool space = false;

    for (unsigned char c : s) {

        if (std::isspace(c)) {

            if (!output.empty())
                space = true;

        } else {

            if (space) {
                output += ' ';
                space = false;
            }

            output += char(c);
        }
    }

    return output;
}

// ==========================================
// WORD EXTRACTION USING DEQUE
// ==========================================

static std::deque<std::string> words(
    const std::string& s
) {
    std::istringstream input(normalize(s));

    std::deque<std::string> result;

    std::string word;

    while (input >> word) {
        result.push_back(word);
    }

    return result;
}

// ==========================================
// JOIN WORDS
// ==========================================

static std::string join(
    const std::deque<std::string>& data,
    size_t start,
    size_t end
) {
    std::string result;

    for (size_t i = start; i < end; ++i) {

        if (!result.empty())
            result += ' ';

        result += data[i];
    }

    return result;
}

// ==========================================
// CREATE EMPTY JSON ARRAY
// ==========================================

static crow::json::wvalue emptyArray() {

    return crow::json::wvalue(
        crow::json::wvalue::list{}
    );
}

// ==========================================
// EXACT TEXT MODIFICATION ANALYSIS
// BOUNDED MYERS DIFFERENCE ALGORITHM
// ==========================================

static crow::json::wvalue diffText(
    const std::string& before,
    const std::string& after
) {
    auto a = words(before);
    auto b = words(after);

    crow::json::wvalue output;

    output["changes"] = emptyArray();

    size_t changeIndex = 0;

    size_t p = 0;

    while (
        p < a.size() &&
        p < b.size() &&
        a[p] == b[p]
    ) {
        ++p;
    }

    size_t ea = a.size();
    size_t eb = b.size();

    while (
        ea > p &&
        eb > p &&
        a[ea - 1] == b[eb - 1]
    ) {
        --ea;
        --eb;
    }

    if (ea == p && eb == p)
        return output;

    int N = int(ea - p);
    int M = int(eb - p);

    constexpr int LIMIT = 300;

    int maxD = std::min(N + M, LIMIT);
    int off = maxD + 2;

    std::deque<int> v(
        2 * off + 1,
        -1
    );

    v[off + 1] = 0;

    std::deque<std::deque<int>> trace;

    int solved = -1;

    // Find the shortest edit sequence.

    for (int d = 0; d <= maxD; ++d) {

        for (int k = -d; k <= d; k += 2) {

            int idx = off + k;

            int x =
                (
                    k == -d ||
                    (
                        k != d &&
                        v[idx - 1] < v[idx + 1]
                    )
                )
                ? v[idx + 1]
                : v[idx - 1] + 1;

            int y = x - k;

            while (
                x >= 0 &&
                y >= 0 &&
                x < N &&
                y < M &&
                a[p + x] == b[p + y]
            ) {
                ++x;
                ++y;
            }

            v[idx] = x;

            if (x >= N && y >= M) {

                solved = d;
                break;
            }
        }

        trace.push_back(v);

        if (solved >= 0)
            break;
    }

    // Handle extensive modifications.

    if (solved < 0) {

        crow::json::wvalue c;

        c["type"] =
            ea == p ? "added" :
            eb == p ? "removed" :
            "replaced";

        c["old_text"] = join(a, p, ea);
        c["new_text"] = join(b, p, eb);

        c["old_line"] = int(p + 1);
        c["new_line"] = int(p + 1);

        output["changes"][changeIndex++] =
            std::move(c);

        output["warning"] =
            "Extensive differences: displayed "
            "a combined changed region rather "
            "than individual edits.";

        return output;
    }

    // Store individual edit operations.

    struct Op {
        char kind;
        int ai;
        int bi;
    };

    std::deque<Op> operations;

    int x = N;
    int y = M;

    // Reconstruct the edit sequence.

    for (int d = solved; d > 0; --d) {

        const auto& previous = trace[d - 1];

        int k = x - y;

        int pk =
            (
                k == -d ||
                (
                    k != d &&
                    previous[off + k - 1] <
                    previous[off + k + 1]
                )
            )
            ? k + 1
            : k - 1;

        int px = previous[off + pk];
        int py = px - pk;

        while (x > px && y > py) {

            operations.push_back({
                '=',
                int(p) + x - 1,
                int(p) + y - 1
            });

            --x;
            --y;
        }

        if (x == px) {

            operations.push_back({
                '+',
                int(p) + x,
                int(p) + y - 1
            });

            --y;

        } else {

            operations.push_back({
                '-',
                int(p) + x - 1,
                int(p) + y
            });

            --x;
        }
    }

    while (x > 0 && y > 0) {

        operations.push_back({
            '=',
            int(p) + x - 1,
            int(p) + y - 1
        });

        --x;
        --y;
    }

    std::reverse(
        operations.begin(),
        operations.end()
    );

    size_t i = 0;

    // Group consecutive modifications.

    while (i < operations.size()) {

        if (operations[i].kind == '=') {

            ++i;
            continue;
        }

        std::deque<std::string> oldWords;
        std::deque<std::string> newWords;

        int oldPos = 0;
        int newPos = 0;

        while (
            i < operations.size() &&
            operations[i].kind != '='
        ) {
            auto op = operations[i++];

            if (op.kind == '-') {

                if (!oldPos)
                    oldPos = op.ai + 1;

                oldWords.push_back(a[op.ai]);

            } else {

                if (!newPos)
                    newPos = op.bi + 1;

                newWords.push_back(b[op.bi]);
            }
        }

        crow::json::wvalue c;

        c["type"] =
            oldWords.empty() ? "added" :
            newWords.empty() ? "removed" :
            "replaced";

        c["old_text"] = join(
            oldWords,
            0,
            oldWords.size()
        );

        c["new_text"] = join(
            newWords,
            0,
            newWords.size()
        );

        c["old_line"] = oldPos;
        c["new_line"] = newPos;

        output["changes"][changeIndex++] =
            std::move(c);
    }

    return output;
}

// ==========================================
// PDF PATH HANDLING
// ==========================================

static std::string quotePath(
    const fs::path& p
) {
    return "\"" +
           fs::absolute(p).string() +
           "\"";
}

// ==========================================
// PDF TEXT EXTRACTION USING POPPLER
// ==========================================

static bool pdfText(
    const fs::path& pdf,
    const fs::path& txt
) {
    std::error_code ec;

    fs::remove(txt, ec);

    std::string command =
        "pdftotext -layout -enc UTF-8 " +
        quotePath(pdf) + " " +
        quotePath(txt);

#ifdef _WIN32
    command += " >NUL 2>&1";
#else
    command += " >/dev/null 2>&1";
#endif

    return
        std::system(command.c_str()) == 0 &&
        fs::exists(txt);
}

// ==========================================
// ORIGINAL AND MODIFIED FILE COMPARISON
// ==========================================

static crow::response compare(
    const Evidence& e
) {
    if (
        !fs::exists(original(e)) ||
        !fs::exists(monitored(e))
    ) {
        return fail(
            "Evidence file missing",
            404
        );
    }

    auto h = hashFile(monitored(e));

    if (h.empty())
        return fail(
            "Unable to calculate current hash",
            500
        );

    crow::json::wvalue r;

    bool changed = h != e.originalHash;

    r["id"] = e.id;
    r["name"] = e.name;
    r["original_hash"] = e.originalHash;
    r["current_hash"] = h;
    r["tampered"] = changed;
    r["comparison_mode"] = "text";
    r["pages"] = emptyArray();

    if (!changed) {

        r["message"] =
            "File verified: "
            "no modification detected.";

        return json(std::move(r));
    }

    std::string a;
    std::string b;

    auto extension = ext(e.name);

    // PDF comparison.

    if (extension == ".pdf") {

        auto t1 =
            base / "metadata" /
            (e.id + "_original_extract.txt");

        auto t2 =
            base / "metadata" /
            (e.id + "_monitored_extract.txt");

        bool ok1 = pdfText(original(e), t1);
        bool ok2 = pdfText(monitored(e), t2);

        if (ok1)
            a = readFile(t1);

        if (ok2)
            b = readFile(t2);

        std::error_code ec;

        fs::remove(t1, ec);
        fs::remove(t2, ec);

        if (!ok1 || !ok2) {

            return fail(
                "PDF extraction failed; "
                "check pdftotext and PDF validity",
                422
            );
        }

    // Plain text comparison.

    } else if (
        extension == ".txt" ||
        extension == ".csv" ||
        extension == ".log" ||
        extension == ".json" ||
        extension == ".md"
    ) {
        a = readFile(original(e));
        b = readFile(monitored(e));

    } else {

        r["comparison_mode"] = "unsupported";

        r["message"] =
            "Hash mismatch. Text comparison "
            "is unavailable for this file type.";

        return json(std::move(r));
    }

    if (normalize(a) == normalize(b)) {

        r["message"] =
            "SHA-256 mismatch, but extracted "
            "text is identical. Formatting, "
            "metadata or images may have changed.";

    } else {

        auto difference = diffText(a, b);

        difference["page"] =
            extension == ".pdf" ? 0 : 1;

        r["pages"][size_t(0)] =
            std::move(difference);

        r["message"] =
            "Readable text changes detected.";
    }

    return json(std::move(r));
}

// ==========================================
// LIVE FILE INTEGRITY SCANNING
// ==========================================

static void scan() {

    std::lock_guard<std::mutex> lock(mu);

    for (const auto& e : evidence) {

        std::string h =
            hashFile(monitored(e));

        auto it = observed.find(e.id);

        if (it == observed.end()) {

            observed[e.id] = h;
            continue;
        }

        if (it->second == h)
            continue;

        std::string kind;

        if (h.empty()) {

            kind = "deleted";

        } else if (
            it->second.empty() ||
            h == e.originalHash
        ) {
            kind = "restored";

        } else {

            kind = "modified";
        }

        it->second = h;

        addEvent(e, kind, h);
    }
}

// ==========================================
// BACKGROUND MONITORING THREAD
// ==========================================

static void watcher() {

    while (running) {

        if (monitoring)
            scan();

        std::this_thread::sleep_for(
            std::chrono::seconds(2)
        );
    }
}

// ==========================================
// MAIN FUNCTION
// ==========================================

int main() {

    fs::create_directories(
        base / "originals"
    );

    fs::create_directories(
        base / "monitored"
    );

    fs::create_directories(
        base / "metadata"
    );

    loadIndex();
    loadEvents();

    for (const auto& e : evidence) {

        observed[e.id] =
            hashFile(monitored(e));
    }

    std::thread worker(watcher);

    crow::SimpleApp app;

    // ======================================
    // HOME PAGE
    // ======================================

    CROW_ROUTE(app, "/")
    ([] {

        return fileResponse(
            "frontend/index.html",
            "text/html; charset=utf-8",
            true
        );
    });

    // ======================================
    // SERVER HEALTH
    // ======================================

    CROW_ROUTE(app, "/api/health")
    ([] {

        crow::json::wvalue v;

        v["status"] = "running";
        v["monitoring"] = monitoring.load();

        return json(std::move(v));
    });

    // ======================================
    // EVIDENCE LIBRARY
    // ======================================

    CROW_ROUTE(app, "/api/evidence")
    ([] {

        std::lock_guard<std::mutex> lock(mu);

        crow::json::wvalue v;

        v["items"] = emptyArray();

        size_t index = 0;

        for (const auto& e : evidence) {

            v["items"][index++] = summary(e);
        }

        return json(std::move(v));
    });

    // ======================================
    // UPLOAD EVIDENCE
    // ======================================

    CROW_ROUTE(app, "/api/upload")
    .methods(crow::HTTPMethod::POST)
    ([](const crow::request& req) {

        if (req.body.empty()) {

            return fail(
                "Choose a nonempty file"
            );
        }

        if (
            req.body.size() >
            25ULL * 1024 * 1024
        ) {
            return fail(
                "Maximum 25 MiB",
                413
            );
        }

        std::lock_guard<std::mutex> lock(mu);

        auto t =
            std::chrono::duration_cast<
                std::chrono::microseconds
            >(
                std::chrono::system_clock::now()
                    .time_since_epoch()
            ).count();

        Evidence e;

        e.id = std::to_string(t);

        while (lookup(e.id))
            e.id += '1';

        e.name = safeName(
            req.get_header_value("X-Filename")
        );

        e.type = mime(e.name);
        e.created = timestamp();

        if (
            !writeFile(original(e), req.body) ||
            !writeFile(monitored(e), req.body)
        ) {
            std::error_code ec;

            fs::remove(original(e), ec);
            fs::remove(monitored(e), ec);

            return fail(
                "Cannot store evidence",
                500
            );
        }

        e.originalHash = hashFile(original(e));

        if (e.originalHash.empty()) {

            std::error_code ec;

            fs::remove(original(e), ec);
            fs::remove(monitored(e), ec);

            return fail(
                "Hash generation failed",
                500
            );
        }

        evidence.push_back(e);

        observed[e.id] = e.originalHash;

        saveIndex();

        addEvent(
            e,
            "uploaded",
            e.originalHash
        );

        return json(summary(e), 201);
    });

    // ======================================
    // VIEW ORIGINAL OR MONITORED FILE
    // ======================================

    CROW_ROUTE(
        app,
        "/api/evidence/<string>/view/<string>"
    )
    ([](
        const std::string& id,
        const std::string& version
    ) {

        std::lock_guard<std::mutex> lock(mu);

        auto* e = lookup(id);

        if (!e)
            return fail("Unknown evidence", 404);

        if (
            version != "original" &&
            version != "monitored"
        ) {
            return fail("Invalid version");
        }

        return fileResponse(
            version == "original"
                ? original(*e)
                : monitored(*e),
            e->type
        );
    });

    // ======================================
    // UPLOAD MODIFIED COPY
    // ======================================

    CROW_ROUTE(
        app,
        "/api/evidence/<string>/replace"
    )
    .methods(crow::HTTPMethod::POST)
    ([](
        const crow::request& req,
        const std::string& id
    ) {

        if (req.body.empty())
            return fail("Choose a nonempty file");

        if (
            req.body.size() >
            25ULL * 1024 * 1024
        ) {
            return fail(
                "Maximum 25 MiB",
                413
            );
        }

        std::lock_guard<std::mutex> lock(mu);

        auto* e = lookup(id);

        if (!e)
            return fail("Unknown evidence", 404);

        if (!writeFile(
                monitored(*e),
                req.body
            )) {

            return fail(
                "Unable to replace file",
                500
            );
        }

        auto h = hashFile(monitored(*e));

        if (h.empty())
            return fail("Hash generation failed", 500);

        if (monitoring) {

            std::string previous =
                observed[e->id];

            if (previous != h) {

                addEvent(
                    *e,
                    h == e->originalHash
                        ? "restored"
                        : "modified",
                    h
                );

                observed[e->id] = h;
            }
        }

        return json(summary(*e));
    });

    // ======================================
    // CHECK FILE INTEGRITY
    // ======================================

    CROW_ROUTE(
        app,
        "/api/evidence/<string>/check"
    )
    ([](const std::string& id) {

        std::lock_guard<std::mutex> lock(mu);

        auto* e = lookup(id);

        if (!e)
            return fail("Unknown evidence", 404);

        return json(summary(*e));
    });

    // ======================================
    // COMPARE EVIDENCE
    // ======================================

    CROW_ROUTE(
        app,
        "/api/evidence/<string>/compare"
    )
    ([](const std::string& id) {

        std::lock_guard<std::mutex> lock(mu);

        auto* e = lookup(id);

        if (!e)
            return fail("Unknown evidence", 404);

        return compare(*e);
    });

    // ======================================
    // MONITORING STATUS
    // ======================================

    CROW_ROUTE(app, "/api/monitor/status")
    ([] {

        std::lock_guard<std::mutex> lock(mu);

        crow::json::wvalue v;

        v["enabled"] = monitoring.load();
        v["interval_seconds"] = 2;
        v["monitored_count"] = evidence.size();
        v["event_count"] = events.size();

        return json(std::move(v));
    });

    // ======================================
    // START MONITORING
    // ======================================

    CROW_ROUTE(app, "/api/monitor/start")
    .methods(crow::HTTPMethod::POST)
    ([] {

        std::lock_guard<std::mutex> lock(mu);

        for (const auto& e : evidence) {

            observed[e.id] =
                hashFile(monitored(e));
        }

        monitoring = true;

        crow::json::wvalue v;

        v["enabled"] = true;

        return json(std::move(v));
    });

    // ======================================
    // STOP MONITORING
    // ======================================

    CROW_ROUTE(app, "/api/monitor/stop")
    .methods(crow::HTTPMethod::POST)
    ([] {

        monitoring = false;

        crow::json::wvalue v;

        v["enabled"] = false;

        return json(std::move(v));
    });

    // ======================================
    // MONITORING EVENT HISTORY
    // ======================================

    CROW_ROUTE(app, "/api/monitor/events")
    ([] {

        std::lock_guard<std::mutex> lock(mu);

        crow::json::wvalue v;

        v["items"] = emptyArray();

        size_t start =
            events.size() > 100
                ? events.size() - 100
                : 0;

        size_t index = 0;

        for (
            size_t i = events.size();
            i > start;
        ) {
            const auto& e = events[--i];

            crow::json::wvalue x;

            x["seq"] = e.seq;
            x["id"] = e.id;
            x["name"] = e.name;
            x["kind"] = e.kind;
            x["time"] = e.when;
            x["hash"] = e.hash;

            v["items"][index++] =
                std::move(x);
        }

        return json(std::move(v));
    });

    // ======================================
    // START FORENSIX SERVER
    // ======================================

    std::cout
        << "\n==================================\n"
        << "       FORENSIX SERVER\n"
        << "==================================\n"
        << "Server: http://localhost:5000\n"
        << "Monitoring interval: 2 seconds\n"
        << "Press Ctrl+C to stop the server\n"
        << "==================================\n";

    try {

        app.bindaddr("127.0.0.1")
           .port(5000)
           .concurrency(4)
           .run();

    } catch (const std::exception& e) {

        std::cerr
            << "Server error: "
            << e.what()
            << '\n';

        running = false;

        worker.join();

        return 1;
    }

    running = false;

    worker.join();

    return 0;
}
