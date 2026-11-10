# CO4 Assignment 4 – Designing Reusable Class Hierarchies

This repository contains six task folders with C++ source files, concise task READMEs and available Kali Linux terminal screenshots.

## Compiler
GNU g++ using C++17.

## General build command
`g++ -std=c++17 -Wall -Wextra source.cpp -o program`

## AddressSanitizer build
`g++ -std=c++17 -Wall -Wextra -g -fsanitize=address -fno-omit-frame-pointer source.cpp -o program`

## Tasks
- Task01: College payroll class hierarchy and runtime polymorphism
- Task02: Diamond problem and virtual base classes
- Task03: Constructors, member objects and initialization order
- Task04: Derived-class pointers, virtual dispatch, slicing and virtual destructor
- Task05: The this pointer and method chaining
- Task06: Abstract classes and pure virtual functions

## Evidence
Screenshots are the terminal captures supplied during practical execution. The Q2 ambiguity example and Q3 initializer-order warning are intentional compiler-diagnostic demonstrations.
