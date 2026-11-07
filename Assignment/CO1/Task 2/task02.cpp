#include <iostream>
#include "fare_constants.h"

// Intentionally unsafe macro to demonstrate operator precedence.
#define FARE_INNER 500 + 500
constexpr int FARE_INNER_C = 500 + 500;

enum OldZone { OInner, OMiddle, OOuter };

int main() {
    std::cout << "macro FARE_INNER*2 = " << FARE_INNER * 2 << '\n';
    std::cout << "constexpr FARE_INNER_C*2 = " << FARE_INNER_C * 2 << '\n';
    std::cout << "sizeof(Zone)=" << sizeof(Zone)
              << " sizeof(OldZone)=" << sizeof(OldZone) << '\n';
    std::cout << "plain enum arithmetic compiles: " << (OOuter + 5) << '\n';
    std::cout << "OInner == 0 ? " << (OInner == 0) << '\n';
    std::cout << "sizeof(FARE_INNER_C)=" << sizeof(FARE_INNER_C) << '\n';
    std::cout << "Inner base fare (paise) = " << BASE_PAISE[0] << '\n';
}
