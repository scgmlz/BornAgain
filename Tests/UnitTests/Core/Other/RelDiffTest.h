#ifndef RELDIFFTEST_H
#define RELDIFFTEST_H

#include "Numeric.h"
#include <algorithm>

class RelDiffTest : public ::testing::Test
{
 protected:
    RelDiffTest() {}
    virtual ~RelDiffTest() {}
};


TEST_F(RelDiffTest, RelDiffAlmostEq)
{
    EXPECT_TRUE( Numeric::areAlmostEqual(+1e+120, +1e+120, 1.) );
    EXPECT_TRUE( Numeric::areAlmostEqual(+1e-120, +1e-120, 1.) );
    EXPECT_TRUE( Numeric::areAlmostEqual(0, 0, 1.) );
    EXPECT_TRUE( Numeric::areAlmostEqual(-1e-120, -1e-120, 1.) );
    EXPECT_TRUE( Numeric::areAlmostEqual(-1e+120, -1e+120, 1.) );

    EXPECT_FALSE( Numeric::areAlmostEqual(+1e+120, 0, 1.) );
//    EXPECT_FALSE( Numeric::areAlmostEqual(+1e-120, 0, 1.) );
//    EXPECT_FALSE( Numeric::areAlmostEqual(-1e-120, 0, 1.) );
    EXPECT_FALSE( Numeric::areAlmostEqual(-1e+120, 0, 1.) );
}

#endif // RELDIFFTEST_H
