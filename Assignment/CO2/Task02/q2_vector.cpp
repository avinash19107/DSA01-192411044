#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> marks;
    marks.reserve(2);
    marks.push_back(75);
    marks.push_back(92);
    int& highest = marks[1];
    cout << "Before growth:\\nCapacity: " << marks.capacity()
         << "\\nHighest mark: " << highest << '\\n';
    marks.push_back(85);
    cout << "\\nAfter growth:\\nCapacity: " << marks.capacity()
         << "\\nVector size: " << marks.size()
         << "\\nHighest mark in vector: " << marks[1] << '\\n';
    // Do not access highest after possible reallocation.
}
