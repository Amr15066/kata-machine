// Two Crystal Balls: find first true in sorted boolean array using sqrt(n) jumps
// Teaches: math.h sqrt, two-phase search
//
// Implement: Jump by sqrt(n) to find the region, then linear scan back.
// Time complexity: O(sqrt(n))
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

int two_crystal_balls(bool* breaks, int len) {
    // TODO: implement two crystal balls
    // Hint: jump = (int)sqrt((double)len)
    return -1;
}

int main(void) {
    int len = 10000;
    bool* arr = calloc(len, sizeof(bool));
    int break_point = 7321;
    for (int i = break_point; i < len; i++) arr[i] = true;
    assert(two_crystal_balls(arr, len) == break_point);
    free(arr);

    arr = calloc(len, sizeof(bool));
    assert(two_crystal_balls(arr, len) == -1);
    free(arr);

    printf("All two crystal balls tests passed!\n");
    return 0;
}
