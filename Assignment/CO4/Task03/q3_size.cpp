#include <iostream>
using namespace std;
class Person { protected: int id; };
class StudentVirtual : virtual public Person { double cgpa; };
class StaffVirtual : virtual public Person { double salary; };
class TeachingAssistantVirtual : public StudentVirtual, public StaffVirtual { int hours; };
class StudentNormal : public Person { double cgpa; };
class StaffNormal : public Person { double salary; };
class TeachingAssistantNormal : public StudentNormal, public StaffNormal { int hours; };
int main() {
    cout << "Virtual inheritance: " << sizeof(TeachingAssistantVirtual) << " bytes\n";
    cout << "Non-virtual inheritance: " << sizeof(TeachingAssistantNormal) << " bytes\n";
}