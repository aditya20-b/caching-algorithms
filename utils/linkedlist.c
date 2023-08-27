#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

LinkedList_t *ll_create() {
    LinkedList_t *list = malloc(sizeof(LinkedList_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

ll_status ll_append(LinkedList_t *list, void* data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    // If the list is empty, set the head to the new node
    if (list->head == NULL) {
        list->head = node;

        // Otherwise, set the tail's next to the new node
    }
    else {
        list->tail->next = node;
    }
    // Set the tail to the new node
    list->tail = node;
    list->size++;
    return LL_SUCCESS;
}

ll_status ll_insert(LinkedList_t *list, void* data, int index) {

    if (index < 0 || index > list->size) {
        return LL_OUT_OF_BOUNDS;
    }

    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    // If the list is empty, set the head to the new node
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
        list->size++;
        return LL_SUCCESS;
    }
    else if (index == 0) {
        node->next = list->head;
        list->head = node;
        list->size++;
        return LL_SUCCESS;
    }
    else if (index == list->size) {
        list->tail->next = node;
        list->tail = node;
        list->size++;
        return LL_SUCCESS;
    } else {

        Node *current = list->head;
        for (int i = 1; i < index; i++) {
            if (!current) {
                free(node);
                return LL_OUT_OF_BOUNDS; // Just to be extra safe
            }
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }
    list->size++;
    return LL_SUCCESS;
}


ll_status ll_remove_last(LinkedList_t *list) {

    if (list->head == NULL) {
        return LL_EMPTY;
    }

    if (list->head == list->tail) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->size--;
        return LL_SUCCESS;
    }

    Node *current = list->head;
    Node *previous = NULL;

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }
    
    previous->next = NULL;
    list->tail = previous;
    free(current);
    list->size--;
    return LL_SUCCESS;
}


ll_status ll_remove_at(LinkedList_t *list, int index) {

    if (index < 0 || index >= list->size) {
        return LL_OUT_OF_BOUNDS;
    }

    Node *current = list->head;
    Node *previous = NULL;
    int i = 0;

    if (current == NULL) {
        return LL_EMPTY;
    }

    for (i = 0; i < index && current != NULL; i++) {
        if (!current) {
            return LL_OUT_OF_BOUNDS; // Just to be extra safe
        }
        previous = current;
        current = current->next;
    }

    if (current == list->head) {
        list->head = current->next;
    } else if (previous) {
        previous->next = current->next;
    }

    if (current == list->tail) {
        list->tail = previous;
    }

    free(current);
    list->size--;
    return LL_SUCCESS;
}


void _print_linked_list(LinkedList_t *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", *(int*)(current->data));  // Dereference the data as int*
        current = current->next;
    }
    printf("\n");
}


void ll_destroy(LinkedList_t *list) {
    Node *current = list->head;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        // Only uncomment this if you are storing pointers in the linked list
        // free(current->data);
        free(current);
        current = next;
    }
    free(list);
}

int _main() {
    LinkedList_t *list = ll_create();
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; i++) {
        ll_append(list, &nums[i]);
    }



    _print_linked_list(list);

    ll_remove_at(list, 0);
    ll_remove_at(list, 1);
    ll_remove_at(list, 5);
    ll_remove_at(list, 10);
    ll_remove_at(list, 15);
    ll_remove_at(list, 20);

    int extra_nums[] = {32, 142, 242, 342};
    ll_insert(list, &extra_nums[0], 0);
    ll_insert(list, &extra_nums[1], 4);
    ll_insert(list, &extra_nums[2], 9);
    ll_insert(list, &extra_nums[3], 5);

    _print_linked_list(list);

    ll_destroy(list);
    return 0;
}
