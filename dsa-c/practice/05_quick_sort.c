// Quick Sort: O(n log n) average, in-place partition sort
// Teaches: recursion, partitioning, Lomuto partition scheme
//
// Implement: Pick a pivot, partition array so smaller elements are left of pivot,
// then recurse on each half.
// Time complexity: O(n log n) average, O(n^2) worst case
#include <stdio.h>
#include <assert.h>

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int* arr, int lo, int hi) {
    // TODO: implement Lomuto partition
    // Hint: use arr[hi] as pivot, walk i from lo to hi-1
    return lo;
}

void quick_sort_impl(int* arr, int lo, int hi) {
    // TODO: implement recursive quick sort
}

void quick_sort(int* arr, int len) {
    if (len <= 1) return;
    quick_sort_impl(arr, 0, len - 1);
}

int main(void) {
    int arr[] = {9, 3, 7, 4, 69, 420, 42};
    int expected[] = {3, 4, 7, 9, 42, 69, 420};
    int len = sizeof(arr) / sizeof(arr[0]);

    quick_sort(arr, len);

    for (int i = 0; i < len; i++) {
        assert(arr[i] == expected[i]);
    }

    printf("All quick sort tests passed!\n");
    return 0;
}
