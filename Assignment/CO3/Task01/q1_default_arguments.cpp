#include <iostream>
#include <string>
using namespace std;
class Book {
    string title, author;
    int copies;
public:
    Book(string t = "Unknown", string a = "Unknown", int c = 0)
        : title(t), author(a), copies(c) {}
    void display() const {
        cout << title << " | " << author << " | " << copies << '\n';
    }
};
int main() {
    Book a, b("The C++ Programming Language"), c("Clean Code", "Robert Martin", 5);
    a.display(); b.display(); c.display();
}