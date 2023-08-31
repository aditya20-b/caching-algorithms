#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include "../utils/hashtable.h"
#include "../utils/linkedlist.h"
#define MAX_CACHE_SIZE 101  // 101 is a prime number

typedef struct CacheLine {
    int tag;
    int frequency;
    int data;
} CacheLine_t;

typedef struct LRUCache {
    int capacity;
    HashTable_t *cache;
    LinkedList_t *list;
} LRUCache_t;

typedef enum LRUCacheStatus {
    LRU_SUCCESS,
    LRU_ERROR,
    LRU_EXISTS,
    LRU_NOT_FOUND
} lru_status_t;


LRUCache_t *lru_init(int capacity, HashFunc_t hash, CompareFunc_t compare);

void lru_destroy(LRUCache_t *cache);

lru_status_t lru_insert(LRUCache_t *cache, void *key, Node *value);

void *lru_remove(LRUCache_t *cache, void *key);

void *lru_lookup(CacheLine_t *cache, void *key);



#endif