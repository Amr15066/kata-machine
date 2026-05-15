// Quick Sort: O(n log n) average, in-place partition sort
// Teaches: recursion, partitioning, Lomuto partition scheme
#include <stdio.h>
#include <assert.h>

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int* arr, int lo, int hi) {
    int pivot = arr[hi];
    int idx = lo;

    for (int i = lo; i < hi; i++) {
        if (arr[i] <= pivot) {
            swap(&arr[i], &arr[idx]);
            idx++;
        }
    }
    swap(&arr[idx], &arr[hi]);
    return idx;
}

void quick_sort_impl(int* arr, int lo, int hi) {
    if (lo >= hi) return;

    int pivot_idx = partition(arr, lo, hi);
    quick_sort_impl(arr, lo, pivot_idx - 1);
    quick_sort_impl(arr, pivot_idx + 1, hi);
}

void quick_sort(int* arr, int len) {
    if (len <= 1) return;
    quick_sort_impl(arr, 0, len - 1);
}

int main() {
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
