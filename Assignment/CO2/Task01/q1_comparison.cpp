#include <iostream>
using namespace std;
void byValue(long long fee, int percent) {
    fee -= fee * percent / 100;
    cout << "Inside call by value: " << fee << '\\n';
}
void byReference(long long& fee, int percent) {
    fee -= fee * percent / 100;
    cout << "Inside call by reference: " << fee << '\\n';
}
void byPointer(long long* fee, int percent) {
    if (fee != nullptr) {
        *fee -= *fee * percent / 100;
        cout << "Inside call by pointer: " << *fee << '\\n';
    }
}
int main() {
    long long fee1 = 45000, fee2 = 45000, fee3 = 45000;
    byValue(fee1, 10);
    cout << "Stored fee after value: " << fee1 << '\\n';
    byReference(fee2, 15);
    cout << "Stored fee after reference: " << fee2 << '\\n';
    byPointer(&fee3, 25);
    cout << "Stored fee after pointer: " << fee3 << '\\n';
}
