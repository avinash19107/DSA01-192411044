#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <algorithm>
using namespace std;
class Bill {
protected: string patient;
public:
    explicit Bill(string p) : patient(p) {}
    virtual double total() const = 0;
    virtual string type() const = 0;
    virtual void print() const { cout << type() << " | " << patient << " | Rs. " << total() << '\n'; }
    virtual ~Bill() = default;
};
class OutPatient : public Bill {
    double consultation, tests;
public:
    OutPatient(string p, double c, double t) : Bill(p), consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    string type() const override { return "OP"; }
};
class InPatient : public Bill {
    int days; double perDay, surgery;
public:
    InPatient(string p, int d, double rate, double s) : Bill(p), days(d), perDay(rate), surgery(s) {}
    double total() const override { return days * perDay + surgery; }
    string type() const override { return "IP"; }
};
class DayCareBill : public Bill {
    double price;
public:
    DayCareBill(string p, double v) : Bill(p), price(v) {}
    double total() const override { return price; }
    string type() const override { return "DayCare"; }
};
class EmergencyBill : public Bill {
    double base; int hours; double hourly;
public:
    EmergencyBill(string p, double b, int h, double r) : Bill(p), base(b), hours(h), hourly(r) {}
    double total() const override { return base + hours * hourly; }
    string type() const override { return "Emergency"; }
};
class Payer {
public:
    virtual double amountCovered(const Bill&) const = 0;
    virtual string name() const = 0;
    virtual ~Payer() = default;
};
class SelfPay : public Payer {
public: double amountCovered(const Bill& b) const override { return b.total(); }
    string name() const override { return "SelfPay"; }
};
class Insurance : public Payer {
    double limit, copay;
public:
    Insurance(double l, double c) : limit(l), copay(c) {}
    double amountCovered(const Bill& b) const override { return min(b.total() * (1.0 - copay / 100.0), limit); }
    string name() const override { return "Insurance"; }
};
class GovernmentScheme : public Payer {
    map<string, double> rates;
public:
    GovernmentScheme() { rates = {{"OP",1500},{"IP",40000},{"DayCare",20000},{"Emergency",10000}}; }
    double amountCovered(const Bill& b) const override {
        auto it = rates.find(b.type());
        if (it == rates.end()) throw runtime_error("Unknown package");
        return min(b.total(), it->second);
    }
    string name() const override { return "GovernmentScheme"; }
};
void process(const Bill& b, const Payer& p) { cout << p.name() << " covers Rs. " << p.amountCovered(b) << '\n'; }
int main() {
    vector<unique_ptr<Bill>> bills;
    bills.push_back(make_unique<OutPatient>("Ravi",500,1200));
    bills.push_back(make_unique<InPatient>("Meena",3,2500,40000));
    bills.push_back(make_unique<DayCareBill>("Anita",25000));
    bills.push_back(make_unique<EmergencyBill>("Rahul",5000,3,2000));
    SelfPay self; Insurance insurance(50000,20); GovernmentScheme govt;
    vector<const Payer*> payers = {&self,&insurance,&govt};
    cout << "HOSPITAL BILLING SYSTEM\n\n";
    for (const auto& b : bills) {
        b->print();
        for (const Payer* p : payers) process(*b,*p);
        cout << '\n';
    }
}