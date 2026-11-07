#include <iostream>
#include <string>
int main()
{
    std::string line;
    while (std::getline(std::cin, line)) {
        try {
            size_t pos; int v = std::stoi(line, &pos);
            if (pos != line.size()) throw std::invalid_argument("trailing");
            std::cout << "ok " << v << '\n';
        } catch (const std::exception&) { std::cout << "bad line: '" << line << "'\n"; }
    }
}
