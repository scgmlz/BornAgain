#ifndef CUMULATIVEVALUETEST_H
#define CUMULATIVEVALUETEST_H

#include "CumulativeValue.h"


class CumulativeValueTest : public ::testing::Test
{
 protected:
    CumulativeValueTest(){}
    virtual ~CumulativeValueTest(){}
};

TEST_F(CumulativeValueTest, InitialState)
{
    CumulativeValue cv;
    EXPECT_EQ(0, cv.getNumberOfEntries());
    EXPECT_EQ(0.0, cv.getContent());
    EXPECT_EQ(0.0, cv.getAverage());
    EXPECT_EQ(0.0, cv.getRMS());
}

TEST_F(CumulativeValueTest, AddValue)
{
    CumulativeValue cv1;
    cv1.add(1.0);
    EXPECT_EQ(1, cv1.getNumberOfEntries());
    EXPECT_EQ(1.0, cv1.getContent());
    EXPECT_EQ(1.0, cv1.getAverage());
    EXPECT_EQ(0.0, cv1.getRMS());

    // adding value with weight, all number should stay the same
    CumulativeValue cv2;
    cv2.add(1.0, 10.0);
    EXPECT_EQ(1, cv2.getNumberOfEntries());
    EXPECT_EQ(1.0, cv2.getContent());
    EXPECT_EQ(1.0, cv2.getAverage());
    EXPECT_EQ(0.0, cv2.getRMS());

}

TEST_F(CumulativeValueTest, AddValues)
{
    CumulativeValue cv1;
    cv1.add(1.0);
    cv1.add(3.0);
    EXPECT_EQ(2, cv1.getNumberOfEntries());
    EXPECT_DOUBLE_EQ(4.0, cv1.getContent());
    EXPECT_DOUBLE_EQ(2.0, cv1.getAverage());
    EXPECT_DOUBLE_EQ(1.0, cv1.getRMS());

    cv1.clear();
    EXPECT_EQ(0, cv1.getNumberOfEntries());
    EXPECT_EQ(0.0, cv1.getContent());
    EXPECT_EQ(0.0, cv1.getAverage());
    EXPECT_EQ(0.0, cv1.getRMS());
}

TEST_F(CumulativeValueTest, AddValuesWithWeights)
{
    CumulativeValue cv1;
    cv1.add(1.0, 3.0);
    cv1.add(3.0);
    EXPECT_EQ(2, cv1.getNumberOfEntries());
    EXPECT_DOUBLE_EQ(4.0, cv1.getContent());
    EXPECT_DOUBLE_EQ(1.5, cv1.getAverage());
    EXPECT_DOUBLE_EQ(0.75, cv1.getRMS()*cv1.getRMS());

    cv1.add(3.0);
    cv1.add(3.0);
    EXPECT_EQ(4, cv1.getNumberOfEntries());
    EXPECT_DOUBLE_EQ(10.0, cv1.getContent());
    EXPECT_DOUBLE_EQ(2.0, cv1.getAverage());
	EXPECT_DOUBLE_EQ(1.0, cv1.getRMS());
}

TEST_F(CumulativeValueTest, Comparison)
{
    CumulativeValue cv1, cv2;
    cv1.add(1.0);
    cv2.add(2.0);

    EXPECT_TRUE(cv2 > cv1);
    EXPECT_TRUE(cv1 < cv2);

}



#endif // CUMULATIVEVALUETEST_H
