#include <iostream>
using namespace std;
class Time {
    int h,m,s;
public:
    Time(int hh=0,int mm=0,int ss=0):h(hh),m(mm),s(ss){}
    Time& operator++(){if(++s==60){s=0;if(++m==60){m=0;++h;}}return *this;}
    Time operator++(int){Time old=*this;++(*this);return old;}
    bool operator==(const Time&o)const{return h==o.h&&m==o.m&&s==o.s;}
    bool operator<(const Time&o)const{
        if(h!=o.h)return h<o.h;if(m!=o.m)return m<o.m;return s<o.s;
    }
    void display()const{cout<<h<<':'<<(m<10?"0":"")<<m<<':'<<(s<10?"0":"")<<s<<'\n';}
};
int main(){
    Time t(0,59,59);cout<<"Before increment: ";t.display();++t;
    cout<<"After increment: ";t.display();
    Time a(1,0,0),b(1,0,1);cout<<boolalpha<<"Equal: "<<(t==a)<<'\n';
    cout<<"Less than: "<<(a<b)<<'\n';
}