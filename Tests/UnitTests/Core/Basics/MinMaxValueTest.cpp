#include "Core/Basics/Algorithms.h"
#include "Tests/GTestWrapper/google_test.h"
#include <cmath>

class MinMaxValueTest : public ::testing::Test
{
};

TEST_F(MinMaxValueTest, MinMaxValueAlmostEq)
{
    double val;
    std::vector<double> A{0.};
    std::vector<int> C{1, 2, 3};

    val = algo::min_value(A.begin(), A.end(), [](const double& x) -> double { return x; });
    EXPECT_EQ(val, 0.);
    val = algo::max_value(A.begin(), A.end(), [](const double& x) -> double { return 2 + x; });
    EXPECT_NEAR(val, 2., 1e-15);

    val = algo::min_value(C.begin(), C.end(), [](const int& i) -> double { return i; });
    EXPECT_EQ(val, 1);
    val = algo::min_value(C.begin(), C.end(), [](const int& i) -> double { return -i; });
    EXPECT_EQ(val, -3);
    val =
        algo::min_value(C.begin(), C.end(), [](const int& i) -> double { return pow(i - 2.1, 2); });
    EXPECT_NEAR(val, 0.01, 1e-13);
    val = algo::max_value(C.begin(), C.end(), [](const int& i) -> double { return i; });
    EXPECT_EQ(val, 3);
    val = algo::max_value(C.begin(), C.end(), [](const int& i) -> double { return -i; });
    EXPECT_EQ(val, -1);
    val = algo::max_value(C.begin(), C.end(),
                          [](const int& i) -> double { return -pow(i - 2.1, 2); });
    EXPECT_NEAR(val, -0.01, 1e-13);
}
