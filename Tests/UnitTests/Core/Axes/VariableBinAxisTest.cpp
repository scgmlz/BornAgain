#include "Base/Axis/VariableBinAxis.h"
#include "Device/InputOutput/DataFormatUtils.h"
#include "Tests/GTestWrapper/google_test.h"

class VariableBinAxisTest : public ::testing::Test {};

TEST_F(VariableBinAxisTest, VectorOfUnitLength) {
    static const double arr[] = {0., 1.};
    std::vector<double> values(arr, arr + sizeof(arr) / sizeof(arr[0]));
    VariableBinAxis axis("name", 1, values);
    EXPECT_EQ(size_t(1), axis.size());
    EXPECT_EQ(0.0, axis.lowerBound());
    EXPECT_EQ(1.0, axis.upperBound());
    EXPECT_EQ(0.5, axis[0]);
}

TEST_F(VariableBinAxisTest, ValidityOfCOnstructor) {
    std::vector<double> values;
    ASSERT_THROW(VariableBinAxis("name", 1, values), std::runtime_error);
    values.resize(5);
    ASSERT_THROW(VariableBinAxis("name", 5, values), std::runtime_error);

    static const double arr1[] = {-1.5, -1.5, 0.5, 1.5};
    std::vector<double> v1(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));
    ASSERT_THROW(VariableBinAxis("name", 3, v1), std::runtime_error);

    static const double arr2[] = {1.5, -0.5, 0.5, -1.5};
    std::vector<double> v2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
    ASSERT_THROW(VariableBinAxis("name", 3, v2), std::runtime_error);
}

TEST_F(VariableBinAxisTest, IndexedAccessor) {
    std::vector<double> values;

    double start(0.0);
    double end(10.0);
    size_t nbins(100);
    double step = (end - start) / (nbins);
    for (size_t i = 0; i < nbins + 1; ++i) {
        values.push_back(start + step * (int)i);
    }

    VariableBinAxis a1("name", nbins, values);

    ASSERT_EQ(100u, a1.size());
    EXPECT_EQ(0.0, a1.lowerBound());
    EXPECT_EQ(10.0, a1.upperBound());
    EXPECT_DOUBLE_EQ(0.05, a1[0]);
    EXPECT_DOUBLE_EQ(0.15, a1[1]);
    EXPECT_DOUBLE_EQ(6.55, a1[65]);
    EXPECT_DOUBLE_EQ(9.95, a1[99]);

    static const double arr[] = {-1.5, -0.5, 0.5, 1.5};
    std::vector<double> v2(arr, arr + sizeof(arr) / sizeof(arr[0]));
    VariableBinAxis a2("name", 3, v2);
    EXPECT_DOUBLE_EQ(-1.0, a2[0]);
    EXPECT_DOUBLE_EQ(0.0, a2[1]);
    EXPECT_DOUBLE_EQ(1.0, a2[2]);
    ASSERT_THROW(a2[3], std::runtime_error);
}

TEST_F(VariableBinAxisTest, FindClosestIndex) {
    static const double arr1[] = {0.0, 0.5, 1.0};
    std::vector<double> values1(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]));

    VariableBinAxis v1("name", 2, values1);
    EXPECT_EQ(size_t(2), v1.size());
    EXPECT_EQ(size_t(0), v1.findClosestIndex(0.0));
    EXPECT_EQ(size_t(0), v1.findClosestIndex(0.25));
    EXPECT_EQ(size_t(1), v1.findClosestIndex(0.5));
    EXPECT_EQ(size_t(1), v1.findClosestIndex(0.6));
    //    ASSERT_THROW( v1.findClosestIndex(1.0), std::runtime_error);
    EXPECT_EQ(size_t(1), v1.findClosestIndex(1.0));

    static const double arr2[] = {-1.5, -0.5, 0.5, 1.5};
    std::vector<double> values2(arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]));
    VariableBinAxis v2("name", 3, values2);
    EXPECT_EQ(size_t(0), v2.findClosestIndex(-1.5));
    EXPECT_EQ(size_t(0), v2.findClosestIndex(-1.0));
    EXPECT_EQ(size_t(1), v2.findClosestIndex(-0.5));
    EXPECT_EQ(size_t(1), v2.findClosestIndex(0.0));
    EXPECT_EQ(size_t(2), v2.findClosestIndex(0.5));
    EXPECT_EQ(size_t(2), v2.findClosestIndex(1.499));
    //    ASSERT_THROW( v2.findClosestIndex(1.5), std::runtime_error);
    EXPECT_EQ(size_t(2), v2.findClosestIndex(1.5));

    static const double arr3[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values3(arr3, arr3 + sizeof(arr3) / sizeof(arr2[0]));
    VariableBinAxis v3("name", 4, values3);
    EXPECT_EQ(size_t(0), v3.findClosestIndex(-1.0));
    EXPECT_EQ(size_t(0), v3.findClosestIndex(-0.75));
    EXPECT_EQ(size_t(0), v3.findClosestIndex(-0.51));
    EXPECT_EQ(size_t(1), v3.findClosestIndex(-0.5));
    EXPECT_EQ(size_t(1), v3.findClosestIndex(0.1));
    EXPECT_EQ(size_t(1), v3.findClosestIndex(0.4999));
    EXPECT_EQ(size_t(2), v3.findClosestIndex(0.5));
    EXPECT_EQ(size_t(2), v3.findClosestIndex(0.99999));
    EXPECT_EQ(size_t(3), v3.findClosestIndex(1.0));
    EXPECT_EQ(size_t(3), v3.findClosestIndex(1.9999));
}

