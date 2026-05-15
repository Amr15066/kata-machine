// Min Heap: array-based priority queue
// Teaches: implicit binary tree in array, heapify up/down, index math
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

static int parent(int i) {
    return (i - 1) / 2;
}

static int left_child(int i) {
    return 2 * i + 1;
}

static int right_child(int i) {
    return 2 * i + 2;
}

static void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static void heapify_up(MinHeap* h, int idx) {
    while (idx > 0 && h->data[idx] < h->data[parent(idx)]) {
        swap(&h->data[idx], &h->data[parent(idx)]);
        idx = parent(idx);
    }
}

static void heapify_down(MinHeap* h, int idx) {
    while (1) {
        int smallest = idx;
        int l = left_child(idx);
        int r = right_child(idx);

        if (l < h->length && h->data[l] < h->data[smallest]) smallest = l;
        if (r < h->length && h->data[r] < h->data[smallest]) smallest = r;

        if (smallest == idx) break;
        swap(&h->data[idx], &h->data[smallest]);
        idx = smallest;
    }
}

void heap_insert(MinHeap* h, int value) {
    if (h->length == h->capacity) {
        h->capacity *= 2;
        h->data = realloc(h->data, sizeof(int) * h->capacity);
    }
    h->data[h->length] = value;
    heapify_up(h, h->length);
    h->length++;
}

int heap_delete(MinHeap* h) {
    assert(h->length > 0);
    int min = h->data[0];
    h->length--;
    h->data[0] = h->data[h->length];
    heapify_down(h, 0);
    return min;
}

void heap_free(MinHeap* h) {
    free(h->data);
    h->data = NULL;
    h->length = 0;
    h->capacity = 0;
}

int main() {
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
