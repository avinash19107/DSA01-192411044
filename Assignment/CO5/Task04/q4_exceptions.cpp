#include <iostream>
#include <stdexcept>
#include <string>
#include <new>
#include <limits>
#include <cstddef>
using namespace std;
class BillingError : public runtime_error { public: using runtime_error::runtime_error; };
class InvalidCharge : public BillingError { public: using BillingError::BillingError; };
class ClaimError : public BillingError { public: using BillingError::BillingError; };
class UnknownPackage : public BillingError { public: using BillingError::BillingError; };
class PatientNotFound : public BillingError { public: using BillingError::BillingError; };
class HospitalBill {
    string patient; double amount;
public:
    HospitalBill(string p, double a) : patient(p), amount(a) {
        if (amount < 0) throw InvalidCharge("Negative bill amount");
    }
    double getAmount() const noexcept { return amount; }
    string getPatient() const { return patient; }
    void display() const {
        cout << "Patient: " << patient << '\n';
        cout << "Bill amount: Rs. " << amount << '\n';
    }
    ~HospitalBill() noexcept { cout << "Bill object destroyed\n"; }
};
double approveClaim(double bill, double cover) {
    if (bill < 0 || cover < 0) throw InvalidCharge("Negative amount or cover");
    if (bill > cover) throw ClaimError("Claim exceeds insurance cover");
    return bill;
}
double governmentPackage(const string& code) {
    if (code == "GENERAL") return 5000;
    if (code == "SURGERY") return 40000;
    throw UnknownPackage("Unknown government package");
}
void findPatient(bool exists) {
    if (!exists) throw PatientNotFound("Patient record not found");
    cout << "Patient record found\n";
}
int main() {
    cout << "HOSPITAL EXCEPTION HANDLING\n\n";
    try { HospitalBill bill("Ravi", 12000); bill.display(); }
    catch (const BillingError& e) { cout << "Billing error: " << e.what() << '\n'; }
    cout << '\n';
    try { cout << "Insurance approved: Rs. " << approveClaim(60000, 50000) << '\n'; }
    catch (const ClaimError& e) { cout << "Claim error: " << e.what() << '\n'; }
    cout << '\n';
    try { cout << "Package amount: Rs. " << governmentPackage("UNKNOWN") << '\n'; }
    catch (const UnknownPackage& e) { cout << "Package error: " << e.what() << '\n'; }
    cout << '\n';
    try { findPatient(false); }
    catch (const PatientNotFound& e) { cout << "Patient error: " << e.what() << '\n'; }
    cout << '\n';
    try {
        size_t count = numeric_limits<size_t>::max();
        int* data = new int[count]; delete[] data;
    } catch (const bad_alloc&) {
        cout << "Memory error: allocation failed\n";
    } catch (const exception& e) {
        cout << "Other allocation error: " << e.what() << '\n';
    }
    cout << "\nProgram completed safely\n";
}