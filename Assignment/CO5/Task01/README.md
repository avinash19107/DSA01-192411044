# Task 01 – Polymorphic Bill Hierarchy

Every bill shares patient identity and the operations `total()`, `type()` and `print()`. `Bill` is abstract; `total()` and `type()` are pure virtual, `print()` is virtual with a shared implementation, and the destructor is virtual.

```text
                    Bill (abstract)
             + total() = 0
             + type() = 0
             + print() [virtual]
             + ~Bill() [virtual]
        /             |              |              \
 OutPatient       InPatient       DayCareBill    EmergencyBill
```

SIMATS-style pseudocode:

```text
ALGORITHM CalculateDailyTotal
BEGIN
    SET dailyTotal <- 0
    FOR EACH billPointer IN bills DO
        CALL billPointer.print()
        dailyTotal <- dailyTotal + billPointer.total()
    END FOR
    DISPLAY dailyTotal
END
```

Alternative: one tagged `Bill` record and `switch(type)` has O(n) total processing and O(1) per record; a new bill type requires changing the switch. Virtual dispatch is also O(n) overall and adds a vptr per polymorphic object, but extension adds a derived class without editing the loop.
