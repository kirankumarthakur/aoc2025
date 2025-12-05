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

    std::vector<T> fresh;
    fresh.reserve(1000);

    while (std::getline(file, line)) {
        std::from_chars(line.data(), line.data() + line.size(), a);
        fresh.push_back(a);
    }

    std::sort(fresh.begin(), fresh.end());
    T idx = 0;
    for (T i = 0; i < fresh.size(); i++) {
        while (idx + 1 < merged_limits.size() && fresh[i] > merged_limits[idx].second) {
            idx++;
        }

        if (fresh[i] >= merged_limits[idx].first && fresh[i] <= merged_limits[idx].second) {
            res++;
        }
    }

    return res;
}

int main(int argc, char*[]) {
    std::cout << solve<std::uint64_t>(argc) << std::endl;
}
