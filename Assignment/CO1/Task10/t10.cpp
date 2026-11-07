#include <iomanip>
#include <iostream>
#include <limits>

int main() {
    long long totalPaise = 0;
    double totalRupees = 0.0;
    float totalFloatRupees = 0.0f;
    int totalIntPaise = 0;
    long long farePaise = 0;
    long long count = 0;

    std::cout << "Enter fare values in paise, one per journey; enter EOF to finish.\n";
    while (std::cin >> farePaise) {
        if (farePaise < 0) {
            std::cerr << "Negative fare rejected.\n";
            return 1;
        }
        if (farePaise > std::numeric_limits<int>::max() - totalIntPaise) {
            // Do not perform signed overflow; report that int cannot hold the next sum.
            totalIntPaise = std::numeric_limits<int>::max();
        } else if (totalIntPaise != std::numeric_limits<int>::max()) {
            totalIntPaise += static_cast<int>(farePaise);
        }
        totalPaise += farePaise;
        totalRupees += static_cast<double>(farePaise) / 100.0;
        totalFloatRupees += static_cast<float>(farePaise) / 100.0f;
        ++count;
    }

    std::cout << "Journeys: " << count << '\n';
    std::cout << "Exact total (paise): " << totalPaise << '\n';
    std::cout << std::fixed << std::setprecision(2)
              << "Double total (Rs): " << totalRupees << '\n'
              << "Float total (Rs): " << totalFloatRupees << '\n';
    std::cout << "int accumulator status: "
              << (totalPaise > std::numeric_limits<int>::max()
                      ? "would overflow; accumulator capped for safety"
                      : "within INT_MAX") << '\n';
}
