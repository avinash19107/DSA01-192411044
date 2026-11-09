#include <iostream>
using namespace std;
int& returnReference(int marks[], int index) { return marks[index]; }
const int& returnConstReference(const int marks[], int index) {
    return marks[index];
}
int returnCopy(const int marks[], int index) { return marks[index]; }
int main() {
    int marks[] = {75, 92, 85};
    returnReference(marks, 1) = 98;
    cout << "After reference: " << marks[1] << '\\n';
    cout << "Const reference: " << returnConstReference(marks, 1) << '\\n';
    cout << "Returned copy: " << returnCopy(marks, 1) << '\\n';
}
