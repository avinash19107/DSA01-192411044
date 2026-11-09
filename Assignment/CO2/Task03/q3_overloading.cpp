#include <iostream>
using namespace std;
struct Parcel { double weightKg; bool express; bool insured; };
double charge(int grams) {
    cout << "Selected: int (grams)\\n";
    return grams / 1000.0 * 50;
}
double charge(double kg, bool express = false, bool insured = false) {
    cout << "Selected: double (kg)\\n";
    return kg * 50 + (express ? 30 : 0) + (insured ? 20 : 0);
}
double charge(const Parcel& p) {
    cout << "Selected: Parcel\\n";
    return p.weightKg * 50 + (p.express ? 30 : 0) + (p.insured ? 20 : 0);
}
int main() {
    Parcel p{2.0, true, true};
    cout << "Charge: " << charge(2000) << '\\n';
    cout << "Charge: " << charge(2.0) << '\\n';
    cout << "Charge: " << charge(2) << '\\n';
    cout << "Charge: " << charge(2.0f) << '\\n';
    cout << "Charge: " << charge(2.0, true) << '\\n';
    cout << "Charge: " << charge(p) << '\\n';
}
