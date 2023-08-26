#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashtable.h"

#define BIG_PRIME 1000003

// A hash function to create collisions on purpose
int collision_hash(void *key) {
    return 0;
}

// Testing out hashtables durability with hash function that creates collisions
int main() {
    HashTable_t *ht = ht_create(10, collision_hash, ht_int_compare);
    printf("Started tests...\n");
    printf("Created hashtable\n");
    int key1 = 1, key2 = 2, key3 = 3;
    int value1 = 1, value2 = 2, value3 = 3;

    printf("Inserting values...\n");
    ht_insert(ht, &key1, &value1);
    ht_insert(ht, &key2, &value2);
    ht_insert(ht, &key3, &value3);
    printf("Inserted values\n");

    printf("Retrieving values...\n");
    int *retrievedValue1 = (int *)ht_search(ht, &key1);
    int *retrievedValue2 = (int *)ht_search(ht, &key2);
    int *retrievedValue3 = (int *)ht_search(ht, &key3);

    assert(*retrievedValue1 == value1);
    assert(*retrievedValue2 == value2);
    assert(*retrievedValue3 == value3);
    printf("Retrieved values\n");

    printf("Deleting values...\n");
    int deletion_status = ht_delete(ht, &key2);
    int *deletedValue = (int *)ht_search(ht, &key2);
    assert(deletedValue == NULL);
    printf("Deleted values\n");

    printf("Inserting more values...\n");
    int key4 = 4, value4 = 4;
    ht_insert(ht, &key4, &value4);
    int *retrievedValue4 = (int *)ht_search(ht, &key4);
    assert(*retrievedValue4 == value4);
    printf("Inserted more values\n");
    printf("Finished tests successfully\n");
    return 0;
}