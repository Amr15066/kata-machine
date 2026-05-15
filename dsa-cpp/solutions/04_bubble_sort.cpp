#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
void bubble_sort(std::vector<T>& values) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        for (std::size_t j = 0; j + 1 < values.size() - i; ++j) {
            if (values[j] > values[j + 1]) {
                std::swap(values[j], values[j + 1]);
            }
        }
    }
}

int main() {
    std::vector<int> data{9, 3, 7, 4, 69, 420, 42};
    const std::vector<int> expected{3, 4, 7, 9, 42, 69, 420};

    bubble_sort(data);
    assert(data == expected);

    std::cout << "04_bubble_sort passed\n";
    return 0;
}
