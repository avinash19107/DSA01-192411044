#include <iostream>
using namespace std;
class Account {
public:
    virtual double rate() const { return 3.5; }
    virtual ~Account() { cout << "Account destructor\n"; }
};
class SeniorAccount : public Account {
    double* history;
public:
    SeniorAccount() : history(new double[100]{}) {}
    double rate() const override { return 4.0; }
    ~SeniorAccount() override {
        cout << "SeniorAccount destructor\n";
        delete[] history;
    }
};
int main() {
    Account* a = new Account;
    Account* b = new SeniorAccount;
    cout << "Account rate: " << a->rate() << '\n';
    cout << "Senior rate: " << b->rate() << '\n';
    cout << "\nDeleting objects:\n";
    delete a;
    delete b;
}