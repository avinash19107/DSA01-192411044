#include <iostream>
using namespace std;
int& invalidReference() {
    int value = 100;
    return value; // Deliberately unsafe: reference to a local object.
}
int main() {
    int& result = invalidReference();
    cout << result << '\\n'; // Do not execute: undefined behaviour.
}
