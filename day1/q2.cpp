#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char* []) {
    const std::string filename = argc > 1 ? "input" : "example";
    std::ifstream input(filename);

    if (!input) {
        throw std::runtime_error("cannot open file " + filename);
    }

    std::vector<std::string> lines;
    std::string line;
    std::int32_t start = 50, res = 0;

    while (std::getline(input, line)) {
        bool isZero = !start;
        char direction = line[0];
        std::int32_t rot = std::stoi(line.substr(1));
        start += (direction == 'L') ? -rot : rot;
        if (start < 0 && !isZero) res++;
        res += abs(start) / 100;
        if (!start) res++;
        start = ((start % 100) + 100) % 100;
    }

    std::cout << res << std::endl;
}
