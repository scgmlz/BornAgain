#ifndef FIXEDBINAXISTEST_H
#define FIXEDBINAXISTEST_H

#include "FixedBinAxis.h"
#include "Exceptions.h"
#include "DataFormatUtils.h"
#include <iostream>

class FixedBinAxisTest: public ::testing::Test
{
protected:
    FixedBinAxisTest() {}
};

TEST_F(FixedBinAxisTest, IndexedAccessor)
{
    FixedBinAxis a1("length", 100, 0.0, 10.0);
    ASSERT_EQ(100u, a1.size());
    EXPECT_EQ(0.0, a1.getMin());
    EXPECT_EQ(10.0, a1.getMax());
    EXPECT_DOUBLE_EQ(0.05, a1[0]);
    EXPECT_DOUBLE_EQ(0.15, a1[1]);
    EXPECT_DOUBLE_EQ(6.55, a1[65]);
    EXPECT_DOUBLE_EQ(9.95, a1[99]);

    FixedBinAxis a2("name", 3, -1.5, 1.5);
    EXPECT_DOUBLE_EQ(-1.0, a2[0]);
    EXPECT_DOUBLE_EQ(0.0, a2[1]);
    EXPECT_DOUBLE_EQ(1.0, a2[2]);
    ASSERT_THROW( a2[3], Exceptions::OutOfBoundsException);
}

TEST_F(FixedBinAxisTest, VectorOfUnitLength)
{
    FixedBinAxis vec("name", 1, 1.0, 2.0);
    EXPECT_EQ(1u, vec.size());
    EXPECT_EQ(double(1.0), vec.getMin());
    EXPECT_EQ(double(2.0), vec.getMax());
    EXPECT_EQ(1.5, vec[0]);
}

TEST_F(FixedBinAxisTest, FindClosestIndex)
{
    FixedBinAxis v1("name", 2, 0.0, 1.0);
    EXPECT_EQ( size_t(2), v1.size());
    EXPECT_EQ( size_t(0), v1.findClosestIndex(0.0));
    EXPECT_EQ( size_t(0), v1.findClosestIndex(0.25));
    EXPECT_EQ( size_t(1), v1.findClosestIndex(0.5));
    EXPECT_EQ( size_t(1), v1.findClosestIndex(0.6));
//    ASSERT_THROW( v1.findClosestIndex(1.0), Exceptions::OutOfBoundsException);
    EXPECT_EQ( size_t(1), v1.findClosestIndex(1.0));

    FixedBinAxis v2("name", 3, -1.5, 1.5);
    EXPECT_EQ(size_t(0), v2.findClosestIndex(-1.5));
    EXPECT_EQ(size_t(0), v2.findClosestIndex(-1.0));
    EXPECT_EQ(size_t(1), v2.findClosestIndex(-0.5));
    EXPECT_EQ(size_t(1), v2.findClosestIndex(0.0));
    EXPECT_EQ(size_t(2), v2.findClosestIndex(0.5));
    EXPECT_EQ(size_t(2), v2.findClosestIndex(1.499));
//    ASSERT_THROW( v2.findClosestIndex(1.5), Exceptions::OutOfBoundsException);
    EXPECT_EQ(size_t(2), v2.findClosestIndex(1.5));
}

TEST_F(FixedBinAxisTest, CheckBin)
{
    FixedBinAxis axis("name",20, 0, 10);

    Bin1D bin0 = axis.getBin(0);
    EXPECT_DOUBLE_EQ( 0.25, bin0.getMidPoint());
    EXPECT_DOUBLE_EQ( 0.0, bin0.m_lower);
    EXPECT_DOUBLE_EQ( 0.5, bin0.m_upper);
    EXPECT_DOUBLE_EQ( 0.5, bin0.getBinSize());

    Bin1D bin3 = axis.getBin(3);
    EXPECT_DOUBLE_EQ( 1.75, bin3.getMidPoint());
    EXPECT_DOUBLE_EQ( 1.5, bin3.m_lower);
    EXPECT_DOUBLE_EQ( 2.0, bin3.m_upper);
    EXPECT_DOUBLE_EQ( 0.5, bin3.getBinSize());

    Bin1D bin10 = axis.getBin(10);
    EXPECT_DOUBLE_EQ( 5.25, bin10.getMidPoint());
    EXPECT_DOUBLE_EQ( 5.0, bin10.m_lower);
    EXPECT_DOUBLE_EQ( 5.5, bin10.m_upper);

    Bin1D bin19 = axis.getBin(19);
    EXPECT_DOUBLE_EQ( 9.75, bin19.getMidPoint());
    EXPECT_DOUBLE_EQ( 9.5, bin19.m_lower);
    EXPECT_DOUBLE_EQ( 10.0, bin19.m_upper);

    ASSERT_THROW( axis.getBin(20), Exceptions::OutOfBoundsException);

    FixedBinAxis axis2("name", 3, -1, 2.0);
    EXPECT_DOUBLE_EQ(-0.5, axis2.getBin(0).getMidPoint());
    EXPECT_DOUBLE_EQ(0.5, axis2.getBin(1).getMidPoint());
    EXPECT_DOUBLE_EQ(1.5, axis2.getBin(2).getMidPoint());
}

