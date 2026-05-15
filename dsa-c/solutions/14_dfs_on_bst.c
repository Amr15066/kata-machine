// DFS on BST: search leveraging binary search tree property
// Teaches: BST invariant (left < root < right), efficient search
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

bool dfs_on_bst(BinaryNode* node, int needle) {
    if (node == NULL) return false;
    if (node->value == needle) return true;
    if (needle < node->value) return dfs_on_bst(node->left, needle);
    return dfs_on_bst(node->right, needle);
}

void free_tree(BinaryNode* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main() {
    //       20
    //      /  \
    //    10    50
    //   / \   /  \
    //  5  15 30  100
    //    \   / \
    //    7  29 45
    BinaryNode* root = new_node(20);
    root->left = new_node(10);
    root->right = new_node(50);
    root->left->left = new_node(5);
    root->left->right = new_node(15);
    root->left->left->right = new_node(7);
    root->right->left = new_node(30);
    root->right->right = new_node(100);
    root->right->left->left = new_node(29);
    root->right->left->right = new_node(45);

    assert(dfs_on_bst(root, 45) == true);
    assert(dfs_on_bst(root, 7) == true);
    assert(dfs_on_bst(root, 20) == true);
    assert(dfs_on_bst(root, 69) == false);
    assert(dfs_on_bst(root, 1) == false);

    free_tree(root);
    printf("All DFS on BST tests passed!\n");
    return 0;
}
