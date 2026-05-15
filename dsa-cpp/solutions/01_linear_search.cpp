#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
bool linear_search(const std::vector<T>& haystack, T needle) {
    // const reference avoids copying the whole vector.
    for (const T& value : haystack) {
        if (value == needle) {
            return true;
        }
    }
    return false;
}

int main() {
    const std::vector<int> data{1, 3, 4, 69, 71, 81, 90, 99, 420, 1337, 69420};

    assert(linear_search(data, 69));
    assert(linear_search(data, 69420));
    assert(!linear_search(data, 1336));

    std::cout << "01_linear_search passed\n";
    return 0;
}
