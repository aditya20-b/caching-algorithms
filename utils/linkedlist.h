#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/// @brief Linked list node implementation
typedef struct Node {
    void* data;
    struct Node *prev;
    struct Node *next;
} Node;

/// @brief Linked list implementation
typedef struct LinkedList_t {
    Node *head;
    Node *tail;
    int size;
} LinkedList_t;

/// @brief Linked list status codes
typedef enum ll_status {
    LL_SUCCESS,
    LL_OUT_OF_BOUNDS,
    LL_NOT_FOUND,
    LL_EMPTY,
} ll_status;


/// @brief Creates and inits a new linked list
/// @return A pointer to the new linked list
LinkedList_t *ll_create();

/// @brief Adds a new node to the end of the linked list
/// @param list Pointer to the linked list
/// @param data Data to be added to the linked list
/// @return LL_SUCCESS if the data was added successfully
ll_status ll_append(LinkedList_t *list, void* data);

/// @brief Adds a new node to the linked list at the specified index
/// @param list Pointer to the linked list
/// @param data Data to be added to the linked list
/// @param index Index to add the data at
/// @return LL_SUCCESS if the data was added successfully, LL_OUT_OF_BOUNDS if the index is out of bounds
ll_status ll_insert(LinkedList_t *list, void* data, int index);

/// @brief Removes the node at the specified index
/// @param list Pointer to the linked list
/// @param index Index to remove the node at
/// @return LL_SUCCESS if the node was removed successfully, LL_OUT_OF_BOUNDS if the index is out of bounds
ll_status ll_remove_at(LinkedList_t *list, int index);


/// @brief Removes the last node from the linked list
/// @param list Pointer to the linked list 
/// @return LL_SUCCESS if the node was removed successfully, LL_EMPTY if the list is empty
ll_status ll_remove_last(LinkedList_t *list);


/// @brief Prints the linked list (for debugging purposes)
/// @param list Pointer to the linked list
void _print_linked_list(LinkedList_t *list);

/// @brief Frees the linked list
/// @param list Pointer to the linked list
void ll_destroy(LinkedList_t *list);

#endif
