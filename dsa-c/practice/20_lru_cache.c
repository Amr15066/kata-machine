// LRU Cache: Least Recently Used eviction with hash map + doubly linked list
// Teaches: combining data structures, eviction policy
//
// Implement: update() adds/refreshes entry, get() returns value and refreshes.
// When at capacity, evict the least recently used (tail of list).
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef struct LRUNode {
    char* key;
    int value;
    struct LRUNode* prev;
    struct LRUNode* next;
} LRUNode;

typedef struct {
    LRUNode** buckets;
    int bucket_count;
    LRUNode* head;  // most recently used
    LRUNode* tail;  // least recently used
    int capacity;
    int size;
} LRUCache;

void lru_init(LRUCache* c, int capacity) {
    c->capacity = capacity;
    c->size = 0;
    c->head = NULL;
    c->tail = NULL;
    c->bucket_count = capacity * 4;
    c->buckets = calloc(c->bucket_count, sizeof(LRUNode*));
}

void lru_update(LRUCache* c, const char* key, int value) {
    // TODO: if key exists, update value and move to front
    // If new and at capacity, evict tail (LRU)
    // Then insert new node at front
}

int lru_get(LRUCache* c, const char* key, bool* found) {
    // TODO: find node, move to front (refresh), return value
    *found = false;
    return 0;
}

void lru_free(LRUCache* c) {
    LRUNode* curr = c->head;
    while (curr) {
        LRUNode* next = curr->next;
        free(curr->key);
        free(curr);
        curr = next;
    }
    free(c->buckets);
}

int main(void) {
    LRUCache c;
    lru_init(&c, 3);
    bool found;

    lru_update(&c, "a", 1);
    lru_update(&c, "b", 2);
    lru_update(&c, "c", 3);

    assert(lru_get(&c, "a", &found) == 1 && found);
    assert(lru_get(&c, "b", &found) == 2 && found);
    assert(lru_get(&c, "c", &found) == 3 && found);

    // After get(a), get(b), get(c): order is c, b, a
    // Adding d evicts a (LRU = tail)
    lru_update(&c, "d", 4);
    lru_get(&c, "a", &found);
    assert(!found);

    assert(lru_get(&c, "b", &found) == 2 && found);
    assert(lru_get(&c, "c", &found) == 3 && found);
    assert(lru_get(&c, "d", &found) == 4 && found);

    lru_update(&c, "b", 99);
    assert(lru_get(&c, "b", &found) == 99 && found);

    lru_free(&c);
    printf("All LRU cache tests passed!\n");
    return 0;
}
