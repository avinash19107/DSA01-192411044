#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;
constexpr double DA_RATE = 0.42;

class Staff {
protected:
    string name;
    int id;
    double basic;
public:
    Staff(string n, int i, double b) : name(n), id(i), basic(b) {}
    virtual double pay() const = 0;
    virtual void display() const {
        cout << "Name: " << name << '\n'
             << "ID: " << id << '\n'
             << "Pay: " << pay() << "\n\n";
    }
    virtual ~Staff() = default;
};

class Professor : public Staff {
    double research;
public:
    Professor(string n, int i, double b, double r)
        : Staff(n, i, b), research(r) {}
    double pay() const override { return basic + basic * DA_RATE + research; }
};

class LabAssistant : public Staff {
public:
    LabAssistant(string n, int i, double b) : Staff(n, i, b) {}
    double pay() const override { return basic + basic * DA_RATE; }
};

class GuestFaculty : public Staff {
    double hours, rate;
public:
    GuestFaculty(string n, int i, double h, double r)
        : Staff(n, i, 0), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
};

int main() {
    vector<unique_ptr<Staff>> employees;
    employees.push_back(make_unique<Professor>("Anita", 101, 50000, 10000));
    employees.push_back(make_unique<LabAssistant>("Rahul", 102, 30000));
    employees.push_back(make_unique<GuestFaculty>("Kiran", 103, 40, 800));
    cout << "COLLEGE PAYROLL SYSTEM\n\n";
    for (const auto& employee : employees) employee->display();
    cout << "Total staff: " << employees.size() << '\n';
}