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
    T cur = 1;
    T idx = 0;
    T width = 10;
    T res = 0;
    std::cout << upper << std::endl;
    T tmp = cur * width + cur;
    while (tmp <= upper && tmp <= std::numeric_limits<T>::max()) {
        while (tmp > data[idx].second) {
            idx++;
        }

        if (tmp >= data[idx].first && tmp <= data[idx].second) {
            res += tmp;
        }

        cur++;

        if (cur == width) {
            width *= 10;
        }

        tmp = cur * width + cur;
    }

    return res;
}

int main(int argc, char*[]) {
    std::cout << solve<std::int64_t>(argc) << std::endl;
}
