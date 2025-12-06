#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <string_view>
#include <ranges>
#include <algorithm>
#include <numeric>
#include <print>
#include <charconv> 

template <typename T>
[[nodiscard]] T solve(int argc) {
    std::string filename = argc > 1 ? "input" : "example";
    std::ifstream file(filename);
    std::string line;

    std::vector<std::string> lines;
    lines.reserve(1000);

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    // T n = lines.size();
    using Op = std::function<T(T, T)>;
    
    auto operations = lines.back()
        | std::views::split(' ')
        | std::views::filter([](auto&& rng) { return !rng.empty(); }) 
        | std::views::transform([](auto&& rng) -> Op {
            std::string_view token(rng.begin(), rng.end());
            if (token == "*") return std::multiplies<T>{};
            return std::plus<T>{};
        })
        | std::ranges::to<std::vector>();

    std::vector<T> values(lines[0].size());
    
    for (T i = 0; i < lines.size() - 1; i++) {
        std::string& cur = lines[i];
        for (T k = 0; k < values.size(); k++) {

        }
    }
}

int main(int argc, char*[]) {
    std::cout << solve<std::uint64_t>(argc) << std::endl;
}