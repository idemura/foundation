#include "test/testing.h"

#include <stdio.h>

struct testing_context
{
    char const *name;
    int failed;
};

struct testing_node
{
    char const *name;
    testing_func_f test;
    struct testing_node *next;
};

static struct testing_node *testing_head_node;

static void
testing_failed_test_msg(struct testing_context *ctx, char const *file, int line)
{
    fprintf(stderr, "FAILED %s: %s:%d\n", ctx->name, file, line);
}

void
testing_fail(struct testing_context *ctx, char const *file, int line)
{
    ctx->failed++;
    testing_failed_test_msg(ctx, file, line);
}

void
testing_fail_2v(
        struct testing_context *ctx, char const *file, int line, char const *value_format, ...)
{
    ctx->failed++;

    testing_failed_test_msg(ctx, file, line);

    char format_buf[80];
    snprintf(
            format_buf,
            countof(format_buf),
            "  expected: %s\n  actual:   %s\n",
            value_format,
            value_format);

    va_list va;
    va_start(va, value_format);
    vfprintf(stderr, format_buf, va);
    va_end(va);
}

bool testing_expect_eql(
        struct testing_context *ctx, char const *file, int line, long e, long v)
{
    if (e != v) {
        testing_fail_2v(ctx, file, line, "%ld", e, v);
        return false;
    }
    return true;
}

bool testing_expect_eqs(
        struct testing_context *ctx, char const *file, int line, char const *e, char const *v)
{
    if (strcmp(e, v) != 0) {
        testing_fail_2v(ctx, file, line, "%s", e, v);
        return false;
    }
    return true;
}

bool testing_expect_eqb(
        struct testing_context *ctx, char const *file, int line, bool e, bool v)
{
    if (e != v) {
        testing_fail_2v(ctx, file, line, "%d", e, v);
        return false;
    }
    return true;
}

void testing_register(char const *name, testing_func_f test)
{
    struct testing_node *node = malloc(sizeof(*node));
    node->next = testing_head_node;
    node->name = name;
    node->test = test;
    testing_head_node = node;
}

int testing_main(int argc, char **argv)
{
    int succeeded = 0;
    int failed = 0;

    struct testing_node *node = testing_head_node;
    while (node) {
        struct testing_node *t = node;

        struct testing_context ctx = {0};
        ctx.name = t->name;
        t->test(&ctx);

        if (ctx.failed) {
            failed++;
        } else {
            succeeded++;
        }

        node = node->next;
        free(t);
    }

    if (failed) {
        fprintf(stderr, "%d succeeded, %d failed\n", succeeded, failed);
        return 1;
    } else {
        fprintf(stderr, "ALL TESTS PASSED\n");
        return 0;
    }
}
