// Trie: prefix tree for string storage and prefix search
// Teaches: tree of arrays, string iteration, recursive collection
//
// Implement: insert adds characters one by one. find collects all words with prefix.
// delete removes a word and cleans up empty nodes.
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

TrieNode* trie_new_node(void) {
    return calloc(1, sizeof(TrieNode));
}

void trie_insert(TrieNode* root, const char* word) {
    // TODO: walk/create nodes for each character
}

void trie_delete(TrieNode* root, const char* word) {
    // TODO: unmark is_end, clean up empty nodes
    // Hint: use a recursive helper that returns true if parent should free child
}

// String array helper for collecting results
typedef struct { char** words; int length; int capacity; } StringArray;
void sa_init(StringArray* a) { a->capacity = 16; a->length = 0; a->words = malloc(sizeof(char*) * 16); }
void sa_push(StringArray* a, const char* w) {
    if (a->length == a->capacity) { a->capacity *= 2; a->words = realloc(a->words, sizeof(char*) * a->capacity); }
    a->words[a->length] = malloc(strlen(w) + 1);
    strcpy(a->words[a->length], w);
    a->length++;
}
void sa_free(StringArray* a) { for (int i = 0; i < a->length; i++) free(a->words[i]); free(a->words); }
bool sa_contains(StringArray* a, const char* w) {
    for (int i = 0; i < a->length; i++) if (strcmp(a->words[i], w) == 0) return true;
    return false;
}

void trie_find_with_prefix(TrieNode* root, const char* prefix, StringArray* results) {
    // TODO: walk to prefix node, then collect all words from there
    // Hint: use a recursive collect function with a char buffer
}

void trie_free(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) trie_free(node->children[i]);
    free(node);
}

int main(void) {
    TrieNode* root = trie_new_node();

    trie_insert(root, "foo");
    trie_insert(root, "fool");
    trie_insert(root, "foolish");
    trie_insert(root, "bar");

    StringArray results;
    sa_init(&results);
    trie_find_with_prefix(root, "fo", &results);
    assert(results.length == 3);
    assert(sa_contains(&results, "foo"));
    assert(sa_contains(&results, "fool"));
    assert(sa_contains(&results, "foolish"));
    sa_free(&results);

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
