# Task 07 – Procedural vs Object-Oriented

Two source excerpts are included: procedural global-state version and encapsulated SmartCard version. A third file demonstrates the public-balance weakness.

Compile each separately:
```bash
g++ -std=c++17 -Wall -Wextra procedural.cpp -o procedural
g++ -std=c++17 -Wall -Wextra oop.cpp -o oop
g++ -std=c++17 -Wall -Wextra public_balance.cpp -o public_balance
```
Capture your own output and explain how public balance can violate the Rs 50 minimum-balance invariant.
