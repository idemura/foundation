#include "fds/memmgr.h"

void *
fds_alloc_dirty(size_t pool, size_t size)
{
    void *ptr = malloc(size);
    if (!ptr) {
        die("allocation failed: %zu", size);
    }
    return ptr;
}

void *
fds_alloc_clean(size_t pool, size_t size)
{
    void *ptr = calloc(1, size);
    if (!ptr) {
        die("allocation failed: %zu", size);
    }
    return ptr;
}

void
fds_free(size_t pool, void *ptr)
{
    free(ptr);
}
