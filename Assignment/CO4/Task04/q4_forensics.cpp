#include <iostream>
using namespace std;
class Account {
public:
    double rate() const { return 3.5; }
    virtual double vrate() const { return 3.5; }
    ~Account() { cout << "Account destructor\n"; } // Deliberately non-virtual.
};
class SeniorAccount : public Account {
    double* history;
public:
    SeniorAccount() : history(new double[100]{}) {}
    double rate() const { return 4.0; }
    double vrate() const override { return 4.0; }
    ~SeniorAccount() { cout << "SeniorAccount destructor\n"; delete[] history; }
};
int main() {
    Account* accounts[2] = {new Account, new SeniorAccount};
    cout << "Account rates:\n";
    for (Account* a : accounts) cout << a->rate() << '\n';
    cout << "\nVirtual rates:\n";
    for (Account* a : accounts) cout << a->vrate() << '\n';
    cout << "\nDeleting through base pointers:\n";
    for (Account* a : accounts) delete a;
    cout << "\nObject slicing test:\n";
    SeniorAccount senior; Account copy = senior;
    cout << "Copied base rate: " << copy.vrate() << '\n';
}