#include <iostream>
int main() { int i = 5; i = i++; std::cout << i << '\n'; int j = 5; int k = j++; int m =
    ++j; std::cout << k << ' ' << m << ' ' << j << '\n'; }
