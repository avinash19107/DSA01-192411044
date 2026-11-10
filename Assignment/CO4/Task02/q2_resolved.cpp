#include <iostream>
#include <string>
using namespace std;
struct Person {
    string name;
    Person(string n = "University Member") : name(n) {}
};
struct Student : virtual Person { Student() : Person() {} };
struct Staff : virtual Person { Staff() : Person() {} };
struct TeachingAssistant : Student, Staff {
    TeachingAssistant() : Person("Kavya") {}
};
int main() {
    TeachingAssistant ta;
    cout << "Name: " << ta.name << '\n';
}