// Binary Search: O(log n) search on sorted array
// Teaches: while loops, integer overflow-safe midpoint, comparison logic
//
// Implement: Use two pointers (lo, hi). Compute mid, compare, halve the range.
// Time complexity: O(log n)
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

bool binary_search(int* arr, int len, int needle) {
    // TODO: implement binary search
    // Hint: use half-open range [lo, hi)
    return false;
}

int main(void) {
    int arr[] = {1, 3, 4, 69, 71, 81, 90, 99, 420, 1337, 69420};
    int len = sizeof(arr) / sizeof(arr[0]);

    assert(binary_search(arr, len, 69) == true);
    assert(binary_search(arr, len, 1336) == false);
    assert(binary_search(arr, len, 69420) == true);
    assert(binary_search(arr, len, 69421) == false);
    assert(binary_search(arr, len, 1) == true);
    assert(binary_search(arr, len, 0) == false);

    printf("All binary search tests passed!\n");
    return 0;
}
