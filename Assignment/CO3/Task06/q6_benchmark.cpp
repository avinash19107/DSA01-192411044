#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
using namespace std; using namespace chrono;
class Text {
    char* data;
public:
    Text(const char*s=""){data=new char[strlen(s)+1];strcpy(data,s);}
    Text(const Text&o){data=new char[strlen(o.data)+1];strcpy(data,o.data);}
    Text& operator=(const Text&o){if(this!=&o){char*t=new char[strlen(o.data)+1];strcpy(t,o.data);delete[]data;data=t;}return *this;}
    ~Text(){delete[]data;}
    Text& operator+=(const Text&o){size_t n=strlen(data)+strlen(o.data)+1;char*t=new char[n];strcpy(t,data);strcat(t,o.data);delete[]data;data=t;return *this;}
    size_t length()const{return strlen(data);}
};
int main(){
    const int N=100000;Text custom,unit("x");
    auto s1=steady_clock::now();for(int i=0;i<N;++i)custom+=unit;auto e1=steady_clock::now();
    string standard;auto s2=steady_clock::now();for(int i=0;i<N;++i)standard+='x';auto e2=steady_clock::now();
    cout<<"Custom Text length: "<<custom.length()<<'\n';
    cout<<"Custom Text time: "<<duration_cast<milliseconds>(e1-s1).count()<<" ms\n";
    cout<<"std::string length: "<<standard.length()<<'\n';
    cout<<"std::string time: "<<duration_cast<milliseconds>(e2-s2).count()<<" ms\n";
}