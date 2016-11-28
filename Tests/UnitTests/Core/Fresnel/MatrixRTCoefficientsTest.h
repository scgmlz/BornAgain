#ifndef MATRIXRTCOEFFICIENTSTEST_H
#define MATRIXRTCOEFFICIENTSTEST_H

#include "MatrixRTCoefficients.h"

class MatrixRTCoefficientsTest : public ::testing :: Test
{
protected:
    MatrixRTCoefficientsTest();
    virtual ~MatrixRTCoefficientsTest(){}

    MatrixRTCoefficients mrtcDefault;
};

MatrixRTCoefficientsTest::MatrixRTCoefficientsTest()
{
}

TEST_F(MatrixRTCoefficientsTest, T1plus)
{
    Eigen::Vector2cd vector = mrtcDefault.T1plus();
    EXPECT_EQ(complex_t(0.5,0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficientsTest, T1min)
{
    Eigen::Vector2cd vector = mrtcDefault.T1min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(0.5,0.0), vector(1));
}

TEST_F(MatrixRTCoefficientsTest, T2plus)
{
    Eigen::Vector2cd vector = mrtcDefault.T2plus();
    EXPECT_EQ(complex_t(0.5,0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficientsTest, T2min)
{
    Eigen::Vector2cd vector = mrtcDefault.T2min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(0.5,0.0), vector(1));
}


TEST_F(MatrixRTCoefficientsTest, R1plus)
{
    Eigen::Vector2cd vector = mrtcDefault.R1plus();
    EXPECT_EQ(complex_t(-0.5,0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficientsTest, R1min)
{
    Eigen::Vector2cd vector = mrtcDefault.R1min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(-0.5,0.0), vector(1));
}

TEST_F(MatrixRTCoefficientsTest, R2plus)
{
    Eigen::Vector2cd vector = mrtcDefault.R2plus();
    EXPECT_EQ(complex_t(-0.5,0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficientsTest, R2min)
{
    Eigen::Vector2cd vector = mrtcDefault.R2min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(-0.5,0.0), vector(1));
}

TEST_F(MatrixRTCoefficientsTest, getKz)
{
    Eigen::Vector2cd vector = mrtcDefault.getKz();
    EXPECT_EQ(complex_t(0.0,0.0), vector(0));
    EXPECT_EQ(complex_t(0.0,0.0), vector(1));
}

#endif // MATRIXRTCOEFFICIENTSTEST_H
