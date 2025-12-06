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

    T n = lines.size();
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

    auto values = lines
        | std::views::take(n - 1)
        | std::views::transform([](const std::string& s) {
            return s
                | std::views::split(' ')
                | std::views::filter([](auto&& rng) { return !rng.empty(); }) 
                | std::views::transform([](auto&& rng) {
                    T val{}; 
                    auto* ptr = &*rng.begin();
                    std::from_chars(ptr, ptr + std::ranges::distance(rng), val);
                    return val;
                })
                | std::ranges::to<std::vector<T>>();
        });

    auto res_arr = std::ranges::fold_left_first(
        values,
        [&operations](std::vector<T> acc, const std::vector<T>& row) {
            for (size_t i = 0; i < acc.size(); i++) {
                acc[i] = operations[i % operations.size()](acc[i], row[i]);
            }
            return std::move(acc);
        }
    );

    return std::reduce(res_arr->begin(), res_arr->end());
}

int main(int argc, char*[]) {
    std::cout << solve<std::uint64_t>(argc) << std::endl;
}