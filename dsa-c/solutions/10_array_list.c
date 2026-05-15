// ArrayList: dynamic array that grows as needed
// Teaches: realloc, capacity vs length, amortized O(1) append
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

static void al_grow(ArrayList* list) {
    if (list->length < list->capacity) return;
    list->capacity *= 2;
    list->data = realloc(list->data, sizeof(int) * list->capacity);
}

void al_append(ArrayList* list, int value) {
    al_grow(list);
    list->data[list->length++] = value;
}

void al_prepend(ArrayList* list, int value) {
    al_grow(list);
    memmove(list->data + 1, list->data, sizeof(int) * list->length);
    list->data[0] = value;
    list->length++;
}

void al_insert_at(ArrayList* list, int index, int value) {
    if (index < 0 || index > list->length) return;
    al_grow(list);
    memmove(list->data + index + 1, list->data + index, sizeof(int) * (list->length - index));
    list->data[index] = value;
    list->length++;
}

int al_get(ArrayList* list, int index, bool* ok) {
    if (index < 0 || index >= list->length) {
        *ok = false;
        return 0;
    }
    *ok = true;
    return list->data[index];
}

int al_remove_at(ArrayList* list, int index, bool* ok) {
    if (index < 0 || index >= list->length) {
        *ok = false;
        return 0;
    }
    *ok = true;
    int val = list->data[index];
    memmove(list->data + index, list->data + index + 1, sizeof(int) * (list->length - index - 1));
    list->length--;
    return val;
}

int al_remove_value(ArrayList* list, int value, bool* ok) {
    for (int i = 0; i < list->length; i++) {
        if (list->data[i] == value) {
            return al_remove_at(list, i, ok);
        }
    }
    *ok = false;
    return 0;
}

void al_free(ArrayList* list) {
    free(list->data);
    list->data = NULL;
    list->length = 0;
    list->capacity = 0;
}

int main() {
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
