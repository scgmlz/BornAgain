#ifndef TRANGETEST_H
#define TRANGETEST_H

#include "TRange.h"
#include <algorithm>

class TRangeTest : public ::testing::Test
{
 protected:
    TRangeTest();
    virtual ~TRangeTest();

    const TRange<int> *intRange;
    const TRange<float> *floatRange;
    const TRange<double> *doubleRange;
    const TSampledRange<int> *intSampledRange;
    const TSampledRange<float> *floatSampledRange;
    const TSampledRange<double> *doubleSampledRange;
};

TRangeTest::TRangeTest()
{
    intRange = new TRange<int>(1,100);
    floatRange = new TRange<float>(101.0f, 200.0f);
    doubleRange = new TRange<double>(201.0,300.0);

    intSampledRange = new TSampledRange<int>(4000u, 1, 100);
    floatSampledRange = new TSampledRange<float>(5000u, 101.0f, 200.0f);
    doubleSampledRange = new TSampledRange<double>(6000u, 201.0,300.0);
}

TRangeTest::~TRangeTest()
{
    delete intRange;
    delete floatRange;
    delete doubleRange;
    delete intSampledRange;
    delete floatSampledRange;
    delete doubleSampledRange;
}

TEST_F(TRangeTest, TRangeTestLowerBound)
{
    EXPECT_EQ(1, intRange->getLowerBound());
    EXPECT_EQ(101.0f, floatRange->getLowerBound());
    EXPECT_EQ(201.0, doubleRange->getLowerBound());
}

TEST_F(TRangeTest, TRangeTestUpperBound)
{
    EXPECT_EQ(100, intRange->getUpperBound());
    EXPECT_EQ(200.0f, floatRange->getUpperBound());
    EXPECT_EQ(300.0, doubleRange->getUpperBound());

}

TEST_F(TRangeTest, TRangeTestDifference)
{
    EXPECT_EQ(99, intRange->getDifference());
    EXPECT_EQ(99.0f, floatRange->getDifference());
    EXPECT_EQ(99.0, doubleRange->getDifference());
}

TEST_F(TRangeTest, TRangeTestInRange)
{
    EXPECT_TRUE(intRange->inRange(1));
    EXPECT_TRUE(floatRange->inRange(101.0f));
    EXPECT_TRUE(doubleRange->inRange(201.0));

    EXPECT_TRUE(intRange->inRange(50));
    EXPECT_TRUE(floatRange->inRange(150.0f));
    EXPECT_TRUE(doubleRange->inRange(250.0));

    EXPECT_FALSE(intRange->inRange(100));
    EXPECT_FALSE(floatRange->inRange(200.0f));
    EXPECT_FALSE(doubleRange->inRange(300.0));

    EXPECT_FALSE(intRange->inRange(0));
    EXPECT_FALSE(floatRange->inRange(100.0f));
    EXPECT_FALSE(doubleRange->inRange(200.0));

    EXPECT_FALSE(intRange->inRange(101));
    EXPECT_FALSE(floatRange->inRange(201.0f));
    EXPECT_FALSE(doubleRange->inRange(301.0));

}

TEST_F(TRangeTest, TSampledRangeNSamples)
{
    EXPECT_EQ(4000u, intSampledRange->getNSamples());
    EXPECT_EQ(5000u, floatSampledRange->getNSamples());
    EXPECT_EQ(6000u, doubleSampledRange->getNSamples());
}

#endif // TRANGETEST_H
