# Task 12 – RAII and Sanitizer Safety

The RAII run used `vector<unique_ptr<Bill>>`, printed a grand total of Rs. 49,200 and showed derived destructors before base destructors. A separate `q12_exception_sanitizer.cpp` was added for the exact B4.2 requirement: an exception is thrown and caught while a `unique_ptr` owns a polymorphic bill. This additional program still needs to be run under AddressSanitizer and its terminal screenshot added.

Compile: `g++ -std=c++17 -Wall -Wextra source.cpp -o program`; run: `./program`.
