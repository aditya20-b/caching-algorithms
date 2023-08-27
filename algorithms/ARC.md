Adaptive Replacement Cache (ARC) algorithm using hashtables and linkedlists:

1. **Data Structures**:
    - `hashtable` for key-value pairs
    - Two `linkedlists` for T1 and T2 which holds keys of the cache. T1 is for recently accessed data and T2 for frequently accessed data.
    - Two additional `linkedlists` for B1 and B2 which are "ghost lists" to hold metadata about recently evicted items.

2. **Operations**:
    - **Lookup**:
        1. Check the key in the hashtable.
        2. If found, move the key to the front of T1 or T2.
        3. If not found, handle cache miss (detailed in the next operation).
    - **Insertion**:
        1. Check if the key is in B1 or B2. If it's in B1, adaptively increase the size of T1 and decrease the size of T2 and vice versa for B2.
        2. If key is not in B1 or B2, evict from T1 or T2 depending on their sizes.
        3. Insert the new key at the front of T1.


# Using hashtables instead of linkedlists

- Two hash tables `t1` and `t2` that will store recently accessed and frequently accessed pages respectively. 
- Two linked lists `b1` and `b2` that will store recently evicted pages from `t1` and `t2` respectively.


When a request is made for a page:
1. If it's in `t1` or `t2`, it's a cache hit. Promote it to `t2` if it's not already there.
2. If it's in `b1` or `b2`, it's a cache miss but shows the cache needs to adapt. Adjust `p` accordingly.
3. If it's not in any of the structures, it's a true cache miss.

Remember:
- Whenever you replace a page from `t1` or `t2`, you should put it in `b1` or `b2` respectively.
- You need to manage sizes of `b1` and `b2`. If either gets too big (larger than `c`), you should discard from the front.

This is a broad view of ARC's implementation. You'll need to further break down each step and translate the pseudo-code into actual C code using the provided linked list and hash table functions.