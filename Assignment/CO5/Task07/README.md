# Task 07 – Error Conditions, Prediction and Rethrowing

The prediction program output was `ok done caught negative [log too large] caught too large`. `invalid_argument` bypasses the inner `out_of_range` handler; `out_of_range` is logged and rethrown. The completed claim program approved 40000, logged and rejected the over-cover claim, and rejected a negative amount. The `throw e` comparison had the same visible output for this specific derived exception reference.

Compile: `g++ -std=c++17 -Wall -Wextra source.cpp -o program`; run: `./program`.
