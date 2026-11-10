#include <iostream>
#include <string>
using namespace std;
class Prescription {
    int n;
    string* medicines;
public:
    explicit Prescription(int count) : n(count), medicines(new string[count]) {}
    ~Prescription() { delete[] medicines; }
    void set(int i, const string& m) { medicines[i] = m; }
    string get(int i) const { return medicines[i]; }
};
int main() {
    Prescription p(2);
    p.set(0, "Paracetamol"); p.set(1, "Cetirizine");
    Prescription q = p; // Shallow copy: both objects own the same array.
    cout << "Original: " << p.get(0) << ' ' << p.get(1) << '\n';
    cout << "Copy: " << q.get(0) << ' ' << q.get(1) << '\n';
}