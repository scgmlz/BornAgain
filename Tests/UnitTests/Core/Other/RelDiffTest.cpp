#include "Fit/TestEngine/Numeric.h"
#include "Tests/GTestWrapper/google_test.h"
#include <algorithm>

class RelDiffTest : public ::testing::Test
{
};

TEST_F(RelDiffTest, RelDiffAlmostEq)
{
    EXPECT_TRUE(Numeric::AreAlmostEqual(+1e+120, +1e+120, 1.));
    EXPECT_TRUE(Numeric::AreAlmostEqual(+1e-120, +1e-120, 1.));
    EXPECT_TRUE(Numeric::AreAlmostEqual(0, 0, 1.));
    EXPECT_TRUE(Numeric::AreAlmostEqual(-1e-120, -1e-120, 1.));
    EXPECT_TRUE(Numeric::AreAlmostEqual(-1e+120, -1e+120, 1.));

    EXPECT_FALSE(Numeric::AreAlmostEqual(+1e+120, 0, 1.));
    EXPECT_FALSE(Numeric::AreAlmostEqual(-1e+120, 0, 1.));
}
