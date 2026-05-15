// LRU Cache: Least Recently Used eviction with O(1) get/put
// Teaches: combining hash map + doubly linked list, eviction policy
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
    LRUNode** buckets;  // hash table for O(1) lookup
    int bucket_count;
    LRUNode* head;      // most recently used
    LRUNode* tail;      // least recently used
    int capacity;
    int size;
} LRUCache;

static char* string_duplicate(const char* s) {
    size_t len = strlen(s) + 1;
    char* copy = malloc(len);
    memcpy(copy, s, len);
    return copy;
}

static unsigned int hash_key(const char* key, int capacity) {
    unsigned int h = 0;
    while (*key) {
        h = h * 31 + (unsigned char)*key;
        key++;
    }
    return h % (unsigned int)capacity;
}

void lru_init(LRUCache* c, int capacity) {
    c->capacity = capacity;
    c->size = 0;
    c->head = NULL;
    c->tail = NULL;
    c->bucket_count = capacity * 4; // over-provision to reduce collisions
    c->buckets = calloc((size_t)c->bucket_count, sizeof(LRUNode*));
}

static LRUNode* lru_find(LRUCache* c, const char* key) {
    // Linear scan (simplified; production would use chaining).
    for (int i = 0; i < c->bucket_count; i++) {
        LRUNode* n = c->buckets[i];
        if (n && strcmp(n->key, key) == 0) return n;
    }
    return NULL;
}

static void lru_detach(LRUCache* c, LRUNode* node) {
    if (node->prev) node->prev->next = node->next;
    else c->head = node->next;
    if (node->next) node->next->prev = node->prev;
    else c->tail = node->prev;
    node->prev = NULL;
    node->next = NULL;
}

static void lru_prepend(LRUCache* c, LRUNode* node) {
    node->next = c->head;
    node->prev = NULL;
    if (c->head) c->head->prev = node;
    c->head = node;
    if (!c->tail) c->tail = node;
}

static void lru_store(LRUCache* c, LRUNode* node) {
    unsigned int idx = hash_key(node->key, c->bucket_count);
    // Simple open addressing (find empty slot).
    for (int i = 0; i < c->bucket_count; i++) {
        int slot = ((int)idx + i) % c->bucket_count;
        if (c->buckets[slot] == NULL) {
            c->buckets[slot] = node;
            return;
        }
    }
}

static void lru_unstore(LRUCache* c, LRUNode* node) {
    for (int i = 0; i < c->bucket_count; i++) {
        if (c->buckets[i] == node) {
            c->buckets[i] = NULL;
            return;
        }
    }
}

void lru_update(LRUCache* c, const char* key, int value) {
    LRUNode* node = lru_find(c, key);

    if (node) {
        node->value = value;
        lru_detach(c, node);
        lru_prepend(c, node);
        return;
    }

    // Evict if at capacity.
    if (c->size == c->capacity) {
        LRUNode* evict = c->tail;
        lru_detach(c, evict);
        lru_unstore(c, evict);
        free(evict->key);
        free(evict);
        c->size--;
    }

    // Create new node.
    node = malloc(sizeof(LRUNode));
    node->key = string_duplicate(key);
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    lru_prepend(c, node);
    lru_store(c, node);
    c->size++;
}

int lru_get(LRUCache* c, const char* key, bool* found) {
    LRUNode* node = lru_find(c, key);
    if (!node) {
        *found = false;
        return 0;
    }

    // Move to front (most recently used).
    lru_detach(c, node);
    lru_prepend(c, node);

    *found = true;
    return node->value;
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
    c->buckets = NULL;
    c->head = NULL;
    c->tail = NULL;
    c->bucket_count = 0;
    c->capacity = 0;
    c->size = 0;
}

int main() {
    LRUCache c;
    lru_init(&c, 3);
    bool found;

    lru_update(&c, "a", 1);
    lru_update(&c, "b", 2);
    lru_update(&c, "c", 3);

    assert(lru_get(&c, "a", &found) == 1 && found);
    assert(lru_get(&c, "b", &found) == 2 && found);
    assert(lru_get(&c, "c", &found) == 3 && found);

    // Each get moves to the front. After get(a), get(b), get(c),
    // the tail is "a", so adding "d" evicts "a".
    lru_update(&c, "d", 4);

    lru_get(&c, "a", &found);
    assert(!found); // evicted

    assert(lru_get(&c, "b", &found) == 2 && found);
    assert(lru_get(&c, "c", &found) == 3 && found);
    assert(lru_get(&c, "d", &found) == 4 && found);

    // Update existing.
    lru_update(&c, "b", 99);
    assert(lru_get(&c, "b", &found) == 99 && found);

    lru_free(&c);
    printf("All LRU cache tests passed!\n");
    return 0;
}
