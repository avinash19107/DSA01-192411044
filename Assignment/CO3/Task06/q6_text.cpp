#include <iostream>
#include <cstring>
using namespace std;
class Text {
    char* data; static int copyCount;
public:
    Text(const char* str=""){data=new char[strlen(str)+1];strcpy(data,str);}
    Text(const Text& o){data=new char[strlen(o.data)+1];strcpy(data,o.data);++copyCount;cout<<"Copy constructor called\n";}
    Text& operator=(const Text& o){
        if(this!=&o){char* t=new char[strlen(o.data)+1];strcpy(t,o.data);delete[] data;data=t;++copyCount;}
        return *this;
    }
    ~Text(){delete[] data;}
    Text operator+(const Text& o)const{
        size_t n=strlen(data)+strlen(o.data)+1;char* t=new char[n];
        strcpy(t,data);strcat(t,o.data);Text result(t);delete[] t;return result;
    }
    bool operator==(const Text&o)const{return strcmp(data,o.data)==0;}
    bool operator!=(const Text&o)const{return !(*this==o);}
    friend ostream& operator<<(ostream& out,const Text&t){return out<<t.data;}
    static void resetCopies(){copyCount=0;}
    static int getCopies(){return copyCount;}
};
int Text::copyCount=0;
int main(){
    Text a("Hello "),b("World"),c("!");
    cout<<"Text A: "<<a<<'\n'<<"Text B: "<<b<<'\n';
    Text result=a+b+c;cout<<"Concatenated: "<<result<<'\n';
    cout<<boolalpha<<"A == B: "<<(a==b)<<'\n'<<"A != B: "<<(a!=b)<<'\n';
    Text empty;cout<<"Empty text: ["<<empty<<"]\n";
    Text longMessage("This is a long SMS gateway message.");
    cout<<"Long message: "<<longMessage<<'\n';
    empty=empty;cout<<"After self-assignment: ["<<empty<<"]\n";
    cout<<"\nCopy constructor test:\n";
    Text original("SMS");Text::resetCopies();Text copied=original;
    cout<<"Original: "<<original<<'\n'<<"Copied: "<<copied<<'\n';
    cout<<"Copies made: "<<Text::getCopies()<<'\n';
}