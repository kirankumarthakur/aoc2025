#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>

template <typename T>
[[nodiscard]] T solve(int argc) {
    std::string filename = argc > 1 ? "input" : "example";
    std::ifstream file(filename);
    std::string line;
    T res = 0;

    while (std::getline(file, line)) {
        // largest number you can make with a subsequence of length this
        T n = line.size(), count = 12;
        std::string st;
        st.reserve(count);

        for (T i = 0; i < n; ++i) {
            char cur = line[i];
            while (!st.empty() && st.back() < cur && (st.size() - 1 + (n - i)) >= count) {
                st.pop_back();
            }
            if (st.size() < count) {
                st.push_back(cur);
            }
        }
        res += std::stoull(st.substr(0, count));
    }

    return res;
}

int main(int argc, char*[]) {
    std::cout << solve<std::uint64_t>(argc) << std::endl;
}
