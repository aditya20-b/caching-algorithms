#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

LinkedList_t *ll_create() {
    LinkedList_t *list = (LinkedList_t *) malloc(sizeof(LinkedList_t));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

ll_status ll_append(LinkedList_t *list, void* data) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = list->tail;

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

    Node *node = (Node *) malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;

    // If the list is empty, set the head to the new node
    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else if (index == 0) {
        // Insert at the head
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    } else if (index == list->size) {
        // Insert at the tail
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    } else {
        // Insert in the middle at nth index
        Node *current = list->head;
        for (int i = 1; i < index; i++) {
            current = current->next;
        }
        node->next = current->next;
        node->prev = current;
        current->next->prev = node;
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
        // Delete the only node
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    } else {
        // Remove the last node
        Node *last_node = list->tail;
        list->tail = last_node->prev;
        list->tail->next = NULL;
        free(last_node);
    }

    list->size--;
    return LL_SUCCESS;
}


ll_status ll_remove_at(LinkedList_t *list, int index) {

    if (index < 0 || index >= list->size) {
        return LL_OUT_OF_BOUNDS;
    }

    Node *current = list->head;

    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    // Remove the node
    // Here if the below condition is true then it means that the node to be deleted is the head node
    // and we need to change the head node to the next node
    // then we need to free the current node
    if (current == list->head) {
        list->head = current->next;
        if (list->head) {
            list->head->prev = NULL;
        }
    } else if (current == list->tail) {
        list->tail = current->prev; 
        list->tail->next = NULL;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
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
