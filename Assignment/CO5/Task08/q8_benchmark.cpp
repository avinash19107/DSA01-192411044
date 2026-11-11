#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <iomanip>
using namespace std; using namespace chrono;
volatile double resultSink = 0.0;
class Bill { public: virtual double total() const = 0; virtual ~Bill() = default; };
class OutPatient : public Bill {
    double a,b;
public: OutPatient(double x,double y):a(x),b(y){} double total() const override{return a+b;}
};
class InPatient : public Bill {
    double a,b;
public: InPatient(double x,double y):a(x),b(y){} double total() const override{return a+b;}
};
struct BillRecord { int type; double first,second; };
double virtualTotal(const vector<unique_ptr<Bill>>& v) { double s=0; for(const auto& b:v)s+=b->total(); return s; }
double switchTotal(const vector<BillRecord>& v) {
    double s=0; for(const auto& b:v) switch(b.type) {
        case 0: s+=b.first+b.second; break;
        case 1: s+=b.first+b.second; break;
    } return s;
}
int main() {
    const int sizes[]={1000,1000000,10000000};
    cout<<fixed<<setprecision(3)<<"VIRTUAL FUNCTION VS SWITCH\n";
    for(int n:sizes) {
        vector<unique_ptr<Bill>> vb; vector<BillRecord> sb;
        vb.reserve(n); sb.reserve(n);
        for(int i=0;i<n;++i) {
            double a=500+(i%100), b=1200+(i%50);
            if(i%2==0){vb.push_back(make_unique<OutPatient>(a,b));sb.push_back({0,a,b});}
            else{vb.push_back(make_unique<InPatient>(a,b));sb.push_back({1,a,b});}
        }
        auto s1=steady_clock::now(); double vt=virtualTotal(vb); auto e1=steady_clock::now();
        auto s2=steady_clock::now(); double st=switchTotal(sb); auto e2=steady_clock::now();
        resultSink=vt+st;
        cout<<"\nBills: "<<n<<"\nVirtual total: "<<vt<<"\nSwitch total:  "<<st
            <<"\nVirtual time:  "<<duration<double,milli>(e1-s1).count()<<" ms"
            <<"\nSwitch time:   "<<duration<double,milli>(e2-s2).count()<<" ms\n";
    }
}