#ifndef METRO_CORE_H
#define METRO_CORE_H
#include <algorithm>

enum class Zone { Inner, Middle, Outer };
constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int CONCESSION_PERCENT = 50; // Assignment assumption; confirm with faculty.
constexpr long long MIN_BALANCE_PAISE = 5000;

inline bool isPeak(int hour, int minute) {
    const int t = hour * 60 + minute;
    return (t >= 8 * 60 && t < 10 * 60) || (t >= 17 * 60 && t < 20 * 60);
}
inline long long percent(long long amount, int p) {
    return (amount * p + 50) / 100; // integer paise, half-up rounding
}
inline long long fare(Zone z, bool peak, bool concession = false) {
    const int index = static_cast<int>(z);
    if (index < 0 || index > 2) return -1;
    long long f = BASE_PAISE[index];
    if (concession) f -= percent(f, CONCESSION_PERCENT);
    if (peak) f += percent(f, PEAK_SURCHARGE_PERCENT);
    return f;
}
inline bool canTravel(long long balance, long long f) {
    return f >= 0 && balance - f >= MIN_BALANCE_PAISE;
}
#endif
