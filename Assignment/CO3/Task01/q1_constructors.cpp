#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Book {
    string title, author;
    int copies;
public:
    Book() : Book("Empty", "Unknown", 0) {}
    explicit Book(string t) : Book(t, "Unknown", 0) {}
    Book(string t, string a, int c)
        : title(t), author(a), copies(c) {
        if (c < 0) throw invalid_argument("Invalid copies");
    }
    void display() const {
        cout << "Title: " << title << "\nAuthor: " << author
             << "\nCopies: " << copies << "\n";
    }
};
int main() {
    Book empty;
    Book titled("The C++ Programming Language");
    Book full("Clean Code", "Robert Martin", 5);
    cout << "Default Constructor:\n"; empty.display();
    cout << "\nTitle Constructor:\n"; titled.display();
    cout << "\nParameterized Constructor:\n"; full.display();
    try { Book invalid("Bad Book", "Unknown", -1); }
    catch (const invalid_argument& e) { cout << "\nError: " << e.what() << '\n'; }
}