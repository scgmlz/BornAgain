#include "Core/SimulationElement/PolarizationHandler.h"
#include "Core/Vector/EigenCore.h"
#include "Tests/GTestWrapper/google_test.h"

class PolarizationHandlerTest : public ::testing::Test
{
protected:
    PolarizationHandlerTest();

    Eigen::Matrix2cd identity;
    Eigen::Matrix2cd test_matrix;

private:
    Eigen::Matrix2cd testMatrix();
};

PolarizationHandlerTest::PolarizationHandlerTest()
    : identity(Eigen::Matrix2cd::Identity()), test_matrix(testMatrix())
{
}

Eigen::Matrix2cd PolarizationHandlerTest::testMatrix()
{
    Eigen::Matrix2cd result;
    result << 0, 1, 1, 0;
    return result;
}

TEST_F(PolarizationHandlerTest, InitialState)
{
    PolarizationHandler handler;
    EXPECT_EQ(identity / 2.0, handler.getPolarization());
    EXPECT_EQ(identity, handler.getAnalyzerOperator());
}

TEST_F(PolarizationHandlerTest, SettersGetters)
{
    PolarizationHandler handler;
    handler.setAnalyzerOperator(test_matrix);
    EXPECT_EQ(test_matrix, handler.getAnalyzerOperator());
    handler.setPolarization(test_matrix);
    EXPECT_EQ(test_matrix, handler.getPolarization());
}

TEST_F(PolarizationHandlerTest, Swap)
{
    PolarizationHandler handler;
    PolarizationHandler handler2;

    handler.setPolarization(test_matrix);
    handler2.swapContent(handler);

    EXPECT_EQ(test_matrix, handler2.getPolarization());
    EXPECT_EQ(identity / 2.0, handler.getPolarization());

    handler.setAnalyzerOperator(test_matrix);
    handler2.swapContent(handler);

    EXPECT_EQ(test_matrix, handler2.getAnalyzerOperator());
    EXPECT_EQ(identity, handler.getAnalyzerOperator());

    handler.swapContent(handler);

    EXPECT_EQ(identity, handler.getAnalyzerOperator());
    EXPECT_EQ(test_matrix, handler.getPolarization());
}

TEST_F(PolarizationHandlerTest, CopyMoveAssign)
{
    PolarizationHandler handler;

    handler.setPolarization(test_matrix);
    handler.setAnalyzerOperator(test_matrix);

    PolarizationHandler handler2 = handler;

    EXPECT_EQ(test_matrix, handler2.getPolarization());
    EXPECT_EQ(test_matrix, handler2.getAnalyzerOperator());
    EXPECT_EQ(test_matrix, handler.getPolarization());
    EXPECT_EQ(test_matrix, handler.getAnalyzerOperator());

    PolarizationHandler handler3;
    handler3 = handler2;

    EXPECT_EQ(test_matrix, handler3.getPolarization());
    EXPECT_EQ(test_matrix, handler3.getAnalyzerOperator());
    EXPECT_EQ(test_matrix, handler2.getPolarization());
    EXPECT_EQ(test_matrix, handler2.getAnalyzerOperator());

    PolarizationHandler handler4 = std::move(handler);

    EXPECT_EQ(test_matrix, handler4.getPolarization());
    EXPECT_EQ(test_matrix, handler4.getAnalyzerOperator());

    PolarizationHandler handler5;
    handler5 = std::move(handler2);

    EXPECT_EQ(test_matrix, handler5.getPolarization());
    EXPECT_EQ(test_matrix, handler5.getAnalyzerOperator());
}
