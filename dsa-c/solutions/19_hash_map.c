// Hash Map: key-value store with separate chaining
// Teaches: hashing, linked list buckets, dynamic resizing concept
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define INITIAL_CAPACITY 16

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

static char* string_duplicate(const char* s) {
    size_t len = strlen(s) + 1;
    char* copy = malloc(len);
    memcpy(copy, s, len);
    return copy;
}

void map_init(HashMap* m) {
    m->capacity = INITIAL_CAPACITY;
    m->size = 0;
    m->buckets = calloc((size_t)m->capacity, sizeof(Entry*));
}

static unsigned int hash(const char* key, int capacity) {
    unsigned int h = 0;
    while (*key) {
        h = h * 31 + (unsigned char)*key;
        key++;
    }
    return h % (unsigned int)capacity;
}

void map_set(HashMap* m, const char* key, int value) {
    unsigned int idx = hash(key, m->capacity);

    // Check if key exists.
    Entry* curr = m->buckets[idx];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            curr->value = value; // update
            return;
        }
        curr = curr->next;
    }

    // Insert new entry at head of chain.
    Entry* entry = malloc(sizeof(Entry));
    entry->key = string_duplicate(key);
    entry->value = value;
    entry->next = m->buckets[idx];
    m->buckets[idx] = entry;
    m->size++;
}

int map_get(HashMap* m, const char* key, bool* found) {
    unsigned int idx = hash(key, m->capacity);
    Entry* curr = m->buckets[idx];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            *found = true;
            return curr->value;
        }
        curr = curr->next;
    }
    *found = false;
    return 0;
}

bool map_delete(HashMap* m, const char* key) {
    unsigned int idx = hash(key, m->capacity);
    Entry* curr = m->buckets[idx];
    Entry* prev = NULL;

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            if (prev) prev->next = curr->next;
            else m->buckets[idx] = curr->next;
            free(curr->key);
            free(curr);
            m->size--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void map_free(HashMap* m) {
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
    m->buckets = NULL;
    m->size = 0;
    m->capacity = 0;
}

int main() {
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

    // Delete.
    assert(map_delete(&m, "fool") == true);
    assert(m.size == 2);
    map_get(&m, "fool", &found);
    assert(!found);

    // Delete non-existent.
    assert(map_delete(&m, "nope") == false);
    assert(m.size == 2);

    map_free(&m);
    printf("All hash map tests passed!\n");
    return 0;
}
