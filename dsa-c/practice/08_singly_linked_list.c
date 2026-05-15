// Singly Linked List: forward-only linked nodes with insert/remove/get
// Teaches: pointer chasing, node allocation, edge cases (head/tail ops)
//
// Implement all operations. Watch out for edge cases at head and tail.
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
    int length;
} SinglyLinkedList;

void sll_init(SinglyLinkedList* list) {
    list->head = NULL;
    list->length = 0;
}

void sll_prepend(SinglyLinkedList* list, int value) {
    // TODO: insert at head
}

void sll_append(SinglyLinkedList* list, int value) {
    // TODO: insert at tail (walk to end)
}

int sll_get(SinglyLinkedList* list, int index, bool* ok) {
    // TODO: return value at index
    *ok = false;
    return 0;
}

int sll_remove_at(SinglyLinkedList* list, int index, bool* ok) {
    // TODO: remove node at index, return its value
    *ok = false;
    return 0;
}

int sll_remove_value(SinglyLinkedList* list, int value, bool* ok) {
    // TODO: find and remove first node with this value
    *ok = false;
    return 0;
}

void sll_free(SinglyLinkedList* list) {
    // TODO: free all nodes
}

int main(void) {
    SinglyLinkedList list;
    sll_init(&list);
    bool ok;

    sll_append(&list, 5);
    sll_append(&list, 7);
    sll_append(&list, 9);

    assert(sll_get(&list, 2, &ok) == 9 && ok);
    assert(sll_remove_at(&list, 1, &ok) == 7 && ok);
    assert(list.length == 2);

    sll_append(&list, 11);
    assert(sll_remove_at(&list, 1, &ok) == 9 && ok);
    sll_remove_value(&list, 9, &ok);
    assert(!ok);
    assert(sll_remove_at(&list, 0, &ok) == 5 && ok);
    assert(sll_remove_at(&list, 0, &ok) == 11 && ok);
    assert(list.length == 0);

    sll_prepend(&list, 5);
    sll_prepend(&list, 7);
    sll_prepend(&list, 9);

    assert(sll_get(&list, 2, &ok) == 5 && ok);
    assert(sll_get(&list, 0, &ok) == 9 && ok);
    assert(sll_get(&list, 1, &ok) == 7 && ok);

    sll_free(&list);
    printf("All singly linked list tests passed!\n");
    return 0;
}
