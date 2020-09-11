#include "Tests/GTestWrapper/google_test.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    // run all google tests
    return RUN_ALL_TESTS();
}
