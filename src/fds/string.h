#ifndef FDS_STRING_H
#define FDS_STRING_H

#include "fds/memmgr.h"

/// Dynamically allocated immutable string

typedef struct {
    size_t len;
    char const *str;
} string_t;

inline static
void string_empty(string_t *s)
{
    s->len = 0;
    s->str = nullptr;
}

// Construct a string by making a copy.
void string_of(string_t *s, char const *str, size_t len);
void string_of_sz(string_t *s, char const *str);

void string_copy(string_t *s, string_t const *other);

// Release string buffer.
void string_free(string_t *s);

// Returns true if string equal to a string ending with 0.
bool string_equal_sz(string_t const *s, const char *str);

#endif
