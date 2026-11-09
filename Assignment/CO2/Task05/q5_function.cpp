#include <iostream>
#include <string>
using namespace std;
class BusTicket {
    static int issued;
    static const int CAPACITY = 5;
    int seat;
    string name;
public:
    explicit BusTicket(const string& n) : seat(0), name(n) {
        if (issued < CAPACITY) seat = ++issued;
    }
    static int count() { return issued; }
    void print() const {
        cout << name << ": ";
        if (seat == 0) cout << "Waiting\\n";
        else cout << "Seat " << seat << '\\n';
    }
};
int BusTicket::issued = 0;
void createTickets() {
    BusTicket tickets[3] = {BusTicket("Asha"), BusTicket("Bala"),
                            BusTicket("Chitra")};
    for (const auto& ticket : tickets) ticket.print();
    cout << "Total issued: " << BusTicket::count() << '\\n';
}
int main() {
    cout << "First function call:\\n"; createTickets();
    cout << "\\nSecond function call:\\n"; createTickets();
}
