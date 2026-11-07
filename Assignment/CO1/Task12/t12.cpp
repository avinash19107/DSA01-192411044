// Task 12: revised design - 4 zones, weekend discount, monthly pass
#include <iomanip>
#include <iostream>
#include <string>
 
enum class Zone
{
    Inner,
    Middle,
    Outer,
    Airport,
    Count
};
constexpr int ZONE_COUNT = static_cast<int>(Zone::Count);
constexpr long long BASE_PAISE[ZONE_COUNT] = {1000, 2000, 3000,
                                              6000}; // Rs 10, 20, 30, 60
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT_PERCENT = 10;
constexpr int CONCESSION_PERCENT = 50;
constexpr long long MIN_BALANCE_PAISE = 5000;
 
struct Journey
{
    Zone farthest;
    int hour, minute;
    int weekday; // weekday 0=Mon..6=Sun
    bool concession;
    int year, month;
};
 
constexpr bool isWeekend(int weekday) { return weekday >= 5; }
constexpr bool isPeak(int h, int m)
{
    int t = h * 60 + m;
    return (t >= 480 && t < 600) || (t >= 1020 && t < 1200);
}
constexpr long long pct(long long a, int p) { return (a * p + 50) / 100; }
 
// Fare rule kept in ONE place: weekend discount replaces the peak surcharge (assumption
// A1)
long long fare(const Journey &j)
{
    long long f = BASE_PAISE[static_cast<int>(j.farthest)];
    if (j.concession) f -= pct(f, CONCESSION_PERCENT);
    if (isWeekend(j.weekday))
        f -= pct(f, WEEKEND_DISCOUNT_PERCENT);
    else if (isPeak(j.hour, j.minute))
        f += pct(f, PEAK_SURCHARGE_PERCENT);
    return f;
}
 
class Pass
{ // monthly pass for two chosen zones
    unsigned mask_;
    int year_, month_;
 
  public:
    Pass(Zone a, Zone b, int y, int m)
        : mask_((1u << static_cast<int>(a)) | (1u << static_cast<int>(b))), year_(y),
          month_(m)
    {
    }
    bool covers(const Journey &j) const
    {
        return j.year == year_ && j.month == month_ &&
               (mask_ >> static_cast<int>(j.farthest) & 1u);
    }
};
 
class SmartCard
{
    long long balance_;
    const Pass *pass_ = nullptr;
 
  public:
    explicit SmartCard(long long b) : balance_(b) {}
    void attach(const Pass *p) { pass_ = p; }
    long long balance() const { return balance_; }
    // returns fare charged, or -1 if denied
    long long travel(const Journey &j)
    {
        if (pass_ && pass_->covers(j)) return 0; // unlimited journey, nothing deducted
        long long f = fare(j);
        if (balance_ - f < MIN_BALANCE_PAISE) return -1;
        balance_ -= f;
        return f;
    }
};
 
static std::string rs(long long p)
{
    std::string s = std::to_string(p / 100) + ".";
    if (p % 100 < 10) s += "0";
    return s + std::to_string(p % 100);
}
static int failures = 0;
static void check(const char *name, long long expected, long long actual)
{
    bool ok = expected == actual;
    if (!ok) ++failures;
    std::cout << std::left << std::setw(46) << name << " expected " << std::setw(5)
              << expected << " actual " << std::setw(5) << actual
              << (ok ? " PASS" : " FAIL") << '\n';
}
int main()
{
    check("Airport weekday 12:00", 6000,
          fare({Zone::Airport, 12, 0, 1, false, 2026, 11}));
    check("Airport weekday 09:00 (peak +20%)", 7200,
          fare({Zone::Airport, 9, 0, 1, false, 2026, 11}));
    check("Inner Saturday 12:00 (-10%)", 900,
          fare({Zone::Inner, 12, 0, 5, false, 2026, 11}));
    check("Inner Saturday 09:00 (peak window)", 900,
          fare({Zone::Inner, 9, 0, 5, false, 2026, 11}));
    check("Outer Sunday 18:00 (no surcharge)", 2700,
          fare({Zone::Outer, 18, 0, 6, false, 2026, 11}));
    check("Airport Sunday student", 2700,
          fare({Zone::Airport, 12, 0, 6, true, 2026, 11}));
    check("Middle Friday 17:00 senior peak", 1200,
          fare({Zone::Middle, 17, 0, 4, true, 2026, 11}));
    Pass p(Zone::Inner, Zone::Middle, 2026, 11);
    SmartCard a(10000);
    a.attach(&p);
    check("Pass: Middle journey free", 0,
          a.travel({Zone::Middle, 9, 0, 1, false, 2026, 11}));
    check("Pass: balance unchanged", 10000, a.balance());
    check("Pass: Outer not covered (peak 3600)", 3600,
          a.travel({Zone::Outer, 9, 0, 1, false, 2026, 11}));
    check("Pass: balance after Outer", 6400, a.balance());
    SmartCard c(10000);
    c.attach(&p);
    check("Pass: next month not covered (fare 2000)", 2000,
          c.travel({Zone::Middle, 12, 0, 1, false, 2026, 12}));
    SmartCard b(10000);
    check("No pass: Airport peak denied (-1)", -1,
          b.travel({Zone::Airport, 9, 0, 1, false, 2026, 11}));
    std::cout << (failures == 0 ? "ALL PASSED" : "SOME FAILED") << '\n';
    std::cout << "Worked example: Airport, Saturday 09:00, student = Rs "
              << rs(fare({Zone::Airport, 9, 0, 5, true, 2026, 11})) << '\n';
}
