#ifndef PRECOMPUTEDTEST_H
#define PRECOMPUTEDTEST_H

#include "Precomputed.h"
#include <memory>

class PrecomputedTest : public ::testing::Test
{
public:
};

TEST_F(PrecomputedTest, Factorial)
{
    const double eps = 2.3e-16; // about the machine precision
    auto& precomputed = Precomputed::instance();
    EXPECT_TRUE(precomputed.factorial.size()>150);
    EXPECT_DOUBLE_EQ(precomputed.factorial[0], 1.);
    EXPECT_DOUBLE_EQ(precomputed.factorial[1], 1.);
    EXPECT_DOUBLE_EQ(precomputed.factorial[2], 2.);
    EXPECT_DOUBLE_EQ(precomputed.factorial[3], 6.);
    /* the following disabled because tgamma is too unprecise under
       old versions of glibc (at leat up to 2.12, but less than 2.22)
    for( size_t k=4; k<precomputed.factorial.size(); ++k )
        EXPECT_NEAR(precomputed.factorial[k], tgamma(k+1.), 12*eps*tgamma(k+1.) );
    */
    EXPECT_NEAR(precomputed.factorial[150], 5.71338395644585459e262, 4*eps*precomputed.factorial[150]);
}

#endif // PRECOMPUTEDTEST_H
