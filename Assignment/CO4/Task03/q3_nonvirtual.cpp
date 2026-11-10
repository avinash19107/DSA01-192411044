#include <iostream>
using namespace std;
class Person {
public:
    Person() { cout << "Person "; }
    ~Person() { cout << "~Person "; }
};
class Student : public Person {
public:
    Student() { cout << "Student "; }
    ~Student() { cout << "~Student "; }
};
class Staff : public Person {
public:
    Staff() { cout << "Staff "; }
    ~Staff() { cout << "~Staff "; }
};
class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant() { cout << "TA "; }
    ~TeachingAssistant() { cout << "~TA "; }
};
int main() {
    { TeachingAssistant ta; cout << "| "; }
    cout << '\n';
}