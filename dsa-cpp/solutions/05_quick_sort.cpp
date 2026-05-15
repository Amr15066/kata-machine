#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
std::size_t partition(std::vector<T>& values, std::size_t low, std::size_t high) {
    const T pivot = values[high];
    std::size_t i = low;

    for (std::size_t j = low; j < high; ++j) {
        if (values[j] <= pivot) {
            std::swap(values[i], values[j]);
            ++i;
        }
    }

    std::swap(values[i], values[high]);
    return i;
}

template <typename T>
void quick_sort_impl(std::vector<T>& values, std::size_t low, std::size_t high) {
    if (low >= high) {
        return;
    }

    const std::size_t pivot_index = partition(values, low, high);
    if (pivot_index > 0) {
        quick_sort_impl(values, low, pivot_index - 1);
    }
    quick_sort_impl(values, pivot_index + 1, high);
}

template <typename T>
void quick_sort(std::vector<T>& values) {
    if (!values.empty()) {
        quick_sort_impl(values, 0, values.size() - 1);
    }
}

int main() {
    std::vector<int> data{9, 3, 7, 4, 69, 420, 42};
    const std::vector<int> expected{3, 4, 7, 9, 42, 69, 420};

    quick_sort(data);
    assert(data == expected);

    std::cout << "05_quick_sort passed\n";
    return 0;
}
