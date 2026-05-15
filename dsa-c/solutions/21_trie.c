// Trie: prefix tree for string storage and prefix search
// Teaches: tree of maps/arrays, string iteration, recursive deletion
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool is_end;
} TrieNode;

typedef struct {
    char** words;
    int length;
    int capacity;
} StringArray;

static char* string_duplicate(const char* s) {
    size_t len = strlen(s) + 1;
    char* copy = malloc(len);
    memcpy(copy, s, len);
    return copy;
}

TrieNode* trie_new_node() {
    TrieNode* node = calloc(1, sizeof(TrieNode));
    return node;
}

void trie_insert(TrieNode* root, const char* word) {
    TrieNode* curr = root;
    while (*word) {
        int idx = *word - 'a';
        if (!curr->children[idx]) {
            curr->children[idx] = trie_new_node();
        }
        curr = curr->children[idx];
        word++;
    }
    curr->is_end = true;
}

bool trie_delete_helper(TrieNode* node, const char* word, int depth) {
    if (!node) return false;

    if (word[depth] == '\0') {
        if (!node->is_end) return false;
        node->is_end = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) return false;
        }
        return true; // safe to delete this node
    }

    int idx = word[depth] - 'a';
    if (trie_delete_helper(node->children[idx], word, depth + 1)) {
        free(node->children[idx]);
        node->children[idx] = NULL;

        if (!node->is_end) {
            for (int i = 0; i < ALPHABET_SIZE; i++) {
                if (node->children[i]) return false;
            }
            return true;
        }
    }
    return false;
}

void trie_delete(TrieNode* root, const char* word) {
    (void)trie_delete_helper(root, word, 0);
}

void sa_init(StringArray* a) {
    a->capacity = 16;
    a->length = 0;
    a->words = malloc(sizeof(char*) * a->capacity);
}

void sa_push(StringArray* a, const char* word) {
    if (a->length == a->capacity) {
        a->capacity *= 2;
        a->words = realloc(a->words, sizeof(char*) * a->capacity);
    }
    a->words[a->length++] = string_duplicate(word);
}

void sa_free(StringArray* a) {
    for (int i = 0; i < a->length; i++) free(a->words[i]);
    free(a->words);
    a->words = NULL;
    a->length = 0;
    a->capacity = 0;
}

void trie_collect(TrieNode* node, char* buffer, int depth, StringArray* results) {
    if (!node) return;
    if (node->is_end) {
        buffer[depth] = '\0';
        sa_push(results, buffer);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            buffer[depth] = (char)('a' + i);
            trie_collect(node->children[i], buffer, depth + 1, results);
        }
    }
}

void trie_find_with_prefix(TrieNode* root, const char* prefix, StringArray* results) {
    TrieNode* curr = root;
    const char* p = prefix;
    while (*p) {
        int idx = *p - 'a';
        if (!curr->children[idx]) return;
        curr = curr->children[idx];
        p++;
    }

    char buffer[256];
    int plen = (int)strlen(prefix);
    strcpy(buffer, prefix);

    if (curr->is_end) {
        sa_push(results, buffer);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (curr->children[i]) {
            buffer[plen] = (char)('a' + i);
            buffer[plen + 1] = '\0';
            trie_collect(curr->children[i], buffer, plen + 1, results);
        }
    }
}

void trie_free(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        trie_free(node->children[i]);
    }
    free(node);
}

static bool sa_contains(StringArray* a, const char* word) {
    for (int i = 0; i < a->length; i++) {
        if (strcmp(a->words[i], word) == 0) return true;
    }
    return false;
}

int main() {
    TrieNode* root = trie_new_node();

    trie_insert(root, "foo");
    trie_insert(root, "fool");
    trie_insert(root, "foolish");
    trie_insert(root, "bar");

    // Find with prefix "fo".
    StringArray results;
    sa_init(&results);
    trie_find_with_prefix(root, "fo", &results);

    assert(results.length == 3);
    assert(sa_contains(&results, "foo"));
    assert(sa_contains(&results, "fool"));
    assert(sa_contains(&results, "foolish"));
    sa_free(&results);

    // Delete "fool".
    trie_delete(root, "fool");

    sa_init(&results);
    trie_find_with_prefix(root, "fo", &results);
    assert(results.length == 2);
    assert(sa_contains(&results, "foo"));
    assert(sa_contains(&results, "foolish"));
    assert(!sa_contains(&results, "fool"));
    sa_free(&results);

    trie_free(root);
    printf("All trie tests passed!\n");
    return 0;
}
