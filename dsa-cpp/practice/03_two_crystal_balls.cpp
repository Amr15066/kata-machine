// Practice: jump search for the first breaking floor.
// Teaches square-root decomposition, std::vector<bool>, and boundary handling.
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

int two_crystal_balls(const std::vector<bool>& breaks) {
    // TODO: implement
    // Hint: jump by sqrt(n) until you find a breaking block, then linearly scan that range.
    (void)breaks;
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
