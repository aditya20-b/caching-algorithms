#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__
#include <stdbool.h>

/// @brief The status returned by the hashtable functions
typedef enum HashTableStatus {
    HT_SUCCESS,
    HT_ERROR,
    HT_EXISTS,
    HT_NOT_FOUND
} ht_status_t;

/// @brief The state of a cell in the hashtable
typedef enum CellState {
    EMPTY,
    DELETED,
    OCCUPIED
} State_t;

/// @brief A key-value pair of void pointers so that the hashtable can be used with any data type
typedef struct HashItem {
    void *key;
    void *value;
    State_t state;
} HashItem_t;

/// @brief A function pointer to a hash function that takes a void pointer and returns an integer
typedef int (*HashFunc_t)(void *);

/// @brief A function pointer to a compare function that takes two void pointers and returns a boolean
typedef bool (*CompareFunc_t)(void *, void *);

/// @brief A hashtable data structure
typedef struct HashTable {
    int size;
    int count;
    HashItem_t *table;
    HashFunc_t hash;
    CompareFunc_t compare;
} HashTable_t;


/// @brief Creates a new hashtable
/// @param size The size of the hashtable
/// @param hash Pointer to the hash function
/// @param compare Pointer to the compare function
/// @return HashTable_t* Pointer to the hashtable
HashTable_t *ht_create(int size, HashFunc_t hash, CompareFunc_t compare);


/// @brief Destroys the hashtable
/// @param ht HashTable_t* Pointer to the hashtable
void ht_destroy(HashTable_t *ht);


/// @brief  Inserts a key-value pair into the hashtable
/// @param ht  Pointer to the hashtable
/// @param key Pointer to the unique key 
/// @param value Pointer to the value
/// @return HT_SUCCESS if the key-value pair was inserted successfully
ht_status_t ht_insert(HashTable_t *ht, void *key, void *value);


/// @brief Replaces the value of a key-value pair in the hashtable
/// @param ht Pointer to the hashtable
/// @param key Pointer to the unique key
/// @param value Pointer to the new value
/// @return HT_SUCCESS if the key-value pair was replaced successfully
ht_status_t ht_replace(HashTable_t *ht, void *key, void *value);


/// @brief Deletes a key-value pair from the hashtable
/// @param ht Pointer to the hashtable
/// @param key Pointer to the unique key
/// @return HT_SUCCESS if the key-value pair was deleted successfully
ht_status_t ht_delete(HashTable_t *ht, void *key);

/// @brief Searches for a key-value pair in the hashtable
/// @param ht Pointer to the hashtable
/// @param key Pointer to the unique key 
/// @return A void pointer to the value if the key-value pair was found, NULL otherwise
void *ht_search(HashTable_t *ht, void *key);


/// @brief Prints the hashtable (for debugging purposes, needs to be modified for different data types)
/// @param ht HashTable_t* Pointer to the hashtable
void _ht_print(HashTable_t *ht);

/// @brief Hash function for integers
/// @param key Pointer to the key
/// @return an integer hash value
int ht_int_hash(void *key);

/// @brief Compare function for integers
/// @param key1 Pointer to the first key
/// @param key2 Pointer to the second key
/// @return Boolean value indicating whether the keys are equal
bool ht_int_compare(void *a, void *b);

/// @brief Hash function for stringss
/// @param key Pointer to the key
/// @return an integer hash value
int ht_string_hash(void *key);

/// @brief Compare function for strings
/// @param key1 Pointer to the first block of memory 
/// @param key2 Pointer to the second block of memory
/// @return Boolean value indicating whether the keys are equal
bool ht_string_compare(void *a, void *b);


#endif