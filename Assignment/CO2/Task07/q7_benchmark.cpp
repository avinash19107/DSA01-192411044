#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;
const int SIZE = 10;
const int N = 5000000;
class ShiftArray {
    int data[SIZE]{};
    int count = 0;
public:
    __attribute__((noinline))
    void add(int value) {
        if (count == SIZE) {
            for (int i = 1; i < SIZE; i++) data[i - 1] = data[i];
            count = SIZE - 1;
        }
        data[count++] = value;
    }
    long long total() const {
        long long sum = 0;
        for (int i = 0; i < count; i++) sum += data[i];
        return sum;
    }
};
class CircularBuffer {
    int data[SIZE]{};
    int start = 0;
    int count = 0;
public:
    __attribute__((noinline))
    void add(int value) {
        if (count < SIZE) {
            data[(start + count) % SIZE] = value;
            count++;
        } else {
            data[start] = value;
            start = (start + 1) % SIZE;
        }
    }
    long long total() const {
        long long sum = 0;
        for (int i = 0; i < count; i++) sum += data[(start + i) % SIZE];
        return sum;
    }
};
int main() {
    ShiftArray original;
    CircularBuffer revised;
    auto start1 = steady_clock::now();
    for (int i = 0; i < N; i++) original.add(i);
    auto end1 = steady_clock::now();
    auto start2 = steady_clock::now();
    for (int i = 0; i < N; i++) revised.add(i);
    auto end2 = steady_clock::now();
    cout << "Original shifting array:\\nTime: "
         << duration_cast<milliseconds>(end1 - start1).count()
         << " ms\\nLast 10 total: " << original.total() << '\\n';
    cout << "\\nRevised circular buffer:\\nTime: "
         << duration_cast<milliseconds>(end2 - start2).count()
         << " ms\\nLast 10 total: " << revised.total() << '\\n';
}
