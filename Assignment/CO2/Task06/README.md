# Q6 – Friend Functions and Inline Functions

Uses friend functions to compare private hour/minute fields and calculate the absolute difference between two times. Correctness cases include times across noon and equal times. A benchmark compares an inline function with a non-inlined function over 10,000,000 calls.

**Build and run**
```bash
g++ -std=c++17 -Wall -Wextra q6_time.cpp -o q6_time && ./q6_time
g++ -std=c++17 -O0 -Wall -Wextra q6_benchmark.cpp -o benchmark_O0 && ./benchmark_O0
g++ -std=c++17 -O2 -Wall -Wextra q6_benchmark.cpp -o benchmark_O2 && ./benchmark_O2
```

**Recorded measurements:** `-O0`: inline 16 ms, normal 16 ms. `-O2`: inline 0 ms at millisecond display resolution, normal 4 ms. Results are machine- and run-dependent.

**Evidence:** `screenshots/`.
