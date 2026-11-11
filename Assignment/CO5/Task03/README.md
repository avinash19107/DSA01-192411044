# Task 03 – Abstract Payer Design

`Payer` defines pure virtual `amountCovered(const Bill&)`. `SelfPay` covers the full total; `Insurance` applies the policy co-payment and cover limit; `GovernmentScheme` uses fixed package rates. `CorporatePayer` demonstrates an extension without modifying existing payer classes.

Alternative: a function pointer or `std::function` can hold a runtime-selected policy. Invocation is O(1) in either approach. A derived payer object naturally stores its cover limit and co-payment data; a function object stores captured policy state.
