#include "Core/Tools/Precomputed.h"
#include "Tests/GTestWrapper/google_test.h"
#include <memory>

namespace
{
constexpr auto ReciprocalFactorialArray = Precomputed::GenerateReciprocalFactorialArray<171>();
}

class PrecomputedTest : public ::testing::Test
{
};

TEST_F(PrecomputedTest, ReciprocalFactorial)
{
    const double eps = 2.3e-16; // about the machine precision
    EXPECT_TRUE(ReciprocalFactorialArray.size() > 150);
    EXPECT_DOUBLE_EQ(ReciprocalFactorialArray[0], 1.);
    EXPECT_DOUBLE_EQ(ReciprocalFactorialArray[1], 1.);
    EXPECT_DOUBLE_EQ(ReciprocalFactorialArray[2], 0.5);
    EXPECT_DOUBLE_EQ(ReciprocalFactorialArray[3], 1.0 / 6);
    /* the following disabled because tgamma is too unprecise under
       old versions of glibc (at leat up to 2.12, but less than 2.22)
    for( size_t k=4; k<precomputed.factorial.size(); ++k )
        EXPECT_NEAR(precomputed.factorial[k], tgamma(k+1.), 12*eps*tgamma(k+1.) );
    */
    EXPECT_NEAR(ReciprocalFactorialArray[150], 1.75027620692601519e-263,
                4 * eps * ReciprocalFactorialArray[150]);
}
