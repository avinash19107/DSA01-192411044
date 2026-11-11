# Task 04 – Exception Strategy

Exception hierarchy:

```text
std::exception
  └── std::runtime_error
       └── BillingError
            ├── InvalidCharge
            ├── ClaimError
            ├── UnknownPackage
            └── PatientNotFound

std::bad_alloc derives separately from std::exception.
```

Potentially throwing operations: bill validation, claim approval, package lookup, patient lookup, parsing with `std::stod`, and allocation. Destructors and simple non-throwing observers should be `noexcept` where appropriate. Destructors should not throw because a second exception during stack unwinding can terminate the process.

Alternative: return an enum/status object. The normal path avoids exception machinery, but every caller must inspect and propagate the status and error information. Both approaches are O(1) per validation; exceptions are preferable for exceptional failures, while return codes/optional suit frequent expected invalid input.


Compile: `g++ -std=c++17 -Wall -Wextra source.cpp -o program`; run: `./program`.
