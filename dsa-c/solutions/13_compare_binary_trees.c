// Compare Binary Trees: structural and value equality check
// Teaches: simultaneous recursion on two trees, base cases
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct BinaryNode {
    int value;
    struct BinaryNode* left;
    struct BinaryNode* right;
} BinaryNode;

BinaryNode* new_node(int value) {
    BinaryNode* n = malloc(sizeof(BinaryNode));
    n->value = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

bool compare(BinaryNode* a, BinaryNode* b) {
    // Both null = structurally equal at this point.
    if (a == NULL && b == NULL) return true;
    // One null, other not = different structure.
    if (a == NULL || b == NULL) return false;
    // Different values.
    if (a->value != b->value) return false;
    // Recurse on children.
    return compare(a->left, b->left) && compare(a->right, b->right);
}

void free_tree(BinaryNode* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main() {
    // Tree 1.
    BinaryNode* t1 = new_node(20);
    t1->left = new_node(10);
    t1->right = new_node(50);
    t1->left->left = new_node(5);
    t1->left->right = new_node(15);

    // Tree 2: same as tree 1.
    BinaryNode* t2 = new_node(20);
    t2->left = new_node(10);
    t2->right = new_node(50);
    t2->left->left = new_node(5);
    t2->left->right = new_node(15);

    // Tree 3: different structure.
    BinaryNode* t3 = new_node(20);
    t3->left = new_node(10);
    t3->right = new_node(50);
    t3->left->left = new_node(5);
    t3->left->right = new_node(99); // different value

    assert(compare(t1, t2) == true);
    assert(compare(t1, t3) == false);
    assert(compare(t1, NULL) == false);
    assert(compare(NULL, NULL) == true);

    free_tree(t1);
    free_tree(t2);
    free_tree(t3);
    printf("All compare binary trees tests passed!\n");
    return 0;
}
