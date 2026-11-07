#include <climits>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

int main() {
    std::cout << "C++ data type sizes (bytes)\n";
    std::cout << "bool       " << sizeof(bool) << '\n';
    std::cout << "char       " << sizeof(char) << '\n';
    std::cout << "int        " << sizeof(int) << '\n';
    std::cout << "unsigned   " << sizeof(unsigned int) << '\n';
    std::cout << "long long  " << sizeof(long long) << '\n';
    std::cout << "float      " << sizeof(float) << '\n';
    std::cout << "double     " << sizeof(double) << '\n';

    std::cout << "\nInteger limits\n";
    std::cout << "INT_MAX       " << INT_MAX << '\n';
    std::cout << "LLONG_MAX     " << LLONG_MAX << '\n';
    std::cout << "UINT_MAX      " << UINT_MAX << '\n';

    std::cout << "\nFloating-point representation\n";
    std::cout << std::setprecision(17);
    std::cout << "0.1 + 0.2 = " << (0.1 + 0.2) << '\n';
    std::cout << "10.8 stored = " << 10.8 << '\n';
    std::cout << "0.1 * 3 == 0.3 ? " << std::boolalpha << (0.1 * 3.0 == 0.3) << '\n';

    std::cout << "\nType conversion examples\n";
    std::cout << "true + 2 = " << (true + 2) << '\n';
    std::cout << "7 / 2.0 = " << (7 / 2.0) << '\n';

    std::cout << "\nAccumulated floating-point error (absolute rupees)\n";
    const long long counts[] = {10, 1000, 100000, 1000000, 3000000, 10000000};
    for (long long n : counts) {
        double sum1080 = 0.0;
        double sum10 = 0.0;
        for (long long i = 0; i < n; ++i) {
            sum1080 += 10.80;
            sum10 += 0.10;
        }
        const long long exact1080Paise = n * 1080LL;
        const long long exact10Paise = n * 10LL;
        const double exact1080Rupees = exact1080Paise / 100.0;
        const double exact10Rupees = exact10Paise / 100.0;
        std::cout << "n=" << n
                  << " Rs10.80_error=" << std::scientific << std::abs(sum1080 - exact1080Rupees)
                  << " Rs0.10_error=" << std::abs(sum10 - exact10Rupees) << '\n';
    }
    return 0;
}
