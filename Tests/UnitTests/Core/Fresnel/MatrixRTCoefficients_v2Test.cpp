#include "Core/RT/MatrixRTCoefficients_v2.h"
#include "Tests/GTestWrapper/google_test.h"

class MatrixRTCoefficients_v2Test : public ::testing::Test
{
protected:
    MatrixRTCoefficients_v2 mrtcDefault{-1., {0., 0.}, kvector_t{0.0, 0.0, 0.0}};
};

TEST_F(MatrixRTCoefficients_v2Test, T1plus)
{
    Eigen::Vector2cd vector = mrtcDefault.T1plus();
    EXPECT_EQ(complex_t(0.5, 0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficients_v2Test, T1min)
{
    Eigen::Vector2cd vector = mrtcDefault.T1min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(0.5, 0.0), vector(1));
}

TEST_F(MatrixRTCoefficients_v2Test, T2plus)
{
    Eigen::Vector2cd vector = mrtcDefault.T2plus();
    EXPECT_EQ(complex_t(0.5, 0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficients_v2Test, T2min)
{
    Eigen::Vector2cd vector = mrtcDefault.T2min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(0.5, 0.0), vector(1));
}

TEST_F(MatrixRTCoefficients_v2Test, R1plus)
{
    Eigen::Vector2cd vector = mrtcDefault.R1plus();
    EXPECT_EQ(complex_t(-0.5, 0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficients_v2Test, R1min)
{
    Eigen::Vector2cd vector = mrtcDefault.R1min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(-0.5, 0.0), vector(1));
}

TEST_F(MatrixRTCoefficients_v2Test, R2plus)
{
    Eigen::Vector2cd vector = mrtcDefault.R2plus();
    EXPECT_EQ(complex_t(-0.5, 0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficients_v2Test, R2min)
{
    Eigen::Vector2cd vector = mrtcDefault.R2min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(-0.5, 0.0), vector(1));
}

TEST_F(MatrixRTCoefficients_v2Test, getKz)
{
    Eigen::Vector2cd vector = mrtcDefault.getKz();
    EXPECT_EQ(complex_t(0.0, 0.0), vector(0));
    EXPECT_EQ(complex_t(0.0, 0.0), vector(1));
}
