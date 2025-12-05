#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

template <typename T>
[[nodiscard]] T solve(int argc) {
    std::string filename = argc > 1 ? "input" : "example";
    std::ifstream file(filename);
    std::string line;
    T res = 0;

    std::vector<std::string> grid;
    while (std::getline(file, line)) {
        grid.push_back(line);
    }

    const int dirs[][2] = {
        {0, 1}, {0, -1},
        {1, 0}, {-1, 0},
        {1, 1}, {1, -1},
        {-1, 1}, {-1, -1}
    };

    T m = grid.size();
    T n = grid[0].size();
    for (T i = 0; i < m; i++) {
        for (T k = 0; k < n; k++) {
            if (grid[i][k] == '@') {
                T count = 0;
                for (auto& dir: dirs) {
                    T y = i + dir[0];
                    T x = k + dir[1];

                    if (y >= 0 && y < n && x >= 0 && x <= n) {
                        if (grid[y][x] == '@') count++;
                    }
                }
                if (count < 4) res++;
            }
        }
    }

    return res;
}

int main(int argc, char*[]) {
    std::cout << solve<std::uint64_t>(argc) << std::endl;
}
