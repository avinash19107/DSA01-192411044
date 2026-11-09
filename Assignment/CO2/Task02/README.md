# Q2 – Return by Reference and Its Dangers

Demonstrates modifying an array element through a returned reference, compares reference/const-reference/copy results, captures the compiler warning for returning a local variable, and shows vector capacity growth that can invalidate references.

**Build and run**
```bash
g++ -std=c++17 -Wall -Wextra q2_reference.cpp -o q2_reference && ./q2_reference
g++ -std=c++17 -Wall -Wextra q2_comparison.cpp -o q2_comparison && ./q2_comparison
g++ -std=c++17 -Wall -Wextra q2_vector.cpp -o q2_vector && ./q2_vector
```

**Warning demonstration only**
```bash
g++ -std=c++17 -Wall -Wextra -Wreturn-local-addr q2_dangling.cpp -o q2_dangling
```
`q2_dangling.cpp` deliberately returns a reference to a local variable. Do not execute it; using the dangling reference has undefined behaviour.

**Evidence:** `screenshots/`.
