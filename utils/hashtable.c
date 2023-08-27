#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define BIG_PRIME 1000003

HashTable_t *ht_create(int size, HashFunc_t hash, CompareFunc_t compare) {
    HashTable_t *ht = malloc(sizeof(HashTable_t));
    if (ht == NULL) {
        return NULL;
    }
    ht->size = size;
    ht->count = 0;
    ht->table = calloc(size, sizeof(HashItem_t)); // Array of HashItem_t
    ht->hash = hash;
    ht->compare = compare;
    if (ht->table == NULL) {
        free(ht);
        return NULL;
    }
    return ht;
}

void ht_destroy(HashTable_t *ht) {
    free(ht->table); 
    free(ht);
}

ht_status_t ht_insert(HashTable_t *ht, void *key, void *value) {
    int index = ht->hash(key) % ht->size;
    int i = 0;
    while (ht->table[index].state == OCCUPIED) {
        // If the key already exists, return HT_EXISTS
        if (ht->compare(ht->table[index].key, key)) {
            return HT_EXISTS;
        }

        // If its a different key, we use linear probing to find the next available index
        index = (index + 1) % ht->size;
        i++;

        // If we have looped through the entire table, return HT_ERROR
        if (i == ht->size) {
            return HT_ERROR;
        }
    }

    // If we have found an empty index, insert the key-value pair
    ht->table[index].key = key;
    ht->table[index].value = value;
    ht->table[index].state = OCCUPIED;
    ht->count++;
    return HT_SUCCESS;
}


ht_status_t ht_replace(HashTable_t *ht, void *key, void *value) {
    int index = ht->hash(key) % ht->size;
    int i = 0;
    while (ht->table[index].state != EMPTY) {
        if (ht->compare(ht->table[index].key, key)) {
            ht->table[index].value = value;
            return HT_SUCCESS;
        }
        index = (index + 1) % ht->size;
        i++;
        if (i == ht->size) {
            return HT_NOT_FOUND;
        }
    }
    return HT_NOT_FOUND;
}


ht_status_t ht_delete(HashTable_t *ht, void *key) {
    int index = ht->hash(key) % ht->size;
    int i = 0;
    // Normally, we would have to check if the key exists before deleting it
    // But since we are using linear probing, we can just check if the next index is empty
    while (ht->table[index].state != EMPTY) {
        // We use the compare function passed via the function pointer to check if the keys are equal
        if (ht->compare(ht->table[index].key, key)) {
            // If they are equal, we mark the cell as DELETED and decrement the count
            ht->table[index].state = DELETED;
            ht->count--;
            return HT_SUCCESS;
        }
        // If they are not equal, we move on to the next index using linear probing
        index = (index + 1) % ht->size;
        i++;
        if (i == ht->size) {
            return HT_NOT_FOUND;
        }
    }
    return HT_NOT_FOUND;
}


void* ht_search(HashTable_t *ht, void *key) {
    int index = ht->hash(key) % ht->size;
    int i = 0;
    while (ht->table[index].state != EMPTY && ht->table[index].state != DELETED) {
        if (ht->compare(ht->table[index].key, key)) {
            return ht->table[index].value;
        }
        index = (index + 1) % ht->size;
        i++;
        if (i == ht->size) {
            return NULL;
        }
    }
    return NULL;
}

// Helper function to print the hashtable
void _ht_print(HashTable_t *ht) {
    printf("HashTable:\n");
    for (int i = 0; i < ht->size; i++) {
        printf("%d: ", i);
        if (ht->table[i].state == OCCUPIED) {
            printf("%i: %i\n", *((int *)ht->table[i].key), *((int *)ht->table[i].value));
        } else {
            printf("EMPTY\n");
        }
    }
}

int ht_int_hash(void *key) {
    // We are using a large prime number to reduce collisions
    int hash_val = *(int *) key % BIG_PRIME;
    // Sometimes the hash value can be negative due to memory errors(?), so we ll_append the prime number to it to make it positive
    return (hash_val < 0) ? hash_val + BIG_PRIME : hash_val;
}

bool ht_int_compare(void *key1, void *key2) {
    return *(int *)key1 == *(int *)key2;
}

int ht_string_hash(void *key) {
    char *str = (char *)key;
    int hash = 0;
    for (int i = 0; i < strlen(str); i++) {
        hash += str[i];
    }
    return hash;
}

bool ht_string_compare(void *key1, void *key2) {
    return strcmp((char *)key1, (char *)key2) == 0;
}



// Test out the hashtable

int _main() {
    HashTable_t *ht = ht_create(10, ht_int_hash, ht_int_compare);

    int key1 = 1;
    int key2 = 2;
    int key3 = 3;
    int key4 = 4;
    int key5 = 5, key6 = 6, key7 = 7, key8 = 8, key9 = 9, key10 = 10;

    int value1 = 1, value2 = 2, value3 = 3, value4 = 4, value5 = 5, value6 = 6;    

    ht_insert(ht, &key1, &value1);
    ht_insert(ht, &key2, &value2);
    ht_insert(ht, &key3, &value3);
    ht_insert(ht, &key4, &value3);
    ht_insert(ht, &key5, &value6);
    ht_insert(ht, &key6, &value6);
    ht_insert(ht, &key6, &value1);

    _ht_print(ht);
    ht_delete(ht, &key1);
    _ht_print(ht);
    int *value = (int *) ht_search(ht, &key7);
    if (value == NULL) {
        printf("Value not found\n");
    } else {
        printf("Value: %d\n", *value);
    }
    ht_destroy(ht);
}