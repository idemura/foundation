#include "test/testing.h"

TEST(test_string_basic);

int
main(int argc, char **argv)
{
    TEST_REGISTER(test_string_basic);
    return testing_main(argc, argv);
}
