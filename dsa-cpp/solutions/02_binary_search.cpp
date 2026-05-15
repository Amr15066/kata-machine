#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
bool binary_search(const std::vector<T>& haystack, T needle) {
    std::size_t low = 0;
    std::size_t high = haystack.size();

    while (low < high) {
        const std::size_t middle = low + (high - low) / 2;
        if (haystack[middle] == needle) {
            return true;
        }
        if (haystack[middle] < needle) {
            low = middle + 1;
        } else {
            high = middle;
        }
    }

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
