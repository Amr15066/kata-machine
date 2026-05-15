// Practice: quick sort using partitioning and recursion.
// Teaches templates, divide-and-conquer, and in-place partition logic.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
std::size_t partition(std::vector<T>& values, std::size_t low, std::size_t high) {
    // TODO: implement
    // Hint: choose a pivot, move smaller elements left, then return the pivot index.
    (void)values;
    (void)low;
    (void)high;
    return low;
}

template <typename T>
void quick_sort_impl(std::vector<T>& values, std::size_t low, std::size_t high) {
    // TODO: implement
    // Hint: stop on the base case, partition, then recurse on the subranges.
    (void)values;
    (void)low;
    (void)high;
}

template <typename T>
void quick_sort(std::vector<T>& values) {
    // TODO: implement
    // Hint: guard against an empty vector before calling the recursive helper.
    (void)values;
}

int main() {
    std::vector<int> data{9, 3, 7, 4, 69, 420, 42};
    const std::vector<int> expected{3, 4, 7, 9, 42, 69, 420};

    quick_sort(data);
    assert(data == expected);

    std::cout << "05_quick_sort passed\n";
    return 0;
}
