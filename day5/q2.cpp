#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <string_view>
#include <charconv>
#include <print>

template <typename T>
[[nodiscard]] T solve(int argc) {
    std::string filename = argc > 1 ? "input" : "example";
    std::ifstream file(filename);
    std::string line;

    T res = 0, a, b;
    std::vector<std::pair<T, T>> limits;
    limits.reserve(1000);

    // Insertion
    while (std::getline(file, line)) {
        // break on empty line
        if (line.empty()) break; 

        std::string_view view = line;
        auto pos = view.find('-');
        std::from_chars(view.data(), view.data() + pos, a);
        std::from_chars(view.data() + pos + 1, view.data() + view.size(), b);
        limits.push_back({a, b});
    }

    std::sort(limits.begin(), limits.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });

    std::vector<std::pair<T, T>> merged_limits;
    merged_limits.reserve(limits.size());

    merged_limits.push_back(limits[0]);
    for (T i = 1; i < limits.size(); i++) {
        auto& last = merged_limits.back();
        auto& cur = limits[i];

        if (last.second >= cur.first) {
            if (cur.second > last.second) {
                last.second = cur.second;
            }
        } else {
            merged_limits.push_back(cur);
        }
    }

    for (auto& lim: merged_limits) {
        res += lim.second - lim.first + 1;
    }

    return res;
}

int main(int argc, char*[]) {
    std::cout << solve<std::uint64_t>(argc) << std::endl;
}
