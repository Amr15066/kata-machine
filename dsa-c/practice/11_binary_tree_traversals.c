// Binary Tree Traversals: pre-order, in-order, post-order DFS
// Teaches: recursive tree traversal, struct with self-referential pointers
//
// Implement three traversal orders:
//   pre:  root, left, right
//   in:   left, root, right
//   post: left, right, root
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

// Simple dynamic int array for collecting results
typedef struct { int* items; int length; int capacity; } IntArray;
void ia_init(IntArray* a) { a->capacity = 16; a->length = 0; a->items = malloc(sizeof(int) * 16); }
void ia_push(IntArray* a, int val) {
    if (a->length == a->capacity) { a->capacity *= 2; a->items = realloc(a->items, sizeof(int) * a->capacity); }
    a->items[a->length++] = val;
}
void ia_free(IntArray* a) { free(a->items); }

void pre_order(BinaryNode* node, IntArray* result) {
    // TODO: implement pre-order traversal (root, left, right)
}

void in_order(BinaryNode* node, IntArray* result) {
    // TODO: implement in-order traversal (left, root, right)
}

void post_order(BinaryNode* node, IntArray* result) {
    // TODO: implement post-order traversal (left, right, root)
}

void free_tree(BinaryNode* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main(void) {
    //        20
    //       /  \
    //     10    50
    //    / \   /  \
    //   5  15 30  100
    //    \   / \
    //     7 29 45
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

    IntArray pre; ia_init(&pre);
    pre_order(root, &pre);
    int expected_pre[] = {20, 10, 5, 7, 15, 50, 30, 29, 45, 100};
    assert(pre.length == 10);
    for (int i = 0; i < 10; i++) assert(pre.items[i] == expected_pre[i]);
    ia_free(&pre);

    IntArray in; ia_init(&in);
    in_order(root, &in);
    int expected_in[] = {5, 7, 10, 15, 20, 29, 30, 45, 50, 100};
    assert(in.length == 10);
    for (int i = 0; i < 10; i++) assert(in.items[i] == expected_in[i]);
    ia_free(&in);

    IntArray post; ia_init(&post);
    post_order(root, &post);
    int expected_post[] = {7, 5, 15, 10, 29, 45, 30, 100, 50, 20};
    assert(post.length == 10);
    for (int i = 0; i < 10; i++) assert(post.items[i] == expected_post[i]);
    ia_free(&post);

    free_tree(root);
    printf("All binary tree traversal tests passed!\n");
    return 0;
}
