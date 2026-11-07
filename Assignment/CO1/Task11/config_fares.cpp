#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<long long> loadFares(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("cannot open fare configuration");
    std::vector<long long> fares;
    long long value;
    while (in >> value) {
        if (value < 0) throw std::runtime_error("fare cannot be negative");
        fares.push_back(value);
    }
    if (!in.eof()) throw std::runtime_error("invalid value in fare configuration");
    if (fares.size() != 3) throw std::runtime_error("expected exactly three zone fares");
    return fares;
}

int main() {
    try {
        const auto fares = loadFares("fares.cfg");
        for (std::size_t i = 0; i < fares.size(); ++i)
            std::cout << "Zone " << i << ": " << fares[i] << " paise\n";
    } catch (const std::exception& e) {
        std::cerr << "Configuration error: " << e.what() << '\n';
        return 1;
    }
}
