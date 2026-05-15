// Queue: FIFO using a singly linked list
// Teaches: struct definition, malloc/free, pointers to pointers concept
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
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;

    if (q->tail == NULL) {
        q->head = q->tail = node;
    } else {
        q->tail->next = node;
        q->tail = node;
    }
    q->length++;
}

int queue_dequeue(Queue* q, bool* ok) {
    if (q->head == NULL) {
        *ok = false;
        return 0;
    }
    *ok = true;
    Node* node = q->head;
    int value = node->value;
    q->head = node->next;
    if (q->head == NULL) q->tail = NULL;
    free(node);
    q->length--;
    return value;
}

int queue_peek(Queue* q, bool* ok) {
    if (q->head == NULL) {
        *ok = false;
        return 0;
    }
    *ok = true;
    return q->head->value;
}

void queue_free(Queue* q) {
    Node* curr = q->head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    q->head = q->tail = NULL;
    q->length = 0;
}

int main() {
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

    // Enqueue again after empty.
    queue_enqueue(&q, 69);
    assert(queue_peek(&q, &ok) == 69 && ok);
    assert(q.length == 1);

    queue_free(&q);
    printf("All queue tests passed!\n");
    return 0;
}
