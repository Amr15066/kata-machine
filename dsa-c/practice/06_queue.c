// Queue: FIFO using a singly linked list
// Teaches: struct definition, malloc/free, pointers
//
// Implement: enqueue adds to tail, dequeue removes from head.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int length;
} Queue;

void queue_init(Queue* q) {
    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
}

void queue_enqueue(Queue* q, int value) {
    // TODO: allocate node, add to tail
}

int queue_dequeue(Queue* q, bool* ok) {
    // TODO: remove from head, return value. Set *ok = false if empty.
    *ok = false;
    return 0;
}

int queue_peek(Queue* q, bool* ok) {
    // TODO: return head value without removing. Set *ok = false if empty.
    *ok = false;
    return 0;
}

void queue_free(Queue* q) {
    // TODO: free all nodes
}

int main(void) {
    Queue q;
    queue_init(&q);
    bool ok;

    queue_enqueue(&q, 5);
    queue_enqueue(&q, 7);
    queue_enqueue(&q, 9);

    assert(queue_dequeue(&q, &ok) == 5 && ok);
    assert(q.length == 2);

    queue_enqueue(&q, 11);
    assert(queue_dequeue(&q, &ok) == 7 && ok);
    assert(queue_dequeue(&q, &ok) == 9 && ok);
    assert(queue_peek(&q, &ok) == 11 && ok);
    assert(queue_dequeue(&q, &ok) == 11 && ok);

    queue_dequeue(&q, &ok);
    assert(!ok);
    assert(q.length == 0);

    queue_enqueue(&q, 69);
    assert(queue_peek(&q, &ok) == 69 && ok);
    assert(q.length == 1);

    queue_free(&q);
    printf("All queue tests passed!\n");
    return 0;
}
