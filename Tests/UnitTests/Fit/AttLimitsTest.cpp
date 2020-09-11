#include "Fit/Tools/AttLimits.h"
#include "Tests/GTestWrapper/google_test.h"

class AttLimitsTest : public ::testing::Test
{
};

TEST_F(AttLimitsTest, InitialState)
{
    AttLimits limits;
    EXPECT_FALSE(limits.isFixed());
    EXPECT_FALSE(limits.isLimited());
    EXPECT_FALSE(limits.isUpperLimited());
    EXPECT_FALSE(limits.isLowerLimited());
    EXPECT_TRUE(limits.isLimitless());
}

TEST_F(AttLimitsTest, LowerLimited)
{
    AttLimits limits = AttLimits::lowerLimited(1.0);
    EXPECT_FALSE(limits.isFixed());
    EXPECT_FALSE(limits.isLimited());
    EXPECT_FALSE(limits.isUpperLimited());
    EXPECT_TRUE(limits.isLowerLimited());
    EXPECT_FALSE(limits.isLimitless());
    EXPECT_EQ(1.0, limits.lowerLimit());
    EXPECT_EQ(0.0, limits.upperLimit());
}

TEST_F(AttLimitsTest, UpperLimited)
{
    AttLimits limits = AttLimits::upperLimited(1.0);
    EXPECT_FALSE(limits.isFixed());
    EXPECT_FALSE(limits.isLimited());
    EXPECT_TRUE(limits.isUpperLimited());
    EXPECT_FALSE(limits.isLowerLimited());
    EXPECT_FALSE(limits.isLimitless());
    EXPECT_EQ(0.0, limits.lowerLimit());
    EXPECT_EQ(1.0, limits.upperLimit());
}

TEST_F(AttLimitsTest, Fixed)
{
    AttLimits limits = AttLimits::fixed();
    EXPECT_TRUE(limits.isFixed());
    EXPECT_FALSE(limits.isLimited());
    EXPECT_FALSE(limits.isUpperLimited());
    EXPECT_FALSE(limits.isLowerLimited());
    EXPECT_FALSE(limits.isLimitless());
    EXPECT_EQ(0.0, limits.lowerLimit());
    EXPECT_EQ(0.0, limits.upperLimit());
}

TEST_F(AttLimitsTest, Limited)
{
    AttLimits limits = AttLimits::limited(1.0, 2.0);
    EXPECT_FALSE(limits.isFixed());
    EXPECT_TRUE(limits.isLimited());
    EXPECT_FALSE(limits.isUpperLimited());
    EXPECT_FALSE(limits.isLowerLimited());
    EXPECT_FALSE(limits.isLimitless());
    EXPECT_EQ(1.0, limits.lowerLimit());
    EXPECT_EQ(2.0, limits.upperLimit());

    // making it fixed, this should remove limits
    limits.setFixed(true);
    EXPECT_TRUE(limits.isFixed());
    EXPECT_FALSE(limits.isLimited());
    EXPECT_FALSE(limits.isUpperLimited());
    EXPECT_FALSE(limits.isLowerLimited());
    EXPECT_FALSE(limits.isLimitless());
    EXPECT_EQ(0.0, limits.lowerLimit());
    EXPECT_EQ(0.0, limits.upperLimit());
}
