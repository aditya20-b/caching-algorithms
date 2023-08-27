#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void test_create_and_initial_state() {
    LinkedList_t *list = ll_create();
    if (list->head == NULL && list->tail == NULL && list->size == 0) {
        printf("Test Create and Initial State: Passed\n");
    } else {
        printf("Test Create and Initial State: Failed\n");
    }
    ll_destroy(list);
}

void test_add_elements() {
    LinkedList_t *list = ll_create();
    int nums[] = {1, 2, 3, 0, 4};
    ll_append(list, &nums[0]);
    ll_append(list, &nums[1]);
    ll_append(list, &nums[2]);
    ll_insert(list, &nums[3], 0);
    ll_insert(list, &nums[4], 4);
    printf("Expected List: 0 1 2 3 4\n");
    printf("Actual List:   ");
    _print_linked_list(list);
    ll_destroy(list);
}


void test_remove_by_index() {
    LinkedList_t *list = ll_create();
    int nums[] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; i++) {
        ll_append(list, &nums[i]);
    }
    ll_remove_at(list, 0);
    ll_remove_at(list, 3);
    ll_remove_at(list, 1);
    printf("Expected List after removal by index: 1 3\n");
    printf("Actual List after removal by index:   ");
    _print_linked_list(list);
    ll_destroy(list);
}

void test_boundary_checks() {
    LinkedList_t *list = ll_create();
    int nums[] = {0, 1, 2, 3, 4, 10};
    for (int i = 0; i < 5; i++) {
        ll_append(list, &nums[i]);
    }
    ll_status status1 = ll_insert(list, &nums[5], 10);
    ll_status status2 = ll_remove_at(list, 10);
    if (status1 == LL_OUT_OF_BOUNDS && status2 == LL_OUT_OF_BOUNDS) {
        printf("Boundary Check: Passed\n");
    } else {
        printf("Boundary Check: Failed\n");
    }
    ll_destroy(list);
}



int main() {
    test_create_and_initial_state();
    test_add_elements();
    test_remove_by_index();
    test_boundary_checks();
    return 0;
}
