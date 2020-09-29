#include "Core/Basics/Assert.h"
#include "Tests/GTestWrapper/google_test.h"

class TestAssert : public ::testing::Test
{
};

TEST_F(TestAssert, Assert)
{
    EXPECT_NO_THROW(ASSERT(1));
#ifndef WIN32 // Win currently dies with msg '' -- TODO verify, repair, restore test
    EXPECT_DEATH(ASSERT(0), "Assertion .* failed .*");
#endif
}
