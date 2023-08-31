#include "FIFO.h"
#include <stdlib.h>

FIFO* fifo_create(int size) {
    FIFO* fifo = (FIFO*) malloc(sizeof(FIFO));
    if (!fifo) return NULL;

    fifo->entries = (CacheEntry_t*) malloc(sizeof(CacheEntry_t) * size);
    if (!fifo->entries) {
        free(fifo);
        return NULL;
    }

    fifo->size = size;
    fifo->head = 0;
    fifo->tail = 0;
    fifo->count = 0;

    return fifo;
}

static int fifo_find_key(FIFO* fifo, int key) {
    for (int i = 0; i < fifo->count; i++) {
        int index = (fifo->head + i) % fifo->size;
        if (fifo->entries[index].key == key) return index;
    }
    return -1;
}

CacheStatus fifo_put(FIFO* fifo, int key, int value) {
    if (fifo_find_key(fifo, key) != -1) {
        // Key already exists, replacing value
        int index = fifo_find_key(fifo, key);
        fifo->entries[index].value = value;
        return CACHE_OK;
    }

    if (fifo->count == fifo->size) {
        // Cache is full, evicting the oldest entry
        fifo->head = (fifo->head + 1) % fifo->size;
        fifo->count--;
    }

    fifo->entries[fifo->tail].key = key;
    fifo->entries[fifo->tail].value = value;
    fifo->tail = (fifo->tail + 1) % fifo->size;
    fifo->count++;

    return CACHE_OK;
}

CacheStatus fifo_get(FIFO* fifo, int key, int* value) {
    int index = fifo_find_key(fifo, key);
    if (index == -1) return CACHE_MISS;

    *value = fifo->entries[index].value;
    return CACHE_OK;
}


CacheStatus fifo_remove(FIFO* fifo, int key) {
    int index = fifo_find_key(fifo, key);
    if (index == -1) return CACHE_MISS;

    fifo->entries[index].key = 0;
    fifo->entries[index].value = 0;
    fifo->count--;

    return CACHE_OK;
}

bool fifo_contains(FIFO* fifo, int key) {
    return fifo_find_key(fifo, key) != -1;
}

void fifo_print(FIFO* fifo) {
    printf("FIFO Cache: ");
    for (int i = 0; i < fifo->count; i++) {
        int index = (fifo->head + i) % fifo->size;
        printf("%d -> %d, ", fifo->entries[index].key, fifo->entries[index].value);
    }
    printf("\n");
}


void fifo_destroy(FIFO* fifo) {
    if (fifo) {
        if (fifo->entries) {
            free(fifo->entries);
        }
        free(fifo);
    }
}
