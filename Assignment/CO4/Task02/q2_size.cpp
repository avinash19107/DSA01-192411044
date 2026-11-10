#include <iostream>
using namespace std;
struct Person { int id; };
struct StudentVirtual : virtual Person { double cgpa; };
struct StaffVirtual : virtual Person { double salary; };
struct TeachingAssistantVirtual : StudentVirtual, StaffVirtual { int hours; };
struct StudentNormal : Person { double cgpa; };
struct StaffNormal : Person { double salary; };
struct TeachingAssistantNormal : StudentNormal, StaffNormal { int hours; };
int main() {
    cout << "Virtual inheritance size: "
         << sizeof(TeachingAssistantVirtual) << " bytes\n";
    cout << "Non-virtual inheritance size: "
         << sizeof(TeachingAssistantNormal) << " bytes\n";
}