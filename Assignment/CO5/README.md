# DSA01 – Assignment 5 (CO5)

**Reliable Software with Runtime Polymorphism and Exceptions**

Task-wise C++ source, concise task READMEs, and available terminal screenshots.

## Build commands
Standard:
`g++ -std=c++17 -Wall -Wextra source.cpp -o program`

Optimized benchmark:
`g++ -std=c++17 -O2 -Wall -Wextra source.cpp -o program`

AddressSanitizer:
`g++ -std=c++17 -Wall -Wextra -g -fsanitize=address -fno-omit-frame-pointer source.cpp -o program`

## Tasks
Task01 polymorphic hierarchy and pseudocode; Task02 runtime binding/vtable/destructor; Task03 payer hierarchy; Task04 exception strategy; Task05 stack unwinding/rethrowing; Task06 polymorphic implementation; Task07 error handling; Task08 virtual vs switch; Task09 exceptions vs return codes; Task10 variant; Task11 extension; Task12 RAII and sanitizer.

## Important submission details
Create the repository as `DSA01-<RegisterNumber>-Assignment5`. Fill student identity and repository link in the report. Add one progressive Git commit per task. Screenshots included here are the captures supplied during the practical work. The additional B4.2 sanitizer test and the 10-million variant benchmark are included as source files but need their own actual run evidence. The PDF also asks for B2 tests of `std::stod` invalid text and top-level `catch(...)`, and an `std::optional` alternative for B2/B3 analysis; these are listed as completion checks in the report.
