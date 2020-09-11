#include "Core/Scattering/ZLimits.h"
#include "Tests/GTestWrapper/google_test.h"
#include <stdexcept>

class ZLimitsTest : public ::testing::Test
{
};

TEST_F(ZLimitsTest, ZLimitsDefaultConstructor)
{
    ZLimits limits;
    EXPECT_TRUE(limits.lowerLimit().m_limitless);
    EXPECT_TRUE(limits.upperLimit().m_limitless);
}

TEST_F(ZLimitsTest, ZLimitsMinMaxConstructor)
{
    ZLimits limits{-4.0, 1.5};
    EXPECT_FALSE(limits.lowerLimit().m_limitless);
    EXPECT_EQ(-4.0, limits.lowerLimit().m_value);
    EXPECT_FALSE(limits.upperLimit().m_limitless);
    EXPECT_EQ(1.5, limits.upperLimit().m_value);
    limits = ZLimits{-4.0, -4.0};
    EXPECT_FALSE(limits.lowerLimit().m_limitless);
    EXPECT_EQ(-4.0, limits.lowerLimit().m_value);
    EXPECT_FALSE(limits.upperLimit().m_limitless);
    EXPECT_EQ(-4.0, limits.upperLimit().m_value);
    EXPECT_THROW(limits = ZLimits(-4.0, -5.0), std::runtime_error);
}

TEST_F(ZLimitsTest, ZLimitsOneSidedLimitConstructor)
{
    ZLimits limits1{{true, -4.0}, {true, 1.5}};
    ZLimits limits2{{false, -4.0}, {true, 1.5}};
    ZLimits limits3{{true, -4.0}, {false, 1.5}};
    ZLimits limits4{{false, -4.0}, {false, 1.5}};
    EXPECT_TRUE(limits1.lowerLimit().m_limitless);
    EXPECT_TRUE(limits1.upperLimit().m_limitless);
    EXPECT_FALSE(limits2.lowerLimit().m_limitless);
    EXPECT_EQ(-4.0, limits2.lowerLimit().m_value);
    EXPECT_TRUE(limits2.upperLimit().m_limitless);
    EXPECT_TRUE(limits3.lowerLimit().m_limitless);
    EXPECT_FALSE(limits3.upperLimit().m_limitless);
    EXPECT_EQ(1.5, limits3.upperLimit().m_value);
    EXPECT_FALSE(limits4.lowerLimit().m_limitless);
    EXPECT_EQ(-4.0, limits4.lowerLimit().m_value);
    EXPECT_FALSE(limits4.upperLimit().m_limitless);
    EXPECT_EQ(1.5, limits4.upperLimit().m_value);
    EXPECT_NO_THROW(ZLimits limits5({true, -4.0}, {true, -5.0}));
    EXPECT_NO_THROW(ZLimits limits6({false, -4.0}, {true, -5.0}));
    EXPECT_NO_THROW(ZLimits limits7({true, -4.0}, {false, -5.0}));
    EXPECT_THROW(ZLimits limits8({false, -4.0}, {false, -5.0}), std::runtime_error);
}

TEST_F(ZLimitsTest, ZLimitsIsFinite)
{
    ZLimits limitless;
    ZLimits poslimit({false, 0}, {true, 0});
    ZLimits neglimit({true, 0}, {false, -1});
    ZLimits finite(-3.0, 5.0);
    EXPECT_FALSE(limitless.isFinite());
    EXPECT_FALSE(poslimit.isFinite());
    EXPECT_FALSE(neglimit.isFinite());
    EXPECT_TRUE(finite.isFinite());
}

TEST_F(ZLimitsTest, ZLimitsConvexHull)
{
    ZLimits limitless;
    ZLimits poslimit1({false, 0}, {true, 0});
    ZLimits poslimit2({false, 4}, {true, 0});
    ZLimits neglimit1({true, 0}, {false, -1});
    ZLimits neglimit2({true, 0}, {false, 5});
    ZLimits finite1(-3.0, 5.0);
    ZLimits finite2(-1.0, 6.0);
    ZLimits finite3(7.0, 15.0);
    ZLimits limits;

    limits = ConvexHull(limitless, limitless);
    EXPECT_EQ(limitless, limits);

    limits = ConvexHull(limitless, poslimit1);
    EXPECT_EQ(limitless, limits);
    limits = ConvexHull(poslimit1, limitless);
    EXPECT_EQ(limitless, limits);

    limits = ConvexHull(limitless, neglimit1);
    EXPECT_EQ(limitless, limits);
    limits = ConvexHull(neglimit1, limitless);
    EXPECT_EQ(limitless, limits);

    limits = ConvexHull(limitless, finite1);
    EXPECT_EQ(limitless, limits);
    limits = ConvexHull(finite1, limitless);
    EXPECT_EQ(limitless, limits);

    limits = ConvexHull(poslimit1, poslimit2);
    EXPECT_EQ(poslimit1, limits);
    limits = ConvexHull(poslimit2, poslimit1);
    EXPECT_EQ(poslimit1, limits);

    limits = ConvexHull(poslimit1, neglimit1);
    EXPECT_EQ(limitless, limits);
    limits = ConvexHull(neglimit1, poslimit1);
    EXPECT_EQ(limitless, limits);

    limits = ConvexHull(poslimit1, finite1);
    EXPECT_EQ(ZLimits({false, -3}, {true, 0}), limits);
    limits = ConvexHull(finite1, poslimit1);
    EXPECT_EQ(ZLimits({false, -3}, {true, 0}), limits);

    limits = ConvexHull(neglimit1, neglimit2);
    EXPECT_EQ(neglimit2, limits);
    limits = ConvexHull(neglimit2, neglimit1);
    EXPECT_EQ(neglimit2, limits);

    limits = ConvexHull(neglimit1, finite1);
    EXPECT_EQ(ZLimits({true, 0}, {false, 5}), limits);
    limits = ConvexHull(finite1, neglimit1);
    EXPECT_EQ(ZLimits({true, 0}, {false, 5}), limits);

    limits = ConvexHull(finite1, finite2);
    EXPECT_EQ(ZLimits(-3, 6), limits);
    limits = ConvexHull(finite2, finite1);
    EXPECT_EQ(ZLimits(-3, 6), limits);

    limits = ConvexHull(finite1, finite3);
    EXPECT_EQ(ZLimits(-3, 15), limits);
    limits = ConvexHull(finite3, finite1);
    EXPECT_EQ(ZLimits(-3, 15), limits);
}
