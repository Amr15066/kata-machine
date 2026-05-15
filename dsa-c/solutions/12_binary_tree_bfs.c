// Binary Tree BFS: level-order search using a queue
// Teaches: BFS with explicit queue, combining data structures
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

// Simple queue of BinaryNode pointers for BFS.
typedef struct QNode {
    BinaryNode* tree_node;
    struct QNode* next;
} QNode;

typedef struct {
    QNode* head;
    QNode* tail;
} NodeQueue;

void nq_init(NodeQueue* q) {
    q->head = q->tail = NULL;
}

void nq_enqueue(NodeQueue* q, BinaryNode* node) {
    QNode* qn = malloc(sizeof(QNode));
    qn->tree_node = node;
    qn->next = NULL;
    if (q->tail) q->tail->next = qn;
    else q->head = qn;
    q->tail = qn;
}

BinaryNode* nq_dequeue(NodeQueue* q) {
    if (!q->head) return NULL;
    QNode* qn = q->head;
    BinaryNode* result = qn->tree_node;
    q->head = qn->next;
    if (!q->head) q->tail = NULL;
    free(qn);
    return result;
}

bool nq_empty(NodeQueue* q) {
    return q->head == NULL;
}

void nq_free(NodeQueue* q) {
    while (!nq_empty(q)) {
        (void)nq_dequeue(q);
    }
}

bool bfs(BinaryNode* head, int needle) {
    if (!head) return false;

    NodeQueue q;
    nq_init(&q);
    nq_enqueue(&q, head);

    while (!nq_empty(&q)) {
        BinaryNode* curr = nq_dequeue(&q);
        if (curr->value == needle) {
            nq_free(&q);
            return true;
        }
        if (curr->left) nq_enqueue(&q, curr->left);
        if (curr->right) nq_enqueue(&q, curr->right);
    }
    return false;
}

void free_tree(BinaryNode* node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main() {
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
