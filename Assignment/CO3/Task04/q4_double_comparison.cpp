#include <iostream>
#include <iomanip>
using namespace std;
int main() {
    const int N=1000000; double d=0;
    for(int i=0;i<N;++i) d+=0.01;
    long long paise=0; for(int i=0;i<N;++i) paise+=1;
    cout<<fixed<<setprecision(10);
    cout<<"Double result: "<<d<<'\n';
    cout<<"Integer paise result: "<<paise/100.0<<'\n';
    cout<<"Expected result: 10000.00\n";
}