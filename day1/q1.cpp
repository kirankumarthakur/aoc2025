#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char* argv[]) {
    const std::string filename = argc > 1 ? "input" : "example";
    std::ifstream input(filename);

    if (!input) {
        throw std::runtime_error("cannot open file " + filename);
    }

    std::vector<std::string> lines;
    std::string line;
    std::int32_t start = 50, res = 0;

    while (std::getline(input, line)) {
        char direction = line[0];
        std::int32_t rot = std::stoi(line.substr(1));
        if (direction == 'R') {
            start = (start + rot) % 100;
            res += (start == 0);
        } else {
            start = (start + 100 - rot) % 100;
            res += (start == 0);
        }
    }

    std::cout << res << std::endl;
}
