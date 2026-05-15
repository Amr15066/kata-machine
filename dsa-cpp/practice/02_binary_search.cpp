// Practice: binary search on sorted data.
// Teaches templates, index arithmetic, and loop invariants.
#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
bool binary_search(const std::vector<T>& haystack, T needle) {
    // TODO: implement
    // Hint: keep low/high bounds and shrink the search space around the middle.
    (void)haystack;
    (void)needle;
    return false;
}

int main() {
    const std::vector<int> data{1, 3, 4, 69, 71, 81, 90, 99, 420, 1337, 69420};

    assert(binary_search(data, 1));
    assert(binary_search(data, 420));
    assert(!binary_search(data, 70));

    std::cout << "02_binary_search passed\n";
    return 0;
}
