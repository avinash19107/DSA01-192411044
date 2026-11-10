#include <iostream>
#include <vector>
#include <memory>
using namespace std;
class Shape {
public:
    virtual double area() const = 0;
    virtual void display() const = 0;
    virtual ~Shape() = default;
};
class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
    void display() const override { cout << "Circle area: " << area() << '\n'; }
};
class Rectangle : public Shape {
    double length, width;
public:
    Rectangle(double l, double w) : length(l), width(w) {}
    double area() const override { return length * width; }
    void display() const override { cout << "Rectangle area: " << area() << '\n'; }
};
int main() {
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(5));
    shapes.push_back(make_unique<Rectangle>(4, 6));
    cout << "ABSTRACT CLASS DEMONSTRATION\n";
    for (const auto& shape : shapes) shape->display();
}