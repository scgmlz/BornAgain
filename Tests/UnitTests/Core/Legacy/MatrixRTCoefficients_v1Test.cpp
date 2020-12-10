#include "Sample/LegacyRT/MatrixRTCoefficients_v1.h"
#include "Tests/GTestWrapper/google_test.h"

class MatrixRTCoefficients_v1Test : public ::testing::Test {
protected:
    MatrixRTCoefficients_v1 mrtcDefault;
};

TEST_F(MatrixRTCoefficients_v1Test, T1plus) {
    Eigen::Vector2cd vector = mrtcDefault.T1plus();
    EXPECT_EQ(complex_t(0.5, 0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficients_v1Test, T1min) {
    Eigen::Vector2cd vector = mrtcDefault.T1min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(0.5, 0.0), vector(1));
}

TEST_F(MatrixRTCoefficients_v1Test, T2plus) {
    Eigen::Vector2cd vector = mrtcDefault.T2plus();
    EXPECT_EQ(complex_t(0.5, 0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficients_v1Test, T2min) {
    Eigen::Vector2cd vector = mrtcDefault.T2min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(0.5, 0.0), vector(1));
}

TEST_F(MatrixRTCoefficients_v1Test, R1plus) {
    Eigen::Vector2cd vector = mrtcDefault.R1plus();
    EXPECT_EQ(complex_t(-0.5, 0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficients_v1Test, R1min) {
    Eigen::Vector2cd vector = mrtcDefault.R1min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(-0.5, 0.0), vector(1));
}

TEST_F(MatrixRTCoefficients_v1Test, R2plus) {
    Eigen::Vector2cd vector = mrtcDefault.R2plus();
    EXPECT_EQ(complex_t(-0.5, 0.0), vector(0));
    EXPECT_EQ(0.0, vector(1));
}

TEST_F(MatrixRTCoefficients_v1Test, R2min) {
    Eigen::Vector2cd vector = mrtcDefault.R2min();
    EXPECT_EQ(0.0, vector(0));
    EXPECT_EQ(complex_t(-0.5, 0.0), vector(1));
}

TEST_F(MatrixRTCoefficients_v1Test, getKz) {
    Eigen::Vector2cd vector = mrtcDefault.getKz();
    EXPECT_EQ(complex_t(0.0, 0.0), vector(0));
    EXPECT_EQ(complex_t(0.0, 0.0), vector(1));
}
