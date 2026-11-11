#include <iostream>
#include <vector>
#include <variant>
#include <memory>
#include <chrono>
#include <iomanip>
using namespace std; using namespace chrono;
volatile double resultSink=0.0;
class Bill { public: virtual double total() const=0; virtual ~Bill()=default; };
class OPBill:public Bill {double a,b;public:OPBill(double x,double y):a(x),b(y){}double total()const override{return a+b;}};
class IPBill:public Bill {double a,b;public:IPBill(double x,double y):a(x),b(y){}double total()const override{return a+b;}};
struct OPData{double a,b;}; struct IPData{double a,b;};
using BillVariant=variant<OPData,IPData>;
double variantTotal(const vector<BillVariant>& v){double s=0;for(const auto& b:v)s+=visit([](const auto& x){return x.a+x.b;},b);return s;}
double virtualTotal(const vector<unique_ptr<Bill>>& v){double s=0;for(const auto& b:v)s+=b->total();return s;}
int main(){
    const int N=1000000; vector<BillVariant> vv; vector<unique_ptr<Bill>> vb;
    vv.reserve(N);vb.reserve(N);
    for(int i=0;i<N;++i){double a=500+(i%100),b=1200+(i%50);
        if(i%2==0){vv.push_back(OPData{a,b});vb.push_back(make_unique<OPBill>(a,b));}
        else{vv.push_back(IPData{a,b});vb.push_back(make_unique<IPBill>(a,b));}}
    auto s1=steady_clock::now();double vt=variantTotal(vv);auto e1=steady_clock::now();
    auto s2=steady_clock::now();double pt=virtualTotal(vb);auto e2=steady_clock::now();
    resultSink=vt+pt;cout<<fixed<<setprecision(3)<<"VARIANT VS VIRTUAL FUNCTION\nBills: "<<N
      <<"\nVariant total: "<<vt<<"\nVirtual total: "<<pt
      <<"\nVariant time: "<<duration<double,milli>(e1-s1).count()<<" ms"
      <<"\nVirtual time: "<<duration<double,milli>(e2-s2).count()<<" ms"
      <<"\nTotals match: "<<boolalpha<<(vt==pt)<<'\n';
}