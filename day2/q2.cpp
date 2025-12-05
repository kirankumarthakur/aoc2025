#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <ranges>
#include <string_view>
#include <charconv>
#include <utility>
#include <set>

template <typename T>
[[nodiscard]] T solve(int argc) {
    std::string filename = argc > 1 ? "input" : "example";
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);

    T upper = 1;

    auto data = line
        | std::views::split(',')
        | std::views::transform([&upper](auto&& rng) {
            std::string_view sv(rng.begin(), rng.end());
            T a, b;
            auto mid = sv.find('-');
            std::from_chars(sv.data(), sv.data() + mid, a);
            std::from_chars(sv.data() + mid + 1, sv.data() + sv.size(), b);
            upper = std::max({upper, a, b});
            return std::make_pair(a, b);
        })
        | std::ranges::to<std::vector<std::pair<T, T>>>();

    std::sort(data.begin(), data.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    std::cout << upper << std::endl;

    std::set<T> invalid;

    T cur = 1;
    while (true) {
        const std::string cur_str = std::to_string(cur);
        std::string acc;
        acc.reserve(50);
        acc += cur_str + cur_str;
        T tmp = std::stoll(acc);

        if (tmp > upper) break;

        while (tmp <= upper && tmp <= std::numeric_limits<T>::max()) {
            invalid.insert(tmp);
            acc += cur_str;
            tmp = std::stoll(acc);
        }
        cur++;
    }

    T res = 0, idx = 0;
    for (auto& it: invalid) {
        while (it > data[idx].second) {
            idx++;
        }
        if (it >= data[idx].first && it <= data[idx].second) {
            res += it;
        }
    }

    return res;
}

int main(int argc, char*[]) {
    std::cout << solve<std::int64_t>(argc) << std::endl;
}
