#include <iostream>
using namespace std;
class Account {
    double transactions[10];
    int count = 0;
public:
    void add(double amount) {
        if (count == 10) {
            for (int i = 1; i < 10; i++) transactions[i - 1] = transactions[i];
            count = 9;
        }
        transactions[count++] = amount;
    }
    void show() const {
        for (int i = 0; i < count; i++) cout << transactions[i] << '\\n';
    }
};
int main() {
    Account account;
    for (int i = 1; i <= 11; i++) account.add(i * 100);
    cout << "Last 10 transactions:\\n";
    account.show();
}
