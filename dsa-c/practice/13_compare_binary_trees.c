// Compare Binary Trees: structural and value equality
// Teaches: simultaneous recursion on two trees, base cases
//
// Implement: Return true if both trees have same structure and values.
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
    n->value = value; n->left = NULL; n->right = NULL;
    return n;
}

bool compare(BinaryNode* a, BinaryNode* b) {
    // TODO: implement tree comparison
    // Hint: handle NULL cases first, then compare values and recurse
    return false;
}

void free_tree(BinaryNode* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main(void) {
    BinaryNode* t1 = new_node(20);
    t1->left = new_node(10); t1->right = new_node(50);
    t1->left->left = new_node(5); t1->left->right = new_node(15);

    BinaryNode* t2 = new_node(20);
    t2->left = new_node(10); t2->right = new_node(50);
    t2->left->left = new_node(5); t2->left->right = new_node(15);

    BinaryNode* t3 = new_node(20);
    t3->left = new_node(10); t3->right = new_node(50);
    t3->left->left = new_node(5); t3->left->right = new_node(99);

    assert(compare(t1, t2) == true);
    assert(compare(t1, t3) == false);
    assert(compare(t1, NULL) == false);
    assert(compare(NULL, NULL) == true);

    free_tree(t1); free_tree(t2); free_tree(t3);
    printf("All compare binary trees tests passed!\n");
    return 0;
}
