#ifndef FARE_CONSTANTS_H
#define FARE_CONSTANTS_H

enum class Zone : unsigned char { Inner, Middle, Outer };

constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int CONCESSION_PERCENT = 50; // Assumption: scenario does not specify percentage
constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_AM_START = 8 * 60;
constexpr int PEAK_AM_END = 10 * 60;
constexpr int PEAK_PM_START = 17 * 60;
constexpr int PEAK_PM_END = 20 * 60;

#endif
