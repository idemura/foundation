#include "fds/string.h"

const char string_empty_buf[0];

void string_of(string_t *s, const char *str, size_t len)
{
    if (len == 0) {
        s->str = nullptr;
    } else {
        s->str = fds_alloc_dirty(FDS_DEFAULT_POOL, len + 1);
        s->len = len;

        // Copy string data
        memcpy(s->str, str, len + 1);
    }
}

void string_of_sz(string_t *s, const char *str)
{
    string_of(s, str, strlen(str));
}

void string_copy(string_t *s, string_t const *other)
{
    string_of(s, other->str, s->len);
}

void string_free(string_t *s)
{
    fds_free(FDS_DEFAULT_POOL, s->str);
    s->len = 0;
    s->str = nullptr;
}

bool string_equal_sz(string_t const *s, const char *str)
{
    size_t len = strlen(str);
    return s->len == len && memcmp(s->str, str, len) == 0;
}
