// Binary Tree BFS: level-order search using a queue
// Teaches: BFS with explicit queue, combining data structures
//
// Implement: Use a queue to visit nodes level by level.
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

bool bfs(BinaryNode* head, int needle) {
    // TODO: implement BFS using a queue
    // Hint: you'll need to create a simple queue of BinaryNode* pointers
    return false;
}

void free_tree(BinaryNode* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main(void) {
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

    assert(bfs(root, 45) == true);
    assert(bfs(root, 7) == true);
    assert(bfs(root, 69) == false);

    free_tree(root);
    printf("All binary tree BFS tests passed!\n");
    return 0;
}
