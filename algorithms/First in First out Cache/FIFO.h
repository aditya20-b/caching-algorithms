#ifndef FIFO_H
#define FIFO_H

#include <stdbool.h>

typedef enum CacheStatus {
    CACHE_OK,
    CACHE_MISS,
    CACHE_FULL,
    CACHE_ERROR
} CacheStatus;

typedef struct CacheEntry {
    int key;
    int value;
} CacheEntry_t;

typedef struct FIFO {
    int size;
    CacheEntry_t* entries;
    int head;
    int tail;
    int count;
} FIFO;


FIFO* fifo_create(int size);

void fifo_destroy(FIFO* fifo);

CacheStatus fifo_get(FIFO* fifo, int key, int* value);

CacheStatus fifo_put(FIFO* fifo, int key, int value);

CacheStatus fifo_remove(FIFO* fifo, int key);

bool fifo_contains(FIFO* fifo, int key);

void fifo_print(FIFO* fifo);


#endif