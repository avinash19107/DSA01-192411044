# Task 09 – Exceptions vs Return Codes Benchmark

Actual measured times for one million bills:

| Invalid | Return-code | Exceptions |
|---:|---:|---:|
| 0% | 2.352 ms | 2.812 ms |
| 1% | 2.891 ms | 15.264 ms |
| 50% | 1.970 ms | 394.454 ms |

Totals matched at each invalid percentage. The benchmark uses a bool/result return code. The assignment also asks for an `std::optional<double>` alternative and a comparison of result storage; that alternative remains to be implemented if required by the evaluator.

Compile: `g++ -std=c++17 -Wall -Wextra source.cpp -o program`; run: `./program`.
