// Doubly Linked List: bidirectional linked nodes
// Teaches: prev/next pointers, more complex unlinking, head+tail maintenance
//
// Implement all operations. Remember to update both prev and next pointers.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int length;
} DoublyLinkedList;

void dll_init(DoublyLinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

void dll_prepend(DoublyLinkedList* list, int value) {
    // TODO: insert at head, update prev/next
}

void dll_append(DoublyLinkedList* list, int value) {
    // TODO: insert at tail, update prev/next
}

int dll_get(DoublyLinkedList* list, int index, bool* ok) {
    // TODO: walk to index and return value
    *ok = false;
    return 0;
}

int dll_remove_at(DoublyLinkedList* list, int index, bool* ok) {
    // TODO: remove node at index, fix prev/next links
    *ok = false;
    return 0;
}

int dll_remove_value(DoublyLinkedList* list, int value, bool* ok) {
    // TODO: find and remove first node with this value
    *ok = false;
    return 0;
}

void dll_free(DoublyLinkedList* list) {
    // TODO: free all nodes
}

int main(void) {
    DoublyLinkedList list;
    dll_init(&list);
    bool ok;

    dll_append(&list, 5);
    dll_append(&list, 7);
    dll_append(&list, 9);

    assert(dll_get(&list, 2, &ok) == 9 && ok);
    assert(dll_remove_at(&list, 1, &ok) == 7 && ok);
    assert(list.length == 2);

    dll_append(&list, 11);
    assert(dll_remove_at(&list, 1, &ok) == 9 && ok);
    dll_remove_value(&list, 9, &ok);
    assert(!ok);
    assert(dll_remove_at(&list, 0, &ok) == 5 && ok);
    assert(dll_remove_at(&list, 0, &ok) == 11 && ok);
    assert(list.length == 0);

    dll_prepend(&list, 5);
    dll_prepend(&list, 7);
    dll_prepend(&list, 9);

    assert(dll_get(&list, 2, &ok) == 5 && ok);
    assert(dll_get(&list, 0, &ok) == 9 && ok);
    assert(dll_get(&list, 1, &ok) == 7 && ok);

    dll_free(&list);
    printf("All doubly linked list tests passed!\n");
    return 0;
}
