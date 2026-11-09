#include <iostream>
using namespace std;
double charge(double weight) { return weight * 50; }
double charge(double weight, bool express) {
    return weight * (express ? 80 : 50);
}
double charge(double weight, bool express = false, bool insured = false) {
    return weight * 50 + (express ? 30 : 0) + (insured ? 20 : 0);
}
int main() { cout << charge(2.0) << '\\n'; }
