# CO1 — Task 02: Tokens, Keywords, Identifiers and Constants

## Purpose
Demonstrate C++ tokens, `#define` vs `constexpr`, and type-safe zone identifiers using `enum class`.

## Files
- `fare_constants.h`: single source of truth for zone fares, peak hours, minimum balance and concession assumption.
- `task02.cpp`: runnable demonstration of macro precedence and enum safety.
- `execution_output.txt`: actual output from compilation and execution.
- `t2_err.cpp`: intentionally invalid `enum class` conversion example.
- `compiler_error.txt`: actual compiler diagnostic for `t2_err.cpp` (expected compilation failure).

## Compile and run
```bash
g++ -std=c++17 -Wall -Wextra task02.cpp -o task02
./task02
```

## Verify compile-time type safety
```bash
g++ -std=c++17 -Wall -Wextra t2_err.cpp -o t2_err
```
The second command is *expected to fail*, because `enum class` does not implicitly convert to `int`.

## Explanation
`#define FARE_INNER 500 + 500` is substituted as text. Thus `FARE_INNER * 2` becomes `500 + 500 * 2` and produces 1500, whereas `constexpr int FARE_INNER_C = 500 + 500` produces 2000 when multiplied by 2.

`Zone` explicitly uses `unsigned char` as its underlying type, so it occupies 1 byte in this build. The plain `OldZone` occupies 4 bytes on this machine; this size is implementation-dependent.

## Complexity
Constant fare access and enum operations are O(1). Macros require no runtime storage; scalar `constexpr` constants typically do not require separate storage unless odr-used. The three-element `BASE_PAISE` array has constant space for this fixed design (24 bytes on this platform); generalized to z zones, its space is O(z).
