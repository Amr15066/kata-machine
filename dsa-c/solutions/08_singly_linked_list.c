// Singly Linked List: forward-only linked nodes with insert/remove/get
// Teaches: pointer chasing, node allocation, edge cases (head/tail ops)
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
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = list->head;
    list->head = node;
    list->length++;
}

void sll_append(SinglyLinkedList* list, int value) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
    } else {
        Node* curr = list->head;
        while (curr->next) curr = curr->next;
        curr->next = node;
    }
    list->length++;
}

void sll_insert_at(SinglyLinkedList* list, int index, int value) {
    if (index == 0) {
        sll_prepend(list, value);
        return;
    }

    Node* curr = list->head;
    for (int i = 0; i < index - 1 && curr; i++) curr = curr->next;
    if (!curr) return;

    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = curr->next;
    curr->next = node;
    list->length++;
}

int sll_get(SinglyLinkedList* list, int index, bool* ok) {
    Node* curr = list->head;
    for (int i = 0; i < index && curr; i++) curr = curr->next;
    if (!curr) {
        *ok = false;
        return 0;
    }
    *ok = true;
    return curr->value;
}

int sll_remove_at(SinglyLinkedList* list, int index, bool* ok) {
    if (!list->head) {
        *ok = false;
        return 0;
    }

    if (index == 0) {
        Node* node = list->head;
        int val = node->value;
        list->head = node->next;
        free(node);
        list->length--;
        *ok = true;
        return val;
    }

    Node* curr = list->head;
    for (int i = 0; i < index - 1 && curr->next; i++) curr = curr->next;
    if (!curr->next) {
        *ok = false;
        return 0;
    }

    Node* node = curr->next;
    int val = node->value;
    curr->next = node->next;
    free(node);
    list->length--;
    *ok = true;
    return val;
}

int sll_remove_value(SinglyLinkedList* list, int value, bool* ok) {
    if (!list->head) {
        *ok = false;
        return 0;
    }

    if (list->head->value == value) {
        Node* node = list->head;
        list->head = node->next;
        free(node);
        list->length--;
        *ok = true;
        return value;
    }

    Node* curr = list->head;
    while (curr->next && curr->next->value != value) curr = curr->next;
    if (!curr->next) {
        *ok = false;
        return 0;
    }

    Node* node = curr->next;
    curr->next = node->next;
    free(node);
    list->length--;
    *ok = true;
    return value;
}

void sll_free(SinglyLinkedList* list) {
    Node* curr = list->head;
    while (curr) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
    list->head = NULL;
    list->length = 0;
}

int main() {
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
    assert(!ok); // 9 no longer exists.
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
