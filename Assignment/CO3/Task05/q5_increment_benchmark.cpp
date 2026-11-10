#include <iostream>
#include <chrono>
using namespace std; using namespace chrono;
class Counter {
    long long value;
public:
    Counter():value(0){}
    Counter& operator++(){++value;return *this;}
    Counter operator++(int){Counter old=*this;++value;return old;}
    long long get()const{return value;}
};
int main(){
    const int N=10000000;
    Counter prefix; auto s1=steady_clock::now();
    for(int i=0;i<N;++i)++prefix; auto e1=steady_clock::now();
    Counter postfix; auto s2=steady_clock::now();
    for(int i=0;i<N;++i)postfix++; auto e2=steady_clock::now();
    cout<<"Prefix count: "<<prefix.get()<<'\n';
    cout<<"Prefix time: "<<duration_cast<milliseconds>(e1-s1).count()<<" ms\n";
    cout<<"Postfix count: "<<postfix.get()<<'\n';
    cout<<"Postfix time: "<<duration_cast<milliseconds>(e2-s2).count()<<" ms\n";
}