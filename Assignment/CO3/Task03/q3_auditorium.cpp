#include <iostream>
using namespace std;
class Event {
    int rows, seats, booked;
    bool** map;
public:
    Event(int r, int s) : rows(r), seats(s), booked(0), map(nullptr) {
        if (rows > 0) {
            map = new bool*[rows];
            for (int i = 0; i < rows; ++i) {
                map[i] = new bool[seats]{};
            }
        }
        cout << "Event created: " << rows << " x " << seats << '\n';
    }
    bool book(int r, int s) {
        if (!map || r < 0 || r >= rows || s < 0 || s >= seats || map[r][s])
            return false;
        map[r][s] = true; ++booked; return true;
    }
    bool cancel(int r, int s) {
        if (!map || r < 0 || r >= rows || s < 0 || s >= seats || !map[r][s])
            return false;
        map[r][s] = false; --booked; return true;
    }
    ~Event() {
        for (int i = 0; i < rows; ++i) delete[] map[i];
        delete[] map;
        cout << "Event closed. Booked seats: " << booked << '\n';
    }
};
int main() {
    { Event local(3, 4); cout << "Book seat: " << local.book(0, 0) << '\n';
      cout << "Book seat: " << local.book(0, 1) << '\n';
      cout << "Cancel seat: " << local.cancel(0, 1) << '\n'; }
    Event* heap = new Event(2, 2); heap->book(0, 0); delete heap;
    Event zero(0, 5);
    cout << "Booking attempt: " << zero.book(0, 0) << '\n';
}