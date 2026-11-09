# Q3 – Default Arguments and Function Overloading

Shows an ambiguous overload set and a revised courier-charge design using an integer-grams overload, a kilogram overload with default arguments, and a `Parcel` overload.

**Ambiguity demonstration (compile only)**
```bash
g++ -std=c++17 -Wall -Wextra q3_ambiguity.cpp -o q3_ambiguity
```
Compilation is expected to fail because `charge(2.0)` matches more than one viable overload.

**Revised implementation**
```bash
g++ -std=c++17 -Wall -Wextra q3_overloading.cpp -o q3_overloading
./q3_overloading
```

**Observed result:** Six calls select the intended overloads without ambiguity.

**Evidence:** `screenshots/`.
