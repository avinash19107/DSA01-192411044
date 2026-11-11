#include <iostream>
using namespace std;
class Bill {
public:
    virtual double total() const = 0;
    virtual ~Bill() { cout << "Bill destructor\n"; }
};
class OutPatient : public Bill {
    int* data;
public:
    OutPatient() : data(new int[100]{}) {}
    double total() const override { return 1700; }
    ~OutPatient() override { cout << "OutPatient destructor\n"; delete[] data; }
};
int main() {
    Bill* bill = new OutPatient;
    cout << "Bill total: " << bill->total() << '\n';
    delete bill;
}