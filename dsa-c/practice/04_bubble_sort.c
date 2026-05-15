// Bubble Sort: O(n^2) comparison sort, in-place
// Teaches: nested loops, swap idiom, mutation
//
// Implement: Repeatedly walk the array, swapping adjacent elements if out of order.
// Time complexity: O(n^2)
#include <stdio.h>
#include <assert.h>

void bubble_sort(int* arr, int len) {
    // TODO: implement bubble sort
}

int main(void) {
    int arr[] = {9, 3, 7, 4, 69, 420, 42};
    int expected[] = {3, 4, 7, 9, 42, 69, 420};
    int len = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, len);

    for (int i = 0; i < len; i++) {
        assert(arr[i] == expected[i]);
    }

    printf("All bubble sort tests passed!\n");
    return 0;
}
