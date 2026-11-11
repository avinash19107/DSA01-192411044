# Task 08 – Virtual vs Switch Benchmark

Actual measured totals matched at 1,000, 1,000,000 and 10,000,000 records. Timings from the supplied Kali run: 0.001/0.001 ms; 3.235/1.841 ms; 41.055/27.332 ms (virtual/switch). This particular switch implementation was faster at larger sizes. The 10-record correctness subtest and per-element memory comparison should be included in the final interpretation.

Compile: `g++ -std=c++17 -Wall -Wextra source.cpp -o program`; run: `./program`.
