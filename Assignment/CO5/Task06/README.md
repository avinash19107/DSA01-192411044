# Task 06 – Polymorphic Billing Implementation

The two-bill TODO program produced OP Ravi: 1700, IP Meena: 47500, Total 49200. The extended program tested four bill types against SelfPay, Insurance and GovernmentScheme (12 combinations). Removing `virtual` from a pure virtual function declaration caused compile-time errors; removing the virtual destructor caused an AddressSanitizer `new-delete-type-mismatch`. The corrected program invokes derived then base destructors.

Compile: `g++ -std=c++17 -Wall -Wextra source.cpp -o program`; run: `./program`.
