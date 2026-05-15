// Stack: LIFO using a singly linked list
// Teaches: push/pop on head of list, simple struct lifecycle
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* top;
    int length;
} Stack;

void stack_init(Stack* s) {
    s->top = NULL;
    s->length = 0;
}

void stack_push(Stack* s, int value) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = s->top;
    s->top = node;
    s->length++;
}

int stack_pop(Stack* s, bool* ok) {
    if (s->top == NULL) {
        *ok = false;
        return 0;
    }
    *ok = true;
    Node* node = s->top;
    int value = node->value;
    s->top = node->next;
    free(node);
    s->length--;
    return value;
}

int stack_peek(Stack* s, bool* ok) {
    if (s->top == NULL) {
        *ok = false;
        return 0;
    }
    *ok = true;
    return s->top->value;
}

void stack_free(Stack* s) {
    Node* curr = s->top;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    s->top = NULL;
    s->length = 0;
}

int main() {
    Stack s;
    stack_init(&s);
    bool ok;

    stack_push(&s, 5);
    stack_push(&s, 7);
    stack_push(&s, 9);

    assert(stack_pop(&s, &ok) == 9 && ok);
    assert(s.length == 2);

    stack_push(&s, 11);
    assert(stack_pop(&s, &ok) == 11 && ok);
    assert(stack_pop(&s, &ok) == 7 && ok);
    assert(stack_peek(&s, &ok) == 5 && ok);
    assert(stack_pop(&s, &ok) == 5 && ok);

    stack_pop(&s, &ok);
    assert(!ok);
    assert(s.length == 0);

    stack_free(&s);
    printf("All stack tests passed!\n");
    return 0;
}
