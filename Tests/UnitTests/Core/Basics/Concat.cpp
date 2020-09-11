#include "Core/Basics/Algorithms.h"
#include "Tests/GTestWrapper/google_test.h"
#include <string>
#include <vector>

class ConcatTest : public ::testing::Test
{
};

TEST_F(ConcatTest, SimpleType)
{
    std::vector<int> A{1, 2, 3};
    std::vector<int> B{4, 5};
    std::vector<int> N;

    EXPECT_EQ(algo::concat(A, B), (std::vector<int>{1, 2, 3, 4, 5}));
    EXPECT_EQ(algo::concat(A, A), (std::vector<int>{1, 2, 3, 1, 2, 3}));
    EXPECT_EQ(algo::concat(A, N), A);
    EXPECT_EQ(algo::concat(N, B), B);
}

TEST_F(ConcatTest, Struct)
{
    struct S {
        std::string nam;
        double val;
        bool operator==(const S& o) const { return nam == o.nam && val == o.val; }
    };
    using V = std::vector<S>;
    V A{{"a", 11.}};
    V B{{"b", 2.}, {"c", .3}};
    V N;

    EXPECT_EQ(algo::concat(A, B), (V{{"a", 11.}, {"b", 2.}, {"c", .3}}));
    EXPECT_EQ(algo::concat(A, A), (V{{"a", 11.}, {"a", 11.}}));
    EXPECT_EQ(algo::concat(A, N), A);
    EXPECT_EQ(algo::concat(N, B), B);
}
