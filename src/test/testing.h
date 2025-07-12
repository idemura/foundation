#ifndef TEST_TESTING_H
#define TEST_TESTING_H

#include "port/port.h"

struct testing_context;

typedef void (*testing_func_f)(struct testing_context *ctx);

#define TEST(FUNC) void FUNC(struct testing_context *testing_context)

#define TEST_REGISTER(FUNC) testing_register(#FUNC, &FUNC)

#define TEST_FAIL() do{ testing_fail(testing_context, __FILE__, __LINE__); return; }while(0)

#define EXPECT_EQL(E, A) \
    do { \
        if (!testing_expect_eql(testing_context, __FILE__, __LINE__, E, A)) return; \
    } while(0)

#define EXPECT_EQS(E, A) \
    do { \
        if (!testing_expect_eqs(testing_context, __FILE__, __LINE__, E, A)) return; \
    } while(0)

#define EXPECT_TRUE(A) \
    do { \
        if (!testing_expect_eqb(testing_context, __FILE__, __LINE__, true, A)) return; \
    } while(0)

#define EXPECT_FALSE(A) \
    do { \
        if (!testing_expect_eqb(testing_context, __FILE__, __LINE__, false, A)) return; \
    } while(0)

int testing_main(int argc, char **argv);
void testing_fail(struct testing_context *ctx, char const *file, int line);
void testing_fail_cmp(
        struct testing_context *ctx, char const *file, int line, char const *value_format, ...);
bool testing_expect_eql(
        struct testing_context *ctx, char const *file, int line, long e, long v);
bool testing_expect_eqs(
        struct testing_context *ctx, char const *file, int line, char const *e, char const *v);
bool testing_expect_eqb(
        struct testing_context *ctx, char const *file, int line, bool e, bool v);
void testing_register(char const *name, testing_func_f test);

#endif
