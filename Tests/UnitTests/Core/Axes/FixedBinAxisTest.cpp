#include "Base/Axis/FixedBinAxis.h"
#include "Device/InputOutput/DataFormatUtils.h"
#include "Tests/GTestWrapper/google_test.h"
#include <iostream>

class FixedBinAxisTest : public ::testing::Test {};

TEST_F(FixedBinAxisTest, IndexedAccessor) {
    FixedBinAxis a1("length", 100, 0.0, 10.0);
    ASSERT_EQ(100u, a1.size());
    EXPECT_EQ(0.0, a1.lowerBound());
    EXPECT_EQ(10.0, a1.upperBound());
    EXPECT_DOUBLE_EQ(0.05, a1[0]);
    EXPECT_DOUBLE_EQ(0.15, a1[1]);
    EXPECT_DOUBLE_EQ(6.55, a1[65]);
    EXPECT_DOUBLE_EQ(9.95, a1[99]);

    FixedBinAxis a2("name", 3, -1.5, 1.5);
    EXPECT_DOUBLE_EQ(-1.0, a2[0]);
    EXPECT_DOUBLE_EQ(0.0, a2[1]);
    EXPECT_DOUBLE_EQ(1.0, a2[2]);
    ASSERT_THROW(a2[3], std::runtime_error);
}

TEST_F(FixedBinAxisTest, VectorOfUnitLength) {
    FixedBinAxis vec("name", 1, 1.0, 2.0);
    EXPECT_EQ(1u, vec.size());
    EXPECT_EQ(double(1.0), vec.lowerBound());
    EXPECT_EQ(double(2.0), vec.upperBound());
    EXPECT_EQ(1.5, vec[0]);
}

TEST_F(FixedBinAxisTest, FindClosestIndex) {
    FixedBinAxis v1("name", 2, 0.0, 1.0);
    EXPECT_EQ(size_t(2), v1.size());
    EXPECT_EQ(size_t(0), v1.findClosestIndex(0.0));
    EXPECT_EQ(size_t(0), v1.findClosestIndex(0.25));
    EXPECT_EQ(size_t(1), v1.findClosestIndex(0.5));
    EXPECT_EQ(size_t(1), v1.findClosestIndex(0.6));
    //    ASSERT_THROW( v1.findClosestIndex(1.0), std::runtime_error);
    EXPECT_EQ(size_t(1), v1.findClosestIndex(1.0));

    FixedBinAxis v2("name", 3, -1.5, 1.5);
    EXPECT_EQ(size_t(0), v2.findClosestIndex(-1.5));
    EXPECT_EQ(size_t(0), v2.findClosestIndex(-1.0));
    EXPECT_EQ(size_t(1), v2.findClosestIndex(-0.5));
    EXPECT_EQ(size_t(1), v2.findClosestIndex(0.0));
    EXPECT_EQ(size_t(2), v2.findClosestIndex(0.5));
    EXPECT_EQ(size_t(2), v2.findClosestIndex(1.499));
    //    ASSERT_THROW( v2.findClosestIndex(1.5), std::runtime_error);
    EXPECT_EQ(size_t(2), v2.findClosestIndex(1.5));
}

TEST_F(FixedBinAxisTest, CheckBin) {
    FixedBinAxis axis("name", 20, 0, 10);

    Bin1D bin0 = axis.bin(0);
    EXPECT_DOUBLE_EQ(0.25, bin0.center());
    EXPECT_DOUBLE_EQ(0.0, bin0.m_lower);
    EXPECT_DOUBLE_EQ(0.5, bin0.m_upper);
    EXPECT_DOUBLE_EQ(0.5, bin0.binSize());

    Bin1D bin3 = axis.bin(3);
    EXPECT_DOUBLE_EQ(1.75, bin3.center());
    EXPECT_DOUBLE_EQ(1.5, bin3.m_lower);
    EXPECT_DOUBLE_EQ(2.0, bin3.m_upper);
    EXPECT_DOUBLE_EQ(0.5, bin3.binSize());

    Bin1D bin10 = axis.bin(10);
    EXPECT_DOUBLE_EQ(5.25, bin10.center());
    EXPECT_DOUBLE_EQ(5.0, bin10.m_lower);
    EXPECT_DOUBLE_EQ(5.5, bin10.m_upper);

    Bin1D bin19 = axis.bin(19);
    EXPECT_DOUBLE_EQ(9.75, bin19.center());
    EXPECT_DOUBLE_EQ(9.5, bin19.m_lower);
    EXPECT_DOUBLE_EQ(10.0, bin19.m_upper);

    ASSERT_THROW(axis.bin(20), std::runtime_error);

    FixedBinAxis axis2("name", 3, -1, 2.0);
    EXPECT_DOUBLE_EQ(-0.5, axis2.bin(0).center());
    EXPECT_DOUBLE_EQ(0.5, axis2.bin(1).center());
    EXPECT_DOUBLE_EQ(1.5, axis2.bin(2).center());
}

