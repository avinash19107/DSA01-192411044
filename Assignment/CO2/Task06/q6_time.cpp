#include <iostream>
using namespace std;
class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};
inline int minutesBetween(const Time& a, const Time& b) {
    int first = a.h * 60 + a.m, second = b.h * 60 + b.m;
    int difference = first - second;
    return difference < 0 ? -difference : difference;
}
inline bool earlier(const Time& a, const Time& b) {
    return a.h * 60 + a.m < b.h * 60 + b.m;
}
int main() {
    Time departure(9, 45), arrival(13, 10);
    cout << minutesBetween(departure, arrival) << ' '
         << boolalpha << earlier(arrival, departure) << '\\n';
    Time morning(11, 30), afternoon(12, 30);
    cout << minutesBetween(morning, afternoon) << ' '
         << earlier(morning, afternoon) << '\\n';
    Time same1(10, 15), same2(10, 15);
    cout << minutesBetween(same1, same2) << ' '
         << earlier(same1, same2) << '\\n';
}
