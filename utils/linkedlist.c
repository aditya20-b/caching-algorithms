#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

LinkedList *create_linked_list() {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

ll_status add(LinkedList *list, int value) {
    Node *node = malloc(sizeof(Node));
    node->data = value;
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

ll_status add_at(LinkedList *list, int data, int index) {

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

ll_status remove_data(LinkedList *list, int value) {
    Node *current = list->head;
    Node *previous = NULL;

    if (current == NULL) {
        return LL_EMPTY;
    }

    // Iterate through the list until we find the node with the value
    while (current != NULL && current->data != value) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return LL_NOT_FOUND;
    }

    // If the node is the head, set the head to the next node
    if (current == list->head) {
        list->head = current->next;
        // Otherwise, set the previous node's next to the current node's next
    }
    else {
        previous->next = current->next;
    }

    // If the node is the tail, set the tail to the previous node
    if (current == list->tail) {
        list->tail = previous;
    }

    free(current);
    list->size--;

    return LL_SUCCESS;
}

ll_status remove_at(LinkedList *list, int index) {

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


void _print_linked_list(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_linked_list(LinkedList *list) {
    Node *current = list->head;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

int _main() {
    LinkedList *list = create_linked_list();
    add(list, 1);
    add(list, 2);
    add(list, 3);
    add(list, 4);
    add(list, 5);
    add(list, 6);
    add(list, 7);
    add(list, 8);
    add(list, 9);


    print_linked_list(list);

    remove_at(list, 0);
    remove_at(list, 1);
    remove_at(list, 5);
    remove_at(list, 10);
    remove_at(list, 15);
    remove_at(list, 20);

    add_at(list, 32, 0);
    add_at(list, 142, 4);
    add_at(list, 242, 9);
    add_at(list, 342, 5);

    print_linked_list(list);
    return 0;
}
