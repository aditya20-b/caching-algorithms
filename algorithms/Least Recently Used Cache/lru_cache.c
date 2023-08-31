#include "lru_cache.h"
#include <stdlib.h>
#include <stdio.h>


HashTable_t *table;
LinkedList_t *list;

LRUCache_t *lru_init(int capacity, HashFunc_t hash, CompareFunc_t compare) {
    LRUCache_t *cache = (LRUCache_t *) malloc(sizeof(LRUCache_t));
    cache->capacity = capacity;
    cache->cache = ht_create(capacity * 2, hash, compare);
    cache->list = ll_create();
    return cache;
}

void lru_destroy(LRUCache_t *cache) {
    ht_destroy(cache->cache);
    ll_destroy(cache->list);
    free(cache);
}

/*
typedef struct CacheLine {
    int tag;
    int frequency;
    int data;
} CacheLine_t;
*/
lru_status_t lru_insert(LRUCache_t *cache, void *key, Node *value) {
    // first check if the capacity is full
    // if it is full, then we need to evict an item to make room for the new one
    // call lru_evict function (not implemented yet)
    // if the capacity is not full, then we can just add the new item to the cache

    lru_status_t status = LRU_SUCCESS;
    // both linkedlist and hashtables are global variables now called list and table respectively

    if (cache->list->size == cache->capacity) {
        // evict LRU
        void *lru_key = ll_remove_at(list, 0); // this function should return the key of the removed node
        ht_delete(table, lru_key);
        cache->list->size--;
    }

    if (ht_insert(cache->cache, key, value) == HT_SUCCESS) {
        ll_append(cache->list, value);
        list->size++;
    } else {
        status =LRU_ERROR;
    }
    return status;

}


void *lru_lookup(CacheLine_t *cache, void *key) {
    void *value;
    if (ht_get(table, key, &value) == HT_SUCCESS) {
        // Move to head
        move_node_to_head(list, key);
        return value;
    }
    return NULL;
}

void *lru_remove(LRUCache_t *cache, void *key) {
    void *value;
    if (ht_get(cache->list, key, &value) == HT_SUCCESS) {
        // Remove from cache
        ht_remove(cache->cache, key);
        // Remove from list
        ll_remove_data(cache->list, key);
        return value;
    }
    return NULL;
}

ll_status move_node_to_head(LinkedList_t *list, void *key) {
    ll_status status = LL_SUCCESS;
    int index = ll_index_of(list, key);
    if (index != -1) {
        ll_remove_at(list, index);
        ll_add(list, key);
    } else {
        status = LL_NOT_FOUND;
    }
    return status;
}



// lru_status_t lru_insert(CacheLine_t *cache, void *key, void *value) {
//     lru_status_t status = LRU_SUCCESS;
//     if (cache->size == cache->capacity) {
//         // Evict LRU
//         void *lru_key = ll_remove_at(cache->list, 0);
//         ht_delete(cache->cache, lru_key);
//         cache->size--;
//     }
//     if (ht_insert(cache->cache, key, value) == HT_SUCCESS) {
//         (cache->list, key);
//         cache->size++;
//     } else {
//         status = LRU_ERROR;
//     }
//     return status;
// }