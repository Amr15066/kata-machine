// Hash Map: key-value store with separate chaining
// Teaches: hashing, linked list buckets, string handling
//
// Implement: hash function, set (insert/update), get, delete.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define CAPACITY 16

typedef struct Entry {
    char* key;
    int value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry** buckets;
    int capacity;
    int size;
} HashMap;

void map_init(HashMap* m) {
    m->capacity = CAPACITY;
    m->size = 0;
    m->buckets = calloc(m->capacity, sizeof(Entry*));
}

static unsigned int hash(const char* key, int capacity) {
    // TODO: implement a hash function
    // Hint: h = h * 31 + char, then % capacity
    return 0;
}

void map_set(HashMap* m, const char* key, int value) {
    // TODO: hash key, check if exists (update), else insert new entry
}

int map_get(HashMap* m, const char* key, bool* found) {
    // TODO: hash key, walk chain, return value if found
    *found = false;
    return 0;
}

bool map_delete(HashMap* m, const char* key) {
    // TODO: hash key, walk chain, unlink and free entry
    return false;
}

void map_free(HashMap* m) {
    // TODO: free all entries and buckets
    for (int i = 0; i < m->capacity; i++) {
        Entry* curr = m->buckets[i];
        while (curr) {
            Entry* next = curr->next;
            free(curr->key);
            free(curr);
            curr = next;
        }
    }
    free(m->buckets);
}

int main(void) {
    HashMap m;
    map_init(&m);
    bool found;

    map_set(&m, "foo", 55);
    assert(m.size == 1);
    map_set(&m, "fool", 75);
    assert(m.size == 2);
    map_set(&m, "foolish", 105);
    assert(m.size == 3);

    assert(map_get(&m, "foo", &found) == 55 && found);
    assert(map_get(&m, "fool", &found) == 75 && found);
    assert(map_get(&m, "foolish", &found) == 105 && found);
    map_get(&m, "missing", &found);
    assert(!found);

    assert(map_delete(&m, "fool") == true);
    assert(m.size == 2);
    map_get(&m, "fool", &found);
    assert(!found);

    assert(map_delete(&m, "nope") == false);

    map_free(&m);
    printf("All hash map tests passed!\n");
    return 0;
}
