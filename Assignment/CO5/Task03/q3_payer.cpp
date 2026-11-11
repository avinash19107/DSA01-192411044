#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
class Bill {
protected: string patient;
public:
    explicit Bill(string p) : patient(p) {}
    virtual double total() const = 0;
    virtual string type() const = 0;
    string getPatient() const { return patient; }
    virtual ~Bill() = default;
};
class OutPatient : public Bill {
    double consultation, tests;
public:
    OutPatient(string p, double c, double t)
        : Bill(p), consultation(c), tests(t) {}
    double total() const override { return consultation + tests; }
    string type() const override { return "OP"; }
};
class InPatient : public Bill {
    int days; double perDay, surgery;
public:
    InPatient(string p, int d, double rate, double s)
        : Bill(p), days(d), perDay(rate), surgery(s) {}
    double total() const override { return days * perDay + surgery; }
    string type() const override { return "IP"; }
};
class Payer {
public:
    virtual double amountCovered(const Bill& bill) const = 0;
    virtual string name() const = 0;
    virtual ~Payer() = default;
};
class SelfPay : public Payer {
public:
    double amountCovered(const Bill& b) const override { return b.total(); }
    string name() const override { return "Self Pay"; }
};
class Insurance : public Payer {
    double coverLimit, copayPercent;
public:
    Insurance(double limit, double copay) : coverLimit(limit), copayPercent(copay) {}
    double amountCovered(const Bill& b) const override {
        return min(b.total() * (1.0 - copayPercent / 100.0), coverLimit);
    }
    string name() const override { return "Insurance"; }
};
class GovernmentScheme : public Payer {
    map<string, double> packageRates;
public:
    GovernmentScheme() { packageRates["OP"] = 1500; packageRates["IP"] = 40000; }
    double amountCovered(const Bill& b) const override {
        auto it = packageRates.find(b.type());
        if (it == packageRates.end()) return 0;
        return min(b.total(), it->second);
    }
    string name() const override { return "Government Scheme"; }
};
class CorporatePayer : public Payer {
    double percent;
public:
    explicit CorporatePayer(double p) : percent(p) {}
    double amountCovered(const Bill& b) const override { return b.total() * percent / 100.0; }
    string name() const override { return "Corporate Tie-up"; }
};
void display(const Bill& b, const Payer& p) {
    cout << p.name() << " covers Rs. " << p.amountCovered(b) << '\n';
}
int main() {
    OutPatient op("Ravi", 500, 1200);
    InPatient ip("Meena", 3, 2500, 40000);
    SelfPay self; Insurance insurance(50000, 20); GovernmentScheme govt; CorporatePayer corp(80);
    cout << "OUT-PATIENT BILL: Rs. " << op.total() << '\n';
    display(op, self); display(op, insurance); display(op, govt); display(op, corp);
    cout << "\nIN-PATIENT BILL: Rs. " << ip.total() << '\n';
    display(ip, self); display(ip, insurance); display(ip, govt); display(ip, corp);
}