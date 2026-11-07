#include <iostream>
struct SmartCard { long long balance; };
int main()
{
    SmartCard card{10000};
    card.balance -= 9999;      // compiles; nothing checks the Rs 50 rule
    card.balance = -500;       // compiles; negative balance
    std::cout << card.balance << '\n';
}
