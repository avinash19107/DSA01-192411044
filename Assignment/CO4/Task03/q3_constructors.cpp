#include <iostream>
#include <string>
using namespace std;
class Address {
    string city; int pin;
public:
    Address(string c, int p) : city(c), pin(p) { cout << "Address constructor\n"; }
    ~Address() { cout << "Address destructor\n"; }
    string getAddress() const { return city + "-" + to_string(pin); }
};
class Course {
    string courseName;
public:
    Course(string c) : courseName(c) { cout << "Course constructor\n"; }
    ~Course() { cout << "Course destructor\n"; }
    string getName() const { return courseName; }
};
class Person {
protected:
    string name; int age; Address home;
public:
    Person(string n, int a, string city, int pin)
        : name(n), age(a), home(city, pin) { cout << "Person constructor\n"; }
    virtual ~Person() { cout << "Person destructor\n"; }
};
class Student : virtual public Person {
protected:
    long long regNo; Course course;
public:
    Student(string n, int a, string city, int pin, long long reg, string courseName)
        : Person(n, a, city, pin), regNo(reg), course(courseName) {
        cout << "Student constructor\n";
    }
    ~Student() override { cout << "Student destructor\n"; }
    void displayStudent() const {
        cout << "Student: " << name << '\n' << "Register: " << regNo << '\n'
             << "Course: " << course.getName() << '\n'
             << "Address: " << home.getAddress() << '\n';
    }
};
class Staff : virtual public Person {
protected:
    string department;
public:
    Staff(string n, int a, string city, int pin, string dept)
        : Person(n, a, city, pin), department(dept) { cout << "Staff constructor\n"; }
    ~Staff() override { cout << "Staff destructor\n"; }
};
class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(string n, int a, string city, int pin, long long reg,
                      string courseName, string dept)
        : Person(n, a, city, pin),
          Student(n, a, city, pin, reg, courseName),
          Staff(n, a, city, pin, dept) {
        cout << "TeachingAssistant constructor\n";
    }
    ~TeachingAssistant() override { cout << "TeachingAssistant destructor\n"; }
};
int main() {
    cout << "--- STUDENT OBJECT ---\n";
    { Student s("Kavya", 19, "Salem", 636001, 192311001, "C++ Programming");
      s.displayStudent(); }
    cout << "\n--- STAFF OBJECT ---\n";
    { Staff s("Arun", 40, "Chennai", 600001, "CSE"); }
    cout << "\n--- TEACHING ASSISTANT OBJECT ---\n";
    { TeachingAssistant ta("Meena", 22, "Vijayawada", 520001,
                           192311002, "OOP", "Computer Science"); }
}