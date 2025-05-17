## Minishell: memory pooling notes

Memory pooling is a technique used to optimize memory allocation and deallocation by pre-allocating a fixed amount of memory and then managing that memory efficiently for reuse. Instead of repeatedly requesting memory from the system (e.g., with `malloc` or `free`), a memory pool allows you to allocate and free memory from a pre-defined block, reducing overhead and fragmentation.

While this technique has not been used, its study has been interesting.

---

### **Why use memory pooling?**

1. **Performance:** Allocating memory from the system is slow. Memory pooling reduces the overhead by managing allocations internally.
2. **Fragmentation:** By using a fixed block of memory, you minimize fragmentation in memory usage.
3. **Deterministic behavior:** Since allocations happen within the pool, the operation becomes predictable in terms of time and space.

---

### **How does it work?**

1. **Initialization:**
    - A large block of memory is allocated at the start (e.g., using `malloc`).
    - This block is divided into smaller chunks of a fixed size.
2. **Allocation:**
    - Instead of calling `malloc`, the program retrieves a free chunk from the pool.
    - The pool tracks which chunks are in use and which are free (e.g., using a linked list or a bitmap).
3. **Deallocation:**
    - When memory is no longer needed, it is returned to the pool, marking the chunk as free.
    - This makes the chunk available for future allocations.

---

### **Basic implementation in C**

Here’s a simplified example of a memory pool implementation:

```c
#include <stdlib.h>
#include <stdio.h>

typedef struct MemoryPool {
    size_t chunk_size;
    size_t total_chunks;
    void *memory_block;
    void **free_list;
    size_t free_index;
} MemoryPool;

MemoryPool *create_pool(size_t chunk_size, size_t total_chunks) {
    MemoryPool *pool = malloc(sizeof(MemoryPool));
    if (!pool) return NULL;

    pool->chunk_size = chunk_size;
    pool->total_chunks = total_chunks;
    pool->memory_block = malloc(chunk_size * total_chunks);
    if (!pool->memory_block) {
        free(pool);
        return NULL;
    }

    pool->free_list = malloc(sizeof(void *) * total_chunks);
    if (!pool->free_list) {
        free(pool->memory_block);
        free(pool);
        return NULL;
    }

    for (size_t i = 0; i < total_chunks; i++) {
        pool->free_list[i] = (char *)pool->memory_block + i * chunk_size;
    }

    pool->free_index = total_chunks;

    return pool;
}

void *allocate_from_pool(MemoryPool *pool) {
    if (pool->free_index == 0) return NULL; // No free memory
    return pool->free_list[--pool->free_index];
}

void free_to_pool(MemoryPool *pool, void *ptr) {
    pool->free_list[pool->free_index++] = ptr;
}

void destroy_pool(MemoryPool *pool) {
    free(pool->memory_block);
    free(pool->free_list);
    free(pool);
}

int main() {
    MemoryPool *pool = create_pool(32, 10); // 10 chunks of 32 bytes
    if (!pool) {
        printf("Failed to create memory pool\n");
        return 1;
    }

    void *ptr1 = allocate_from_pool(pool);
    void *ptr2 = allocate_from_pool(pool);

    printf("Allocated: %p and %p\n", ptr1, ptr2);

    free_to_pool(pool, ptr1);
    free_to_pool(pool, ptr2);

    destroy_pool(pool);
    return 0;
}

```

---

### **Advantages of memory pooling**

1. **Speed:** Allocation and deallocation are faster since there is no need to interact with the OS.
2. **Reduced Fragmentation:** Memory is managed in a contiguous block.
3. **Customizability:** Pools can be tailored to specific application needs (e.g., chunk sizes, alignment).

### **Disadvantages**

1. **Memory Overhead:** Unused chunks in the pool still occupy memory.
2. **Limited Flexibility:** The pool size is fixed, so it cannot handle unexpected large memory demands.

---

Memory pooling is especially useful in embedded systems, real-time applications, and high-performance software where predictable memory management is critical.