TEST_F(FixedBinAxisTest, CheckEquality)
{
    FixedBinAxis b1("axis", 99, -1.01, 3.3);
    FixedBinAxis b2("axis", 99, -1.01, 3.3);
    EXPECT_TRUE( b1 == b2);
    FixedBinAxis b3("axissss", 99, -1.01, 3.3);
    FixedBinAxis b4("axis", 99, -1.0, 3.3);
    FixedBinAxis b5("axis", 99, -1.01, 3.29);
    FixedBinAxis b6("axiss", 98, -1.01, 3.3);
    EXPECT_FALSE( b1 == b3);
    EXPECT_FALSE( b1 == b4);
    EXPECT_FALSE( b1 == b5);
    EXPECT_FALSE( b1 == b6);
}

TEST_F(FixedBinAxisTest, CheckClone)
{
    FixedBinAxis a1("axis", 99, -1.2, 5.4);
    FixedBinAxis *clone=a1.clone();
    EXPECT_TRUE(a1 == *clone);
    delete clone;
}

TEST_F(FixedBinAxisTest, IOStream)
{
    FixedBinAxis axis("name", 99, -1.2, 5.4);

    std::ostringstream oss;
    oss << axis;

    FixedBinAxis *result = dynamic_cast<FixedBinAxis *>(DataFormatUtils::createFixedBinAxis(oss.str()));
    EXPECT_TRUE(axis == *result);
    delete result;
}

TEST_F(FixedBinAxisTest, BinCenters)
{
    FixedBinAxis axis("name", 3, -1.5, 1.5);
    std::vector<double> centers = axis.getBinCenters();
    EXPECT_EQ(size_t(3), centers.size());
    EXPECT_DOUBLE_EQ(-1.0, centers[0]);
    EXPECT_DOUBLE_EQ(0.0, centers[1]);
    EXPECT_DOUBLE_EQ(1.0, centers[2]);

    EXPECT_DOUBLE_EQ(axis.getBinCenter(0), centers[0]);
    EXPECT_DOUBLE_EQ(axis.getBinCenter(1), centers[1]);
    EXPECT_DOUBLE_EQ(axis.getBinCenter(2), centers[2]);

}

TEST_F(FixedBinAxisTest, BinBoundaries)
{
    FixedBinAxis axis("name", 3, -1.5, 1.5);
    std::vector<double> boundaries = axis.getBinBoundaries();
    EXPECT_EQ(size_t(4), boundaries.size());
    EXPECT_DOUBLE_EQ(-1.5, boundaries[0]);
    EXPECT_DOUBLE_EQ(-0.5, boundaries[1]);
    EXPECT_DOUBLE_EQ(0.5, boundaries[2]);
    EXPECT_DOUBLE_EQ(1.5, boundaries[3]);
}


TEST_F(FixedBinAxisTest, ClippedAxis)
{
    FixedBinAxis axis("name", 4, -1.0, 3.0);

    FixedBinAxis *clip1 = axis.createClippedAxis(-0.5, 2.5);
    EXPECT_EQ(clip1->size(), axis.size());
    EXPECT_EQ(clip1->getMin(), axis.getMin());
    EXPECT_EQ(clip1->getMax(), axis.getMax());
    EXPECT_TRUE(*clip1 == axis);
    delete clip1;

    FixedBinAxis *clip2 = axis.createClippedAxis(0.0, 1.99);
    EXPECT_EQ(clip2->size(), size_t(2));
    EXPECT_EQ(clip2->getMin(), 0.0);
    EXPECT_EQ(clip2->getMax(), 2.0);
    EXPECT_TRUE(*clip2 != axis);
    delete clip2;
}


#endif // FIXEDBINAXISTEST_H
