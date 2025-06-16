#include "fds/string.h"

#include "test/testing.h"

TEST(test_string_basic)
{
    string_t s;

    string_of_sz(&s, "hello string");
    EXPECT_EQL(12, s.len);
    EXPECT_EQS("hello string", s.str);
    string_free(&s);
}
