#include "Core/Parametrization/ThreadInfo.h"
#include "Tests/GTestWrapper/google_test.h"

class ThreadInfoTest : public ::testing::Test
{
};

TEST_F(ThreadInfoTest, DefaultValues)
{
    ThreadInfo thread_info;
    EXPECT_EQ(1u, thread_info.n_batches);
    EXPECT_EQ(0u, thread_info.current_batch);
    EXPECT_EQ(0u, thread_info.n_threads);
}
