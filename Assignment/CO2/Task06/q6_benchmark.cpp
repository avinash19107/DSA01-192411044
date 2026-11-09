#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;
inline int inlineFunction(int x) { return x * 2 + 1; }
__attribute__((noinline))
int normalFunction(int x) { return x * 2 + 1; }
int main() {
    const int N = 10000000;
    long long sum = 0;
    auto start1 = steady_clock::now();
    for (int i = 0; i < N; i++) sum += inlineFunction(i);
    auto end1 = steady_clock::now();
    auto start2 = steady_clock::now();
    for (int i = 0; i < N; i++) sum += normalFunction(i);
    auto end2 = steady_clock::now();
    cout << "Inline time: "
         << duration_cast<milliseconds>(end1 - start1).count() << " ms\\n";
    cout << "Normal function time: "
         << duration_cast<milliseconds>(end2 - start2).count() << " ms\\n";
    cout << "Checksum: " << sum << '\\n';
}
