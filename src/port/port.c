#include "port/port.h"

#include <stdio.h>

static_assert(sizeof(long) == 8, "64 bit system required");

noreturn
void die(const char *format, ...)
{
    fprintf(stderr, "Fatal error: ");

    va_list va;
    va_start(va, format);
    vfprintf(stderr, format, va);
    va_end(va);

    fprintf(stderr, "\n");

    exit(1);
}
