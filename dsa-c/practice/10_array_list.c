// ArrayList: dynamic array that grows as needed
// Teaches: realloc, capacity vs length, amortized O(1) append, memmove
//
// Implement a resizable array. Double capacity when full.
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int* data;
    int length;
    int capacity;
} ArrayList;

void al_init(ArrayList* list) {
    list->capacity = 4;
    list->length = 0;
    list->data = malloc(sizeof(int) * list->capacity);
}

void al_append(ArrayList* list, int value) {
    // TODO: grow if needed, add to end
}

void al_prepend(ArrayList* list, int value) {
    // TODO: grow if needed, shift elements right, insert at 0
    // Hint: use memmove()
}

int al_get(ArrayList* list, int index, bool* ok) {
    // TODO: bounds check, return value
    *ok = false;
    return 0;
}

int al_remove_at(ArrayList* list, int index, bool* ok) {
    // TODO: bounds check, shift elements left, decrement length
    *ok = false;
    return 0;
}

int al_remove_value(ArrayList* list, int value, bool* ok) {
    // TODO: find value, then remove at that index
    *ok = false;
    return 0;
}

void al_free(ArrayList* list) {
    free(list->data);
    list->data = NULL;
    list->length = 0;
    list->capacity = 0;
}

int main(void) {
    ArrayList list;
    al_init(&list);
    bool ok;

    al_append(&list, 5);
    al_append(&list, 7);
    al_append(&list, 9);

    assert(al_get(&list, 2, &ok) == 9 && ok);
    assert(al_remove_at(&list, 1, &ok) == 7 && ok);
    assert(list.length == 2);

    al_append(&list, 11);
    assert(al_remove_at(&list, 1, &ok) == 9 && ok);
    al_remove_value(&list, 9, &ok);
    assert(!ok);
    assert(al_remove_at(&list, 0, &ok) == 5 && ok);
    assert(al_remove_at(&list, 0, &ok) == 11 && ok);
    assert(list.length == 0);

    al_prepend(&list, 5);
    al_prepend(&list, 7);
    al_prepend(&list, 9);

    assert(al_get(&list, 2, &ok) == 5 && ok);
    assert(al_get(&list, 0, &ok) == 9 && ok);
    assert(al_get(&list, 1, &ok) == 7 && ok);

    al_free(&list);
    printf("All array list tests passed!\n");
    return 0;
}
