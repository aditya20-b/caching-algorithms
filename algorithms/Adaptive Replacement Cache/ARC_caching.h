#ifndef ARC_CACHING_H
#define ARC_CACHING_H
// #include "utils/hashtable.h"
#include "../utils/hashtable.h"
#include "../utils/linkedlist.h"

typedef enum ARC_List_Type {
    T1,
    T2,
    B1,
    B2
} ARC_List_Type;

typedef enum ARC_Status {
    HIT,
    MISS,
    REJECT
} ARC_Status;


typedef struct ARC_Data {
    void *value;
    ARC_List_Type type;
} ARC_Data_t;

typedef struct ARC {
    int capacity;
    int p; // I dont even know what thsi parameter is
    HashTable_t *cache;
    LinkedList_t *t1;
    LinkedList_t *t2;
    LinkedList_t *b1;
    LinkedList_t *b2;
} ArcCache_t;



ArcCache_t *arc_init(int capacity, HashFunc_t hash, CompareFunc_t compare);
void arc_destroy(ArcCache_t *cache);

ARC_Status arc_lookup(ArcCache_t *cache, void *key, void **value); // For finding items in cache
ARC_Status arc_insert(ArcCache_t *cache, void *key, void *value);        // Insert or update an item


static void arc_adjust_p(ArcCache_t *cache, ARC_List_Type accessed_ghost); 
static void arc_replace(ArcCache_t *cache);



#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
