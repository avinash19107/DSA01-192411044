#include <iostream>
#include <cmath>
#include <iomanip>
#include <stdexcept>
using namespace std;
class Complex {
    double real,imag;
public:
    Complex():real(0),imag(0){}
    Complex(double r):real(r),imag(0){}
    Complex(double r,double i):real(r),imag(i){}
    Complex operator+(const Complex&o)const{return {real+o.real,imag+o.imag};}
    Complex operator-(const Complex&o)const{return {real-o.real,imag-o.imag};}
    Complex operator*(const Complex&o)const{return {real*o.real-imag*o.imag,real*o.imag+imag*o.real};}
    Complex operator/(const Complex&o)const{
        double d=o.real*o.real+o.imag*o.imag;
        if(d==0.0)throw domain_error("Division by zero impedance");
        return {(real*o.real+imag*o.imag)/d,(imag*o.real-real*o.imag)/d};
    }
    bool operator==(const Complex&o)const{return real==o.real&&imag==o.imag;}
    double magnitude()const{return sqrt(real*real+imag*imag);}
    friend ostream& operator<<(ostream&out,const Complex&c){
        out<<fixed<<setprecision(2)<<c.real;
        if(c.imag>=0)out<<" + "<<c.imag<<"j";else out<<" - "<<-c.imag<<"j";
        return out;
    }
};
Complex parallel(const Complex&a,const Complex&b){return (a*b)/(a+b);}
int main(){
    cout<<fixed<<setprecision(2);
    cout<<"SERIES RLC CIRCUIT\n";
    Complex resistor(10,0),inductor(0,5),capacitor(0,-2);
    Complex series=resistor+inductor+capacitor;
    cout<<"Resistor: "<<resistor<<'\n'<<"Inductor: "<<inductor<<'\n'<<"Capacitor: "<<capacitor<<'\n';
    cout<<"Series impedance: "<<series<<'\n'<<"Series magnitude: "<<series.magnitude()<<" ohms\n";
    cout<<"\nPARALLEL RLC CIRCUIT\n";
    Complex r(30,0),l(0,20),c(0,-10);
    Complex parallelRL=parallel(r,l),parallelRLC=parallel(parallelRL,c);
    cout<<"Resistor: "<<r<<'\n'<<"Inductor: "<<l<<'\n'<<"Capacitor: "<<c<<'\n';
    cout<<"Parallel impedance: "<<parallelRLC<<'\n'<<"Parallel magnitude: "<<parallelRLC.magnitude()<<" ohms\n";
    cout<<"\nDIVISION BY ZERO TEST\n";
    try{Complex a(10,5),zero(0,0);cout<<(a/zero)<<'\n';}
    catch(const domain_error&e){cout<<"Error: "<<e.what()<<'\n';}
    cout<<"\nEQUALITY TEST\n";Complex x(4,3),y(4,3);cout<<boolalpha<<"X equals Y: "<<(x==y)<<'\n';
}