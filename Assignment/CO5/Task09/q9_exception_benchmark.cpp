#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <stdexcept>
using namespace std; using namespace chrono;
volatile double resultSink=0.0;
struct Result { bool valid; double amount; };
Result validateReturn(double a){if(a<0||a>1000000)return{false,0};return{true,a};}
double validateException(double a){if(a<0)throw invalid_argument("Negative bill");if(a>1000000)throw out_of_range("Bill too large");return a;}
double runReturn(const vector<double>& v){double s=0;for(double a:v){Result r=validateReturn(a);if(r.valid)s+=r.amount;}return s;}
double runException(const vector<double>& v){double s=0;for(double a:v){try{s+=validateException(a);}catch(const exception&){} }return s;}
int main(){
    const int N=1000000; const int rates[]={0,1,50};
    cout<<fixed<<setprecision(3)<<"EXCEPTIONS VS RETURN CODES\n";
    for(int p:rates){
        vector<double> v;v.reserve(N);int bad=N*p/100;
        for(int i=0;i<N;++i)v.push_back(i<bad?-100:500+(i%100));
        auto s1=steady_clock::now();double a=runReturn(v);auto e1=steady_clock::now();
        auto s2=steady_clock::now();double b=runException(v);auto e2=steady_clock::now();
        resultSink=a+b;
        cout<<"\nInvalid bills: "<<p<<"%\nReturn-code total: "<<a<<"\nException total:   "<<b
            <<"\nReturn-code time:  "<<duration<double,milli>(e1-s1).count()<<" ms"
            <<"\nException time:    "<<duration<double,milli>(e2-s2).count()<<" ms\n";
    }
}