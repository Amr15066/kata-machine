// Two Crystal Balls: find first true in sorted boolean array using sqrt(n) jumps
// Teaches: math.h sqrt, two-phase search
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

int two_crystal_balls(bool* breaks, int len) {
    int jump = (int)sqrt((double)len);
    if (jump < 1) jump = 1;

    int i = 0;
    for (; i < len; i += jump) {
        if (breaks[i]) break;
    }

    // Walk back one jump.
    i -= jump;
    if (i < 0) i = 0;

    for (int j = 0; j < jump && i < len; j++, i++) {
        if (breaks[i]) return i;
    }
    return -1;
}

int main() {
    int len = 10000;
    bool* arr = calloc((size_t)len, sizeof(bool));
    int break_point = 4321;
    for (int i = break_point; i < len; i++) arr[i] = true;
    assert(two_crystal_balls(arr, len) == break_point);
    free(arr);

    // Test with no break (all false).
    arr = calloc((size_t)len, sizeof(bool));
    assert(two_crystal_balls(arr, len) == -1);
    free(arr);

    printf("All two crystal balls tests passed!\n");
    return 0;
}
