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


ARC_Status arc_insert(ArcCache_t *cache, void *key, void *value) {

    ARC_Data_t *lookup_result  = (ARC_Data_t *) ht_search(cache->cache, key); 
    
    if (lookup_result) {
        if (lookup_result->type == T2) {
            // Move to t2
            ll_remove_data(cache->t2, key);
            ll_add(cache->t2, key);
        } else {
            // Move to t1
            ll_remove_data(cache->t1, key);
            ll_add(cache->t2, key);
        }

        ht_replace(cache->cache, key, value);
            
        // Ghost hit in B1
        if (ll_search(cache->b1, key)) {
            arc_adjust_p(cache, B1);
            arc_replace(cache);
            ll_remove_data(cache->b1, key);
            
            ARC_Data_t *data = (ARC_Data_t *) malloc(sizeof(ARC_Data_t)); 
            data->value = value;
            data->type = T2;

            ht_set(cache->cache, key, data);
            ll_add(cache->t2, key);
            return MISS;
        }

        // Ghost hit in B2
        if (ll_search(cache->b2, key)) {
            arc_adjust_p(cache, B2);
            arc_replace(cache);
            ll_remove_data(cache->b2, key);
            
            ARC_Data_t *data = (ARC_Data_t *) malloc(sizeof(ARC_Data_t)); 
            data->value = value;
            data->type = T2;

            ht_set(cache->cache, key, data);
            ll_add(cache->t2, key);
            return MISS;
        }

        return HIT;
    }

    // Here we check if the cache is already full
    // If it is full, then we need to evict an item to make room for the new one

    if (cache->t1->size + cache->t2->size >= cache->capacity) {
        if (cache->t1->size > cache->p) {
            if (cache->b1->size >= cache->capacity) {
                // Evict LRU from b1
                ll_remove_at(cache->b1, 0);
            }
            void *evicted_key = ll_get_at(cache->t1, 0);
            ll_add(cache->b1, evicted_key);
            ll_remove_at(cache->t1, 0);
            ht_remove(cache->cache, evicted_key);
        } else {
            if (cache->b2->size >= cache->capacity) {
                // Evict LRU from b2
                ll_remove_at(cache->b2, 0);
            }
            void *evicted_key = ll_get_at(cache->t2, 0);
            ll_add(cache->b2, evicted_key);
            ll_remove_at(cache->t2, 0);
            ht_remove(cache->cache, evicted_key);
        }
    }



    ARC_Data_t *data = (ARC_Data_t *) malloc(sizeof(ARC_Data_t)); 
    data->value = value;
    data->type = T1;

    ht_set(cache->cache, key, data);
    ll_add(cache->t1, key);

    return MISS;
}


ARC_Status arc_lookup(ArcCache_t *cache, void *key, void **value) {
    ARC_Data_t *lookup_result = (ARC_Data_t *) ht_search(cache->cache, key);

    if (!lookup_result) {
        return MISS;
    }

    *value = lookup_result->value;

    if (lookup_result->type == T1) {
        ll_remove_data(cache->t1, key);
        lookup_result->type = T2;
        ll_add(cache->t2, key);
    } else if (lookup_result->type == T2) {
        ll_remove_data(cache->t2, key);
        ll_add(cache->t2, key);
    }

    return HIT;
}

static void arc_adjust_p(ArcCache_t *cache, ARC_List_Type accessed_ghost) {
    if (accessed_ghost == B1 && cache->t1->size > cache->p) {
        cache->p = MIN(cache->p + MAX(1, cache->b2->size / cache->b1->size), cache->capacity);
    } else if (accessed_ghost == B2 && cache->t1->size < cache->p) {
        cache->p = MAX(cache->p - MAX(1, cache->b1->size / cache->b2->size), 0);
    }
}

static void arc_replace(ArcCache_t *cache) {
    if ((cache->t1->size > 0) && (cache->t1->size > cache->p || (ll_search(cache->b2, ll_get_at(cache->t1, 0)) && cache->t1->size == cache->p))) {
        ll_remove_at(cache->t1, 0);
    } else {
        ll_remove_at(cache->t2, 0);
    }
}