TEST_F(VariableBinAxisTest, CheckBin) {
    static const double arr3[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values3(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));
    VariableBinAxis axis("name", 4, values3);
    EXPECT_DOUBLE_EQ(-1.0, axis.bin(0).m_lower);
    EXPECT_DOUBLE_EQ(-0.75, axis.bin(0).center());
    EXPECT_DOUBLE_EQ(-0.5, axis.bin(0).m_upper);
    EXPECT_DOUBLE_EQ(0.5, axis.bin(0).binSize());

    EXPECT_DOUBLE_EQ(-0.5, axis.bin(1).m_lower);
    EXPECT_DOUBLE_EQ(0.0, axis.bin(1).center());
    EXPECT_DOUBLE_EQ(0.5, axis.bin(1).m_upper);
    EXPECT_DOUBLE_EQ(1.0, axis.bin(1).binSize());

    EXPECT_DOUBLE_EQ(0.5, axis.bin(2).m_lower);
    EXPECT_DOUBLE_EQ(0.75, axis.bin(2).center());
    EXPECT_DOUBLE_EQ(1.0, axis.bin(2).m_upper);
    EXPECT_DOUBLE_EQ(0.5, axis.bin(2).binSize());

    EXPECT_DOUBLE_EQ(1.0, axis.bin(3).m_lower);
    EXPECT_DOUBLE_EQ(1.5, axis.bin(3).center());
    EXPECT_DOUBLE_EQ(2.0, axis.bin(3).m_upper);
    EXPECT_DOUBLE_EQ(1.0, axis.bin(3).binSize());
}

TEST_F(VariableBinAxisTest, CheckEquality) {
    static const double arr3[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values3(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));

    VariableBinAxis a1("name", 4, values3);
    VariableBinAxis a2("name", 4, values3);
    VariableBinAxis a3("nameX", 4, values3);
    EXPECT_TRUE(a1 == a2);
    EXPECT_FALSE(a1 == a3);

    static const double arr4[] = {-1.0, -0.5, 0.5, 1.1, 2.0};
    std::vector<double> values4(arr4, arr4 + sizeof(arr4) / sizeof(arr4[0]));
    VariableBinAxis a4("nameX", 4, values4);
    EXPECT_FALSE(a1 == a4);
}

TEST_F(VariableBinAxisTest, CheckClone) {
    static const double arr3[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values3(arr3, arr3 + sizeof(arr3) / sizeof(arr3[0]));
    VariableBinAxis a1("name", 4, values3);

    VariableBinAxis* clone = a1.clone();
    EXPECT_TRUE(a1 == *clone);
    delete clone;
}

TEST_F(VariableBinAxisTest, IOStream) {
    static const double arr[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values(arr, arr + sizeof(arr) / sizeof(arr[0]));
    VariableBinAxis axis("name", 4, values);

    std::ostringstream oss;
    oss << axis;
    std::istringstream iss(oss.str());

    std::unique_ptr<IAxis> result(DataFormatUtils::createAxis(iss));
    EXPECT_TRUE(axis == *result);
}

TEST_F(VariableBinAxisTest, BinCenters) {
    static const double arr[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values(arr, arr + sizeof(arr) / sizeof(arr[0]));
    VariableBinAxis axis("name", 4, values);

    std::vector<double> centers = axis.binCenters();
    EXPECT_EQ(size_t(4), centers.size());
    EXPECT_DOUBLE_EQ(-0.75, centers[0]);
    EXPECT_DOUBLE_EQ(0.0, centers[1]);
    EXPECT_DOUBLE_EQ(0.75, centers[2]);
    EXPECT_DOUBLE_EQ(1.5, centers[3]);
}

TEST_F(VariableBinAxisTest, BinBoundaries) {
    static const double arr[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values(arr, arr + sizeof(arr) / sizeof(arr[0]));
    VariableBinAxis axis("name", 4, values);

    std::vector<double> boundaries = axis.binBoundaries();
    EXPECT_EQ(size_t(5), boundaries.size());
    EXPECT_DOUBLE_EQ(-1.0, boundaries[0]);
    EXPECT_DOUBLE_EQ(-0.5, boundaries[1]);
    EXPECT_DOUBLE_EQ(0.5, boundaries[2]);
    EXPECT_DOUBLE_EQ(1.0, boundaries[3]);
    EXPECT_DOUBLE_EQ(2.0, boundaries[4]);
}

TEST_F(VariableBinAxisTest, ClippedAxis) {
    static const double arr[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values(arr, arr + sizeof(arr) / sizeof(arr[0]));
    VariableBinAxis axis("name", 4, values);

    VariableBinAxis* clip1 = axis.createClippedAxis(-1.0, 2.0);
    EXPECT_TRUE(axis == *clip1);
    delete clip1;

    VariableBinAxis* clip2 = axis.createClippedAxis(-0.5, 1.5);
    EXPECT_EQ(clip2->size(), size_t(3));
    EXPECT_EQ(clip2->lowerBound(), -0.5);
    EXPECT_EQ(clip2->upperBound(), 2.0);
    std::vector<double> centers = clip2->binCenters();
    EXPECT_EQ(centers[0], 0.0);
    EXPECT_EQ(centers[1], 0.75);
    EXPECT_EQ(centers[2], 1.5);
    EXPECT_TRUE(axis != *clip2);
    delete clip2;

    VariableBinAxis* clip3 = axis.createClippedAxis(-0.5, 0.99);
    EXPECT_EQ(clip3->size(), size_t(2));
    EXPECT_EQ(clip3->lowerBound(), -0.5);
    EXPECT_EQ(clip3->upperBound(), 1.0);
    std::vector<double> boundaries = clip3->binBoundaries();
    EXPECT_EQ(boundaries[0], -0.5);
    EXPECT_EQ(boundaries[1], 0.5);
    EXPECT_EQ(boundaries[2], 1.0);
    delete clip3;
}
