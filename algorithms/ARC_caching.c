#include <stdio.h>
#include <stdlib.h>
#include "ARC_caching.h"


ArcCache_t *arc_init(int capacity, HashFunc_t hash, CompareFunc_t compare) {
    ArcCache_t *cache = malloc(sizeof(ArcCache_t));
    cache->capacity = capacity;
    cache->p = 0;
    cache->cache = ht_create(capacity * 2, hash, compare); // Twice the capacity of the cache just for ghost entries (B1 and B2)
    cache->t1 = ll_create();
    cache->t2 = ll_create();
    cache->b1 = ll_create();
    cache->b2 = ll_create();
    return cache;
}

void arc_destroy(ArcCache_t *cache) {
    ht_destroy(cache->cache);
    ll_destroy(cache->t1);
    ll_destroy(cache->t2);
    ll_destroy(cache->b1);
    ll_destroy(cache->b2);
    free(cache);
}


ht_status_t arc_insert(ArcCache_t *cache, ARC_Data_t *data) {    
    if (ht_search(cache, data->key)) {
        // Replace the value if the key already exists
        ht_replace(cache->cache, data->key, data->value);
        // Move to t2
        ll_remove_data(cache->t1, data->key);
        ll_add(cache->t2, data->key);
    } else {
        // Check if t1 is full
        if (cache->t1->size == cache->capacity) {
            // Evict LRU from t1
            ll_remove_at(cache->t1, 0);
        } else {
            // Check if cache is full
            if (cache->t1->size + cache->b1->size + cache->t2->size + cache->b2->size >= cache->capacity) {
                // Evict LRU from b1
                ll_remove_at(cache->b1, 0);
            }
        }
        // Add to t1
        ll_add(cache->t1, data->key);
        // Add to cache
        ht_set(cache->cache, data->key, data->value);
    }
}


















// ARC_Status arc_lookup(ArcCache_t *cache, void *key, void **value) {
//     if (ht_get(cache->cache, key, value) == HT_SUCCESS) {
//         // Move to t2
//         ll_remove_data(cache->t1, key);
//         ll_add(cache->t2, key);
//         return HIT;
//     } else {
//         // Check if in b1
//         if (ll_remove_data(cache->b1, key) == LL_SUCCESS) {
//             // Move to t2
//             ll_add(cache->t2, key);
//             return MISS;
//         } else {
//             // Check if in b2
//             if (ll_remove_data(cache->b2, key) == LL_SUCCESS) {
//                 // Move to t2
//                 ll_add(cache->t2, key);
//                 return MISS;
//             } else {
//                 // Check if t1 is empty
//                 if (cache->t1->size + cache->b1->size == cache->capacity) {
//                     // Check if t1 is empty
//                     if (cache->t1->size < cache->capacity) {
//                         // Evict LRU from t1
//                         ll_remove_at(cache->t1, 0);
//                     } else {
//                         // Evict LRU from b1
//                         ll_remove_at(cache->b1, 0);
//                     }
//                 } else {
//                     // Check if cache is full
//                     if (cache->t1->size + cache->b1->size + cache->t2->size + cache->b2->size >= cache->capacity) {
//                         // Evict LRU from b2
//                         ll_remove_at(cache->b2, 0);
//                     }
//                 }
//                 return REJECT;
//             }
//         }
//     }
// }


// void arc_insert(ArcCache_t *cache, void *key, void *value) {
//     void *old_value;
//     if (ht_get(cache->cache, key, &old_value) == HT_SUCCESS) {
//         // Update value
//         ht_set(cache->cache, key, value);
//         // Move to t2
//         ll_remove_data(cache->t1, key);
//         ll_add(cache->t2, key);
//     } else {
//         // Check if t1 is full
//         if (cache->t1->size == cache->capacity) {
//             // Evict LRU from t1
//             ll_remove_at(cache->t1, 0);
//         } else {
//             // Check if cache is full
//             if (cache->t1->size + cache->b1->size + cache->t2->size + cache->b2->size >= cache->capacity) {
//                 // Evict LRU from b1
//                 ll_remove_at(cache->b1, 0);
//             }
//         }
//         // Add to t1
//         ll_add(cache->t1, key);
//         // Add to cache
//         ht_set(cache->cache, key, value);
//     }
// }


// void arc_remove(ArcCache_t *cache, void *key) {
//     void *value;
//     if (ht_get(cache->cache, key, &value) == HT_SUCCESS) {
//         // Remove from cache
//         ht_remove(cache->cache, key);
//         // Check if in t1
//         if (ll_remove_data(cache->t1, key) == LL_SUCCESS) {
//             // Add to b1
//             ll_add(cache->b1, key);
//         } else {
//             // Check if in t2
//             if (ll_remove_data(cache->t2, key) == LL_SUCCESS) {
//                 // Add to b2
//                 ll_add(cache->b2, key);
//             }
//         }
//     }
// }


// void arc_print(ArcCache_t *cache) {
//     printf("ARC Cache:\n");
//     printf("Capacity: %d\n", cache->capacity);
//     printf("p: %d\n", cache->p);
//     printf("Cache:\n");
//     ht_print(cache->cache);
//     printf("T1:\n");
//     ll_print(cache->t1);
//     printf("T2:\n");
//     ll_print(cache->t2);
//     printf("B1:\n");
//     ll_print(cache->b1);
//     printf("B2:\n");
//     ll_print(cache->b2);
//     printf("\n");
// }


// int main() {
//     ArcCache_t *cache = arc_init(5);
//     arc_print(cache);
// }