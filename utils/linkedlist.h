#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/// @brief Linked list node implementation
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

/// @brief Linked list implementation
typedef struct LinkedList {
    Node *head;
    Node *tail;
    int size;
} LinkedList;

/// @brief Linked list status codes
typedef enum ll_status {
    LL_SUCCESS,
    LL_OUT_OF_BOUNDS,
    LL_NOT_FOUND,
    LL_EMPTY,
} ll_status;


/// @brief Creates and inits a new linked list
/// @return A pointer to the new linked list
LinkedList *create_linked_list();

/// @brief Adds a new node to the end of the linked list
/// @param list Pointer to the linked list
/// @param data Data to be added to the linked list
/// @return LL_SUCCESS if the data was added successfully
ll_status add(LinkedList *list, int data);

/// @brief Adds a new node to the linked list at the specified index
/// @param list Pointer to the linked list
/// @param data Data to be added to the linked list
/// @param index Index to add the data at
/// @return LL_SUCCESS if the data was added successfully, LL_OUT_OF_BOUNDS if the index is out of bounds
ll_status add_at(LinkedList *list, int data, int index);

/// @brief Removes the node at the specified index
/// @param list Pointer to the linked list
/// @param index Index to remove the node at
/// @return LL_SUCCESS if the node was removed successfully, LL_OUT_OF_BOUNDS if the index is out of bounds
ll_status remove_at(LinkedList *list, int index);

/// @brief Removes the first node with the specified data
/// @param list Pointer to the linked list
/// @param data Data to be removed from the linked list
/// @return LL_SUCCESS if the node was removed successfully, LL_NOT_FOUND if the data was not found
ll_status remove_data(LinkedList *list, int data);


/// @brief Prints the linked list (for debugging purposes)
/// @param list Pointer to the linked list
void _print_linked_list(LinkedList *list);

/// @brief Frees the linked list
/// @param list Pointer to the linked list
void free_linked_list(LinkedList *list);





#endif