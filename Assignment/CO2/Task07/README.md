# Q7 – Diagnose, Redesign and Validate

Compares a fixed ten-element array that shifts entries on each full-capacity insertion with a circular buffer that overwrites the oldest entry using a moving start index. Both versions process the same five million values and report the sum of the retained ten values.

**Build and run**
```bash
g++ -std=c++17 -O2 -Wall -Wextra q7_benchmark.cpp -o q7_benchmark
./q7_benchmark
```

**Recorded result:** Shifting array 24 ms; circular buffer 12 ms. Both retained the same final-ten total, `49999945`. Timings are specific to the recorded run and system.

**Evidence:** `screenshots/`.
