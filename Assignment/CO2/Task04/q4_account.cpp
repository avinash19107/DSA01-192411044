#include <iostream>
#include <string>
using namespace std;
class SavingsAccount {
private:
    int accountNumber;
    double balance;
    double transactions[10];
    int count;
public:
    SavingsAccount(int acc, double initial)
        : accountNumber(acc), balance(initial), count(0) {}
    void addTransaction(double amount) {
        if (count == 10) {
            for (int i = 1; i < 10; i++) transactions[i - 1] = transactions[i];
            count = 9;
        }
        transactions[count++] = amount;
    }
    void deposit(double amount);
    void withdraw(double amount);
    void miniStatement() const;
};
void SavingsAccount::deposit(double amount) {
    if (amount > 0) { balance += amount; addTransaction(amount); }
}
void SavingsAccount::withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount; addTransaction(-amount);
    } else cout << "Withdrawal denied\\n";
}
void SavingsAccount::miniStatement() const {
    cout << "Account: " << accountNumber << '\\n'
         << "Balance: " << balance << '\\n' << "Last transactions:\\n";
    for (int i = 0; i < count; i++) cout << transactions[i] << '\\n';
}
int main() {
    SavingsAccount account(1001, 5000);
    account.deposit(1000); account.withdraw(500);
    account.deposit(200); account.withdraw(300);
    account.miniStatement();
}
