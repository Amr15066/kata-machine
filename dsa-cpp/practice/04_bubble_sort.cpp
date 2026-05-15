// Practice: bubble sort for an in-place array.
// Teaches templates, nested loops, and std::swap.
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
void bubble_sort(std::vector<T>& values) {
    // TODO: implement
    // Hint: repeatedly bubble the largest remaining value to the end.
    (void)values;
}

int main() {
    std::vector<int> data{9, 3, 7, 4, 69, 420, 42};
    const std::vector<int> expected{3, 4, 7, 9, 42, 69, 420};

    bubble_sort(data);
    assert(data == expected);

    std::cout << "04_bubble_sort passed\n";
    return 0;
}
