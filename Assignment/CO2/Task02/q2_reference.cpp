#include <iostream>
using namespace std;
int& highestMark(int marks[], int size) {
    int maxIndex = 0;
    for (int i = 1; i < size; i++)
        if (marks[i] > marks[maxIndex]) maxIndex = i;
    return marks[maxIndex];
}
int main() {
    int marks[] = {75, 92, 85, 88, 79};
    cout << "Highest mark: " << highestMark(marks, 5) << '\\n';
    highestMark(marks, 5) += 2;
    cout << "After moderation: " << highestMark(marks, 5) << '\\n';
}