TEST_F(FixedBinAxisTest, CheckEquality) {
    FixedBinAxis b1("axis", 99, -1.01, 3.3);
    FixedBinAxis b2("axis", 99, -1.01, 3.3);
    EXPECT_TRUE(b1 == b2);
    FixedBinAxis b3("axissss", 99, -1.01, 3.3);
    FixedBinAxis b4("axis", 99, -1.0, 3.3);
    FixedBinAxis b5("axis", 99, -1.01, 3.29);
    FixedBinAxis b6("axiss", 98, -1.01, 3.3);
    EXPECT_FALSE(b1 == b3);
    EXPECT_FALSE(b1 == b4);
    EXPECT_FALSE(b1 == b5);
    EXPECT_FALSE(b1 == b6);
}

TEST_F(FixedBinAxisTest, CheckClone) {
    FixedBinAxis a1("axis", 99, -1.2, 5.4);
    FixedBinAxis* clone = a1.clone();
    EXPECT_TRUE(a1 == *clone);
    delete clone;
}

TEST_F(FixedBinAxisTest, IOStream) {
    FixedBinAxis axis("name", 99, -1.2, 5.4);

    std::ostringstream oss;
    oss << axis;
    std::istringstream iss(oss.str());

    std::unique_ptr<IAxis> result(DataFormatUtils::createAxis(iss));
    EXPECT_TRUE(axis == *result);
}

TEST_F(FixedBinAxisTest, BinCenters) {
    FixedBinAxis axis("name", 3, -1.5, 1.5);
    std::vector<double> centers = axis.binCenters();
    EXPECT_EQ(size_t(3), centers.size());
    EXPECT_DOUBLE_EQ(-1.0, centers[0]);
    EXPECT_DOUBLE_EQ(0.0, centers[1]);
    EXPECT_DOUBLE_EQ(1.0, centers[2]);

    EXPECT_DOUBLE_EQ(axis.binCenter(0), centers[0]);
    EXPECT_DOUBLE_EQ(axis.binCenter(1), centers[1]);
    EXPECT_DOUBLE_EQ(axis.binCenter(2), centers[2]);
}

TEST_F(FixedBinAxisTest, BinBoundaries) {
    FixedBinAxis axis("name", 3, -1.5, 1.5);
    std::vector<double> boundaries = axis.binBoundaries();
    EXPECT_EQ(size_t(4), boundaries.size());
    EXPECT_DOUBLE_EQ(-1.5, boundaries[0]);
    EXPECT_DOUBLE_EQ(-0.5, boundaries[1]);
    EXPECT_DOUBLE_EQ(0.5, boundaries[2]);
    EXPECT_DOUBLE_EQ(1.5, boundaries[3]);
}

TEST_F(FixedBinAxisTest, ClippedAxis) {
    FixedBinAxis axis("name", 4, -1.0, 3.0);

    FixedBinAxis* clip1 = axis.createClippedAxis(-0.5, 2.5);
    EXPECT_EQ(clip1->size(), axis.size());
    EXPECT_EQ(clip1->lowerBound(), axis.lowerBound());
    EXPECT_EQ(clip1->upperBound(), axis.upperBound());
    EXPECT_TRUE(*clip1 == axis);
    delete clip1;

    FixedBinAxis* clip2 = axis.createClippedAxis(0.0, 1.99);
    EXPECT_EQ(clip2->size(), size_t(2));
    EXPECT_EQ(clip2->lowerBound(), 0.0);
    EXPECT_EQ(clip2->upperBound(), 2.0);
    EXPECT_TRUE(*clip2 != axis);
    delete clip2;
}
