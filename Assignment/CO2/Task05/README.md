# Q5 – Static Members and Arrays of Objects

Demonstrates a class-wide static counter, constructor-assigned identifiers, a fixed-capacity bus-ticket allocation system, and the persistence of static state across function calls.

**Build and run**
```bash
g++ -std=c++17 -Wall -Wextra q5_prediction.cpp -o q5_prediction && ./q5_prediction
g++ -std=c++17 -Wall -Wextra q5_busticket.cpp -o q5_busticket && ./q5_busticket
g++ -std=c++17 -Wall -Wextra q5_function.cpp -o q5_function && ./q5_function
```

**Observed result:** Three seats are issued, excess tickets enter the waiting list, and the static counter remains updated after the ticket-creation function returns.

**Evidence:** `screenshots/`.
