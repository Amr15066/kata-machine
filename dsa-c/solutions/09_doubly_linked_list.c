// Doubly Linked List: bidirectional linked nodes
// Teaches: prev/next pointers, more complex unlinking, two-pointer maintenance
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
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->prev = NULL;
    node->next = list->head;

    if (list->head) list->head->prev = node;
    else list->tail = node;
    list->head = node;
    list->length++;
}

void dll_append(DoublyLinkedList* list, int value) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = list->tail;

    if (list->tail) list->tail->next = node;
    else list->head = node;
    list->tail = node;
    list->length++;
}

void dll_insert_at(DoublyLinkedList* list, int index, int value) {
    if (index == 0) {
        dll_prepend(list, value);
        return;
    }
    if (index == list->length) {
        dll_append(list, value);
        return;
    }

    Node* curr = list->head;
    for (int i = 0; i < index && curr; i++) curr = curr->next;
    if (!curr) return;

    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = curr;
    node->prev = curr->prev;
    if (curr->prev) curr->prev->next = node;
    curr->prev = node;
    list->length++;
}

int dll_get(DoublyLinkedList* list, int index, bool* ok) {
    Node* curr = list->head;
    for (int i = 0; i < index && curr; i++) curr = curr->next;
    if (!curr) {
        *ok = false;
        return 0;
    }
    *ok = true;
    return curr->value;
}

static void dll_remove_node(DoublyLinkedList* list, Node* node) {
    if (node->prev) node->prev->next = node->next;
    else list->head = node->next;
    if (node->next) node->next->prev = node->prev;
    else list->tail = node->prev;
    list->length--;
    free(node);
}

int dll_remove_at(DoublyLinkedList* list, int index, bool* ok) {
    Node* curr = list->head;
    for (int i = 0; i < index && curr; i++) curr = curr->next;
    if (!curr) {
        *ok = false;
        return 0;
    }
    *ok = true;
    int val = curr->value;
    dll_remove_node(list, curr);
    return val;
}

int dll_remove_value(DoublyLinkedList* list, int value, bool* ok) {
    Node* curr = list->head;
    while (curr && curr->value != value) curr = curr->next;
    if (!curr) {
        *ok = false;
        return 0;
    }
    *ok = true;
    dll_remove_node(list, curr);
    return value;
}

void dll_free(DoublyLinkedList* list) {
    Node* curr = list->head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = list->tail = NULL;
    list->length = 0;
}

int main() {
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
    assert(!ok); // 9 no longer exists.
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
