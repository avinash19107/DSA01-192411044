#include <iostream>
#include <string>
using namespace std;
class Employee {
private:
    int id; string name; double salary;
public:
    Employee(int id, string name, double salary) {
        this->id = id; this->name = name; this->salary = salary;
    }
    Employee& setSalary(double salary) { this->salary = salary; return *this; }
    Employee& setName(string name) { this->name = name; return *this; }
    void display() const {
        cout << "Employee ID: " << id << '\n'
             << "Name: " << name << '\n'
             << "Salary: " << salary << '\n';
    }
    void compareAddress() { cout << "Current object address: " << this << '\n'; }
};
int main() {
    Employee e1(101, "Anita", 35000);
    cout << "Original employee:\n"; e1.display();
    cout << "\nAfter method chaining:\n";
    e1.setName("Anita Sharma").setSalary(45000); e1.display();
    cout << "\nObject address:\n"; e1.compareAddress();
}