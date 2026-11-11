# Task 05 – Recovery and Rethrowing

`throw;` rethrows the active exception; it preserves the original exception object. `catch (const ClaimError& e)` can log and rethrow with `throw;`. `throw e;` creates a new exception object from the expression and can slice if `e` is a base-class reference.

Stack unwinding destroys local automatic objects in reverse construction order. RAII types such as `std::unique_ptr` and `std::vector` release resources automatically when exceptions leave a scope. Manual `delete` in every catch path increases leak risk as error paths are added.


Compile: `g++ -std=c++17 -Wall -Wextra source.cpp -o program`; run: `./program`.
