#include <iostream>
#include <string>
using namespace std;
struct Person { string name = "University Member"; };
struct Student : Person {};
struct Staff : Person {};
struct TeachingAssistant : Student, Staff {};
int main() {
    TeachingAssistant ta;
    cout << ta.name << '\n'; // Intentionally ambiguous: compile-time demonstration.
}