#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

int two_crystal_balls(const std::vector<bool>& breaks) {
    if (breaks.empty()) {
        return -1;
    }

    const std::size_t jump = static_cast<std::size_t>(std::sqrt(static_cast<double>(breaks.size())));
    std::size_t index = jump;

    while (index < breaks.size() && !breaks[index]) {
        index += jump;
    }

    std::size_t start = index >= jump ? index - jump : 0;
    std::size_t end = std::min(index, breaks.size() - 1);

    for (std::size_t i = start; i <= end; ++i) {
        if (breaks[i]) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

int main() {
    const int size = 10000;
    const int break_point = 6347;  // Deterministic so the test stays stable.
    std::vector<bool> data(size, false);

    for (int i = break_point; i < size; ++i) {
        data[static_cast<std::size_t>(i)] = true;
    }

    assert(two_crystal_balls(data) == break_point);
    assert(two_crystal_balls(std::vector<bool>(size, false)) == -1);

    std::cout << "03_two_crystal_balls passed\n";
    return 0;
}
