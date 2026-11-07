#include "core.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
 
struct Case
{
    const char *name;
    int zone, h, m;
    bool conc;
    long long expected;
};
// Parses a zone/hour text the way the gate does; returns false for invalid input
bool parseHour(const std::string &s, int &out)
{
    std::istringstream in(s);
    in >> out;
    return !in.fail() && in.eof() && out >= 0 && out <= 23;
}
int main()
{
    Case cases[] = {
        {"Inner off-peak", 0, 12, 0, false, 1000},
        {"Middle off-peak", 1, 12, 0, false, 2000},
        {"Outer off-peak", 2, 12, 0, false, 3000},
        {"Inner peak AM", 0, 9, 0, false, 1200},
        {"Middle peak PM", 1, 18, 0, false, 2400},
        {"Outer peak AM", 2, 8, 30, false, 3600},
        {"Boundary 08:00", 0, 8, 0, false, 1200},
        {"Boundary 09:59", 0, 9, 59, false, 1200},
        {"Boundary 10:00", 0, 10, 0, false, 1000},
        {"Boundary 17:00", 0, 17, 0, false, 1200},
        {"Boundary 19:59", 0, 19, 59, false, 1200},
        {"Boundary 20:00", 0, 20, 0, false, 1000},
        {"Concession off", 2, 12, 0, true, 1500},
        {"Concession peak", 2, 9, 0, true, 1800},
    };
    int pass = 0, total = 0;
    std::cout << "No  Case             Expected  Actual  Result\n";
    for (const Case &c : cases)
    {
        long long a = fare(static_cast<Zone>(c.zone), isPeak(c.h, c.m), c.conc);
        bool ok = (a == c.expected);
        ++total;
        pass += ok;
        std::cout << (total < 10 ? " " : "") << total << "  " << c.name
                  << std::string(17 - std::string(c.name).size(), ' ') << c.expected
                  << "      " << a << "    " << (ok ? "PASS" : "FAIL") << '\n';
    }
    // balance leaving exactly Rs 50
    bool b1 = canTravel(6000, 1000), b2 = canTravel(5999, 1000),
         b3 = canTravel(6000, 1001);
    std::cout << "Balance 6000, fare 1000 (leaves exactly 5000): "
              << (b1 ? "allowed" : "denied") << "  expected allowed "
              << (b1 ? "PASS" : "FAIL") << '\n';
    std::cout << "Balance 5999, fare 1000 (leaves 4999):          "
              << (b2 ? "allowed" : "denied") << "  expected denied  "
              << (!b2 ? "PASS" : "FAIL") << '\n';
    std::cout << "Balance 6000, fare 1001 (leaves 4999):          "
              << (b3 ? "allowed" : "denied") << "  expected denied  "
              << (!b3 ? "PASS" : "FAIL") << '\n';
    // invalid
    int zone = 7;
    bool badZone = !(zone >= 0 && zone <= 2);
    long long recharge = -200;
    bool badRecharge = recharge <= 0;
    int h;
    bool badHour = !parseHour("ab", h);
    std::cout << "Unknown zone 7 rejected:     " << (badZone ? "PASS" : "FAIL") << '\n'
              << "Negative recharge rejected:  " << (badRecharge ? "PASS" : "FAIL")
              << '\n'
              << "Hour 'ab' rejected:          " << (badHour ? "PASS" : "FAIL") << '\n'
              << "Hour '25' rejected:          "
              << (!parseHour("25", h) ? "PASS" : "FAIL") << '\n';
    // 5 journeys by hand: Inner 12:00=1000, Middle 09:00=2400, Outer 18:30=3600, Inner
    // 10:00=1000, Outer 20:00=3000 -> 11000
    struct J
    {
        int z, h, m;
    } js[] = {{0, 12, 0}, {1, 9, 0}, {2, 18, 30}, {0, 10, 0}, {2, 20, 0}};
    long long total5 = 0;
    for (auto j : js) total5 += fare(static_cast<Zone>(j.z), isPeak(j.h, j.m), false);
    std::cout << "Five-journey total: hand 11000, program " << total5 << "  "
              << (total5 == 11000 ? "PASS" : "FAIL") << '\n';
    std::cout << pass << "/" << total << " table cases passed\n";
}
