#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void test_create_and_initial_state() {
    LinkedList *list = create_linked_list();
    if (list->head == NULL && list->tail == NULL && list->size == 0) {
        printf("Test Create and Initial State: Passed\n");
    } else {
        printf("Test Create and Initial State: Failed\n");
    }
    free_linked_list(list);
}

void test_add_elements() {
    LinkedList *list = create_linked_list();
    add(list, 1);
    add(list, 2);
    add(list, 3);
    add_at(list, 0, 0);  // add 0 at the beginning
    add_at(list, 4, 4);  // add 4 at the end
    printf("Expected List: 0 1 2 3 4\n");
    printf("Actual List:   ");
    print_linked_list(list);
    free_linked_list(list);
}

void test_remove_by_value() {
    LinkedList *list = create_linked_list();
    for (int i = 0; i < 5; i++) {
        add(list, i);
    }
    remove_data(list, 0);
    remove_data(list, 4);
    remove_data(list, 2);
    printf("Expected List after removal: 1 3\n");
    printf("Actual List after removal:   ");
    print_linked_list(list);
    free_linked_list(list);
}

void test_remove_by_index() {
    LinkedList *list = create_linked_list();
    for (int i = 0; i < 5; i++) {
        add(list, i);
    }
    remove_at(list, 0);
    remove_at(list, 3);
    remove_at(list, 1);
    printf("Expected List after removal by index: 1 3\n");
    printf("Actual List after removal by index:   ");
    print_linked_list(list);
    free_linked_list(list);
}

void test_boundary_checks() {
    LinkedList *list = create_linked_list();
    for (int i = 0; i < 5; i++) {
        add(list, i);
    }
    ll_status status1 = add_at(list, 10, 10);
    ll_status status2 = remove_at(list, 10);
    if (status1 == LL_OUT_OF_BOUNDS && status2 == LL_OUT_OF_BOUNDS) {
        printf("Boundary Check: Passed\n");
    } else {
        printf("Boundary Check: Failed\n");
    }
    free_linked_list(list);
}

int main() {
    test_create_and_initial_state();
    test_add_elements();
    test_remove_by_value();
    test_remove_by_index();
    test_boundary_checks();
    return 0;
}
