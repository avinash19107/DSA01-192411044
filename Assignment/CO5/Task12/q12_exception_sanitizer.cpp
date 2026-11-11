#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;
class Bill {
public:
    virtual double total() const = 0;
    virtual ~Bill() { cout << "Bill base destructor\n"; }
};
class OPBill : public Bill {
    string* record;
public:
    OPBill() : record(new string("patient record")) {}
    double total() const override { return 1700; }
    ~OPBill() override { cout << "OPBill destructor\n"; delete record; }
};
void process(bool reject) {
    unique_ptr<Bill> bill = make_unique<OPBill>();
    cout << "Bill total: " << bill->total() << '\n';
    if (reject) throw runtime_error("claim rejected");
    cout << "Claim accepted\n";
}
int main() {
    try {
        process(true);
    } catch (const exception& e) {
        cout << "Caught exception: " << e.what() << '\n';
    } catch (...) {
        cout << "Unknown error caught\n";
    }
    cout << "Program continued safely\n";
}