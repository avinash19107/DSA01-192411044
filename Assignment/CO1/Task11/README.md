# Task 11 – Final Design Recommendation

Contains a working example of loading fare values from a configuration file, used to compare run-time configuration with compile-time `constexpr` values.

Compile:
```bash
g++ -std=c++17 -Wall -Wextra config_fares.cpp -o config_fares
./config_fares
```
`fares.cfg` stores one fare per line in paise. Test a missing file, malformed value, negative fare and correct file. The master report contains the recommendation and design limitations.
