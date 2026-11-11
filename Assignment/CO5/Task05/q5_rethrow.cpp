#include <iostream>
#include <stdexcept>
using namespace std;
void validate(double amount) {
    if (amount < 0) throw invalid_argument("negative amount");
    if (amount > 1000000) throw out_of_range("amount too large");
    cout << "Validation successful\n";
}
void process(double amount) {
    try { validate(amount); }
    catch (const out_of_range& e) {
        cout << "Audit log: " << e.what() << '\n';
        throw;
    }
}
int main() {
    double amounts[] = {500, 2000000, -100};
    for (double amount : amounts) {
        try { process(amount); cout << "Bill processed\n"; }
        catch (const exception& e) { cout << "Main handler: " << e.what() << '\n'; }
    }
    cout << "Program completed\n";
}