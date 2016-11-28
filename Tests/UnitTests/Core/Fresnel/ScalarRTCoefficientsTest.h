#ifndef SCALARRTCOEFFICIENTSTEST_H
#define SCALARRTCOEFFICIENTSTEST_H

#include "ScalarRTCoefficients.h"

class ScalarRTCoefficientsTest : public ::testing :: Test
{
protected:
    ScalarRTCoefficientsTest();
    virtual ~ScalarRTCoefficientsTest(){}

    ScalarRTCoefficients scrtDefault;
    ScalarRTCoefficients scrtCustom;

};

ScalarRTCoefficientsTest::ScalarRTCoefficientsTest()
{
    scrtCustom.lambda = complex_t(1.0, 1.0);
    scrtCustom.kz = complex_t(1.0, 1.0);
    scrtCustom.t_r(0) = complex_t(0.0, 0.5);
    scrtCustom.t_r(1) = complex_t(1.0, 0.5);
}

TEST_F(ScalarRTCoefficientsTest, T1plus)
{
    Eigen::Vector2cd vector = scrtDefault.T1plus();
    EXPECT_EQ(complex_t(0.0,0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));

    Eigen::Vector2cd vector2 = scrtCustom.T1plus();
    EXPECT_EQ(complex_t(0.0,0.0), vector2(0));
    EXPECT_EQ(0.0, vector2(1));
}

TEST_F(ScalarRTCoefficientsTest, T1min)
{
    Eigen::Vector2cd vector = scrtDefault.T1min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(1.0,0.0), vector(1));

    Eigen::Vector2cd vector2 = scrtCustom.T1min();
    EXPECT_EQ(0.0, vector2(0));
    EXPECT_EQ(complex_t(0.0,0.5), vector2(1));
}

TEST_F(ScalarRTCoefficientsTest, T2plus)
{
    Eigen::Vector2cd vector = scrtDefault.T2plus();
    EXPECT_EQ(complex_t(1.0,0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));

    Eigen::Vector2cd vector2 = scrtCustom.T2plus();
    EXPECT_EQ(complex_t(0.0, 0.5), vector2(0));
    EXPECT_EQ(0.0, vector2(1));
}

TEST_F(ScalarRTCoefficientsTest, T2min)
{
    Eigen::Vector2cd vector = scrtDefault.T2min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(0.0,0.0), vector(1));

    Eigen::Vector2cd vector2 = scrtCustom.T2min();
    EXPECT_EQ(0.0, vector2(0));
    EXPECT_EQ(complex_t(0.0,0.0), vector2(1));
}


TEST_F(ScalarRTCoefficientsTest, R1plus)
{
    Eigen::Vector2cd vector = scrtDefault.R1plus();
    EXPECT_EQ(complex_t(0.0,0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));

    Eigen::Vector2cd vector2 = scrtCustom.R1plus();
    EXPECT_EQ(complex_t(0.0,0.0), vector2(0));
    EXPECT_EQ(0.0, vector2(1));
}

TEST_F(ScalarRTCoefficientsTest, R1min)
{
    Eigen::Vector2cd vector = scrtDefault.R1min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(0.0,0.0), vector(1));

    Eigen::Vector2cd vector2 = scrtCustom.R1min();
    EXPECT_EQ(0.0, vector2(0));
    EXPECT_EQ(complex_t(1.0,0.5), vector2(1));
}

TEST_F(ScalarRTCoefficientsTest, R2plus)
{
    Eigen::Vector2cd vector = scrtDefault.R2plus();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(0.0, vector(1));

    Eigen::Vector2cd vector2 = scrtCustom.R2plus();
    EXPECT_EQ(complex_t(1.0,0.5), vector2(0));
    EXPECT_EQ(0.0, vector2(1));
}

TEST_F(ScalarRTCoefficientsTest, R2min)
{
    Eigen::Vector2cd vector = scrtDefault.R2min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(0.0,0.0), vector(1));

    Eigen::Vector2cd vector2 = scrtCustom.R2min();
    EXPECT_EQ(0.0, vector2(0));
    EXPECT_EQ(complex_t(0.0,0.0), vector2(1));
}

TEST_F(ScalarRTCoefficientsTest, getKz)
{
    Eigen::Vector2cd vector = scrtDefault.getKz();
    EXPECT_EQ(complex_t(0.0,0.0), vector(0));
    EXPECT_EQ(complex_t(0.0,0.0), vector(1));

    Eigen::Vector2cd vector2 = scrtCustom.getKz();
    EXPECT_EQ(complex_t(1.0,1.0), vector2(0));
    EXPECT_EQ(complex_t(1.0,1.0), vector2(1));
}

TEST_F(ScalarRTCoefficientsTest, getScalar)
{
    EXPECT_EQ(complex_t(1.0,0.0), scrtDefault.getScalarT());
    EXPECT_EQ(complex_t(0.0,0.0), scrtDefault.getScalarR());
    EXPECT_EQ(complex_t(0.0,0.0), scrtDefault.getScalarKz());

    EXPECT_EQ(complex_t(0.0,0.5), scrtCustom.getScalarT());
    EXPECT_EQ(complex_t(1.0,0.5), scrtCustom.getScalarR());
    EXPECT_EQ(complex_t(1.0,1.0), scrtCustom.getScalarKz());
}

#endif // SCALARRTCOEFFICIENTSTEST_H
