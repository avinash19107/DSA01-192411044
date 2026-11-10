#include <iomanip>
#include <iostream>
using namespace std;
class Money {
    long long paise;
public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}
    Money operator+(const Money& o) const { Money r; r.paise = paise + o.paise; return r; }
    Money operator-(const Money& o) const { Money r; r.paise = paise - o.paise; return r; }
    Money& operator+=(const Money& o) { paise += o.paise; return *this; }
    Money& operator-=(const Money& o) { paise -= o.paise; return *this; }
    bool operator==(const Money& o) const { return paise == o.paise; }
    bool operator<(const Money& o) const { return paise < o.paise; }
    friend ostream& operator<<(ostream& out, const Money& m) {
        long long v=m.paise; if(v<0){out<<"-Rs ";v=-v;} else out<<"Rs ";
        return out<<v/100<<'.'<<setw(2)<<setfill('0')<<v%100;
    }
    friend istream& operator>>(istream& in, Money& m) {
        long long r; int p; if(in>>r>>p) m.paise=r*100+p; return in;
    }
};
int main() {
    Money a(120,75), b(79,25);
    cout << a+b << '\n' << boolalpha << ((a+b)==Money(200)) << '\n';
    cout << "Paise carry: " << Money(0,75)+Money(0,50) << '\n';
    Money negative(10); negative -= Money(15);
    cout << "Negative: " << negative << '\n';
}