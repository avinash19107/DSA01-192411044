# Q4 – Class with an Array of Transactions

Implements a savings account with private account data, balance and a fixed array containing the ten most recent transactions. Deposits and withdrawals are defined outside the class using the scope resolution operator. The capacity test verifies that the oldest transaction is discarded when an eleventh transaction arrives.

**Build and run**
```bash
g++ -std=c++17 -Wall -Wextra q4_account.cpp -o q4_account && ./q4_account
g++ -std=c++17 -Wall -Wextra q4_capacity.cpp -o q4_capacity && ./q4_capacity
```

**Observed result:** The account balance and transaction history are updated correctly. After eleven insertions, the retained values are 200 through 1100.

**Evidence:** `screenshots/`.
