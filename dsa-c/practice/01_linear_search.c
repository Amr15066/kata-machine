// Linear Search: scan array for needle, return true/false
// Teaches: arrays, loops, function signatures
//
// Implement: Walk through every element. Return true if found.
// Time complexity: O(n)
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

bool linear_search(int* arr, int len, int needle) {
    // TODO: implement linear search
    return false;
}

int main(void) {
    int arr[] = {1, 3, 4, 69, 71, 81, 90, 99, 420, 1337, 69420};
    int len = sizeof(arr) / sizeof(arr[0]);

    assert(linear_search(arr, len, 69) == true);
    assert(linear_search(arr, len, 1336) == false);
    assert(linear_search(arr, len, 69420) == true);
    assert(linear_search(arr, len, 69421) == false);
    assert(linear_search(arr, len, 1) == true);
    assert(linear_search(arr, len, 0) == false);

    printf("All linear search tests passed!\n");
    return 0;
}
