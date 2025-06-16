#ifndef FDS_MEMMGR_H
#define FDS_MEMMGR_H

#include "port/port.h"

/// Memory manager/allocator.

static const size_t FDS_DEFAULT_POOL = 0;

inline static size_t fds_pad_long(size_t size)
{
    return (size + sizeof(long) - 1) & ~(sizeof(long) - 1);
}

// Allocate dirty memory
void *fds_alloc_dirty(size_t pool, size_t size);

// Allocate clear memory (init with 0)
void *fds_alloc_clean(size_t pool, size_t size);

// Releases allocated memory (@ptr can be NULL).
void fds_free(size_t pool, void *ptr);

#endif
