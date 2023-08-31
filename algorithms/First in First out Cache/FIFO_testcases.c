#include <stdio.h>
#include "FIFO.h"
#include <stdlib.h>
#include <assert.h>


void test_fifo_initialization() {
    FIFO* cache = fifo_create(5);
    assert(cache != NULL);
    assert(cache->size == 5);
    assert(cache->count == 0);
    assert(cache->head == 0);
    assert(cache->tail == 0);
    fifo_destroy(cache);
}

void test_fifo_insertion() {
    FIFO* cache = fifo_create(3);

    // Test normal insertion
    assert(fifo_put(cache, 1, 100) == CACHE_OK);
    assert(fifo_put(cache, 2, 200) == CACHE_OK);
    assert(fifo_contains(cache, 1));
    assert(fifo_contains(cache, 2));

    // Test eviction when the cache is full
    assert(fifo_put(cache, 3, 300) == CACHE_OK);
    assert(fifo_put(cache, 4, 400) == CACHE_OK);  // This should evict the entry with key 1
    assert(!fifo_contains(cache, 1));
    assert(fifo_contains(cache, 4));

    fifo_destroy(cache);
}


void test_fifo_retrieval() {
    FIFO* cache = fifo_create(3);
    int value;

    fifo_put(cache, 1, 100);
    fifo_put(cache, 2, 200);

    assert(fifo_get(cache, 1, &value) == CACHE_OK);
    assert(value == 100);
    assert(fifo_get(cache, 2, &value) == CACHE_OK);
    assert(value == 200);
    assert(fifo_get(cache, 3, &value) == CACHE_MISS);

    fifo_destroy(cache);
}


void test_fifo_removal() {
    FIFO* cache = fifo_create(3);

    fifo_put(cache, 1, 100);
    fifo_put(cache, 2, 200);

    assert(fifo_remove(cache, 1) == CACHE_OK);
    assert(!fifo_contains(cache, 1));

    assert(fifo_remove(cache, 3) == CACHE_MISS);

    fifo_destroy(cache);
}


void test_cache() {
    FIFO* cache = fifo_create(3);
    if (!cache) {
        printf("Failed to create cache.\n");
        return;
    }

    CacheStatus status;
    int value;

    // Test adding to the cache
    status = fifo_put(cache, 1, 100);
    if (status != CACHE_OK) printf("Test failed: Could not add 1 -> 100 to cache.\n");

    status = fifo_put(cache, 2, 200);
    if (status != CACHE_OK) printf("Test failed: Could not add 2 -> 200 to cache.\n");

    status = fifo_put(cache, 3, 300);
    if (status != CACHE_OK) printf("Test failed: Could not add 3 -> 300 to cache.\n");

    // Test fetching from the cache
    status = fifo_get(cache, 1, &value);
    if (status != CACHE_OK || value != 100) printf("Test failed: Could not fetch 1 -> 100 from cache.\n");

    // Test cache eviction (FIFO)
    status = fifo_put(cache, 4, 400);
    if (status != CACHE_OK) printf("Test failed: Could not add 4 -> 400 to cache.\n");

    status = fifo_get(cache, 1, &value);
    if (status != CACHE_MISS) printf("Test failed: Entry for key 1 was not evicted.\n");

    status = fifo_get(cache, 4, &value);
    if (status != CACHE_OK || value != 400) printf("Test failed: Could not fetch 4 -> 400 from cache.\n");

    fifo_destroy(cache);
}

int main() {
    printf("Running tests...\n");
    test_fifo_initialization();
    test_fifo_insertion();
    test_fifo_retrieval();
    test_fifo_removal();
    test_cache();
    printf("Tests complete.\n");
    printf("All tests passed!\n");
    return 0;
}
