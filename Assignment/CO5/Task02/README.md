# Task 02 – Runtime Binding and Virtual Destructors

- Early binding resolves a non-virtual call at compile time.
- Late binding resolves a virtual call using the dynamic type of the object.
- `Bill::show()` is non-virtual, but its call to virtual `total()` dispatches to `OPBill::total()`.

Vtable sketch (conceptual; exact ABI layout is implementation-specific):

```text
Bill vtable:       [~Bill, total]
OPBill vtable:     [~OPBill, OPBill::total]
InPatient vtable:  [~InPatient, InPatient::total]

b -> OPBill object -> OPBill vptr -> OPBill::total()
```

A virtual base destructor is required when deleting derived objects through `Bill*`; it invokes the derived destructor and then the base destructor. The captured correct output was `500 ~OPBill ~Bill`. Removing virtual produced a compiler warning and `500 ~Bill`, plus AddressSanitizer `new-delete-type-mismatch`.


Compile: `g++ -std=c++17 -Wall -Wextra source.cpp -o program`; run: `./program`.
