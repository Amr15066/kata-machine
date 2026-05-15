// Min Heap: array-based priority queue
// Teaches: implicit binary tree in array, heapify up/down, index math
//
// Implement: parent = (i-1)/2, left = 2i+1, right = 2i+2
// Insert: add to end, heapify up. Delete: swap root with last, heapify down.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    int* data;
    int length;
    int capacity;
} MinHeap;

void heap_init(MinHeap* h) {
    h->capacity = 16;
    h->length = 0;
    h->data = malloc(sizeof(int) * h->capacity);
}

void heap_insert(MinHeap* h, int value) {
    // TODO: add to end of array, then heapify up
}

int heap_delete(MinHeap* h) {
    // TODO: swap root with last element, shrink, heapify down
    // Return the minimum value
    assert(h->length > 0);
    return 0;
}

void heap_free(MinHeap* h) {
    free(h->data);
    h->data = NULL;
    h->length = 0;
}

int main(void) {
    MinHeap h;
    heap_init(&h);

    heap_insert(&h, 5);
    heap_insert(&h, 3);
    heap_insert(&h, 69);
    heap_insert(&h, 420);
    heap_insert(&h, 4);
    heap_insert(&h, 1);
    heap_insert(&h, 8);
    heap_insert(&h, 7);

    assert(h.length == 8);
    assert(heap_delete(&h) == 1);
    assert(heap_delete(&h) == 3);
    assert(heap_delete(&h) == 4);
    assert(heap_delete(&h) == 5);
    assert(h.length == 4);
    assert(heap_delete(&h) == 7);
    assert(heap_delete(&h) == 8);
    assert(heap_delete(&h) == 69);
    assert(heap_delete(&h) == 420);
    assert(h.length == 0);

    heap_free(&h);
    printf("All min heap tests passed!\n");
    return 0;
}
