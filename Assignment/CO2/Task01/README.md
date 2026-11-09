# Q1 – Call by Value, Reference and Pointer

Compares parameter passing using a hostel-fee concession example. The programs demonstrate local-copy behaviour, caller-side modification through references and pointers, return-by-reference assignment, and default function arguments.

**Build and run**
```bash
g++ -std=c++17 -Wall -Wextra q1_prediction.cpp -o q1_prediction && ./q1_prediction
g++ -std=c++17 -Wall -Wextra q1_concession.cpp -o q1_concession && ./q1_concession
g++ -std=c++17 -Wall -Wextra q1_comparison.cpp -o q1_comparison && ./q1_comparison
```

**Observed results:** Value passing leaves the caller's fee unchanged. Reference and pointer passing update the caller's fee. The prediction program prints `1 12 13`, `1 100`, and `16 13 6`.

**Evidence:** `screenshots/`.
