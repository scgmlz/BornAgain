#include "Core/Binning/PointwiseAxis.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/InputOutput/DataFormatUtils.h"
#include "Tests/GTestWrapper/google_test.h"
#include <iostream>

class PointwiseAxisTest : public ::testing::Test
{
};

TEST_F(PointwiseAxisTest, Construction)
{
    EXPECT_THROW(PointwiseAxis("length", std::vector<double>{0.0}), std::runtime_error);
    EXPECT_THROW(PointwiseAxis("length", std::vector<double>{1.0, 0.0}), std::runtime_error);
    EXPECT_THROW(PointwiseAxis("length", std::vector<double>{0.0, 1.0, 0.5}), std::runtime_error);
    EXPECT_THROW(PointwiseAxis("length", std::vector<double>{0.0, 1.0, 1.0}), std::runtime_error);
    PointwiseAxis a1("length", std::vector<double>{0.0, 1.0});
    std::vector<double> coordinates{0.0, 1.0};
    PointwiseAxis a2("length", coordinates);
    EXPECT_TRUE(a1 == a2);
}

TEST_F(PointwiseAxisTest, BasicProperties)
{
    std::vector<double> coordinates{0.0, 1.0, 4.0, 8.0};
    PointwiseAxis a1("length", coordinates);
    EXPECT_EQ(4u, a1.size());
    EXPECT_EQ(0.0, a1.getMin());
    EXPECT_EQ(8.0, a1.getMax());
    EXPECT_EQ(0.0, a1[0]);
    EXPECT_EQ(1.0, a1[1]);
    EXPECT_EQ(4.0, a1[2]);
    EXPECT_EQ(8.0, a1[3]);
    EXPECT_EQ(a1[0], a1.getBinCenter(0));
    EXPECT_EQ(a1[1], a1.getBinCenter(1));
    EXPECT_EQ(a1[2], a1.getBinCenter(2));
    EXPECT_EQ(a1[3], a1.getBinCenter(3));
    EXPECT_THROW(a1[4], std::runtime_error);
    EXPECT_THROW(a1.getBinCenter(4), std::runtime_error);
    EXPECT_TRUE(coordinates == a1.getBinCenters());
}

TEST_F(PointwiseAxisTest, FindClosestIndex)
{
    PointwiseAxis v1("name", std::vector<double>{0.0, 1.0, 4.0, 8.0});
    EXPECT_EQ(4u, v1.size());
    EXPECT_EQ(v1.findClosestIndex(-1.0), 0u);
    EXPECT_EQ(v1.findClosestIndex(0.0), 0u);
    EXPECT_EQ(v1.findClosestIndex(0.25), 0u);
    EXPECT_EQ(1u, v1.findClosestIndex(0.5));
    EXPECT_EQ(1u, v1.findClosestIndex(0.6));
    EXPECT_EQ(1u, v1.findClosestIndex(2.49));
    EXPECT_EQ(2u, v1.findClosestIndex(2.5));
    EXPECT_EQ(3u, v1.findClosestIndex(8.0));
    EXPECT_EQ(3u, v1.findClosestIndex(11.0));

    PointwiseAxis v2("name", std::vector<double>{-2.0, -1.0});
    EXPECT_EQ(2u, v2.size());
    EXPECT_EQ(v2.findClosestIndex(-3.0), 0u);
    EXPECT_EQ(v2.findClosestIndex(-2.0), 0u);
    EXPECT_EQ(1u, v2.findClosestIndex(-1.5));
    EXPECT_EQ(1u, v2.findClosestIndex(-1.0));
    EXPECT_EQ(1u, v2.findClosestIndex(0.0));
    EXPECT_EQ(1u, v2.findClosestIndex(1.0));
}

TEST_F(PointwiseAxisTest, CheckBin)
{
    PointwiseAxis axis("name", std::vector<double>{0, 2, 10});
    auto boundaries = axis.getBinBoundaries();
    EXPECT_EQ(4u, boundaries.size());

    Bin1D bin0 = axis.getBin(0);
    EXPECT_DOUBLE_EQ(0.5, bin0.getMidPoint());
    EXPECT_DOUBLE_EQ(0.0, bin0.m_lower);
    EXPECT_DOUBLE_EQ(bin0.m_lower, boundaries[0]);
    EXPECT_DOUBLE_EQ(1.0, bin0.m_upper);
    EXPECT_DOUBLE_EQ(bin0.m_upper, boundaries[1]);
    EXPECT_DOUBLE_EQ(1.0, bin0.getBinSize());

    Bin1D bin1 = axis.getBin(1);
    EXPECT_DOUBLE_EQ(3.5, bin1.getMidPoint());
    EXPECT_DOUBLE_EQ(1.0, bin1.m_lower);
    EXPECT_DOUBLE_EQ(bin1.m_lower, boundaries[1]);
    EXPECT_DOUBLE_EQ(6.0, bin1.m_upper);
    EXPECT_DOUBLE_EQ(bin1.m_upper, boundaries[2]);
    EXPECT_DOUBLE_EQ(5.0, bin1.getBinSize());

    Bin1D bin2 = axis.getBin(2);
    EXPECT_DOUBLE_EQ(8.0, bin2.getMidPoint());
    EXPECT_DOUBLE_EQ(6.0, bin2.m_lower);
    EXPECT_DOUBLE_EQ(bin2.m_lower, boundaries[2]);
    EXPECT_DOUBLE_EQ(10.0, bin2.m_upper);
    EXPECT_DOUBLE_EQ(bin2.m_upper, boundaries[3]);
    EXPECT_DOUBLE_EQ(4.0, bin2.getBinSize());

    EXPECT_THROW(axis.getBin(3), std::runtime_error);
}

TEST_F(PointwiseAxisTest, CheckEquality)
{
    PointwiseAxis b1("axis", std::vector<double>{1.0, 2.0, 5.0});
    PointwiseAxis b2("axis", std::vector<double>{1.0, 2.0, 5.0});
    EXPECT_TRUE(b1 == b2);
    PointwiseAxis b3("axissss", std::vector<double>{1.0, 2.0, 5.0});
    PointwiseAxis b4("axis", std::vector<double>{1.0, 2.0, 6.0});
    PointwiseAxis b6("axiss", std::vector<double>{1.5, 2.0, 5.0});
    EXPECT_FALSE(b1 == b3);
    EXPECT_FALSE(b1 == b4);
    EXPECT_FALSE(b1 == b6);
}

TEST_F(PointwiseAxisTest, CheckClone)
{
    PointwiseAxis a1("axis", std::vector<double>{1.0, 2.0, 5.0});
    std::unique_ptr<PointwiseAxis> clone(a1.clone());
    EXPECT_TRUE(a1 == *clone);
}

TEST_F(PointwiseAxisTest, IOStream)
{
    PointwiseAxis axis("name", std::vector<double>{1.0, 2.0, 5.0});

    std::ostringstream oss;
    oss << axis;
    std::istringstream iss(oss.str());

    std::unique_ptr<IAxis> result(DataFormatUtils::createAxis(iss));
    EXPECT_TRUE(axis == *result);
}

TEST_F(PointwiseAxisTest, ClippedAxis)
{
    PointwiseAxis axis("name", std::vector<double>{1.0, 2.0, 2.5, 2.7, 5.0});

    std::unique_ptr<PointwiseAxis> clip1(axis.createClippedAxis(0.99, 5.1));
    EXPECT_TRUE(*clip1 == axis);

    std::unique_ptr<PointwiseAxis> clip2(axis.createClippedAxis(1, 5.0));
    EXPECT_TRUE(*clip2 == axis);

    std::unique_ptr<PointwiseAxis> clip3(axis.createClippedAxis(1.5, 2.5));
    EXPECT_TRUE(*clip3 != axis);
    EXPECT_EQ(clip3->size(), 2u);
    EXPECT_EQ(clip3->operator[](0), 2.0);
    EXPECT_EQ(clip3->operator[](1), 2.5);

    EXPECT_THROW(axis.createClippedAxis(1.5, 2.0), std::runtime_error);
    EXPECT_THROW(axis.createClippedAxis(5.0, 1.0), std::runtime_error);
}

TEST_F(PointwiseAxisTest, FixedBinAxisComparison)
{
    FixedBinAxis fixed_axis("name", 4, 0.0, 4.0);
    PointwiseAxis pointwise_axis("name", std::vector<double>{0.5, 1.5, 2.5, 3.5});

    EXPECT_EQ(fixed_axis.size(), pointwise_axis.size());
    EXPECT_DOUBLE_EQ(fixed_axis[0], pointwise_axis[0]);
    EXPECT_DOUBLE_EQ(fixed_axis[1], pointwise_axis[1]);
    EXPECT_DOUBLE_EQ(fixed_axis[2], pointwise_axis[2]);
    EXPECT_DOUBLE_EQ(fixed_axis[3], pointwise_axis[3]);

    Bin1D bin1 = fixed_axis.getBin(1);
    Bin1D bin1_ = pointwise_axis.getBin(1);
    EXPECT_DOUBLE_EQ(bin1.m_lower, bin1_.m_lower);
    EXPECT_DOUBLE_EQ(bin1.m_upper, bin1_.m_upper);

    EXPECT_EQ(fixed_axis.findClosestIndex(0.0), pointwise_axis.findClosestIndex(0.0));
    EXPECT_EQ(fixed_axis.findClosestIndex(0.99), pointwise_axis.findClosestIndex(0.99));
    EXPECT_EQ(fixed_axis.findClosestIndex(1.0), pointwise_axis.findClosestIndex(1.0));
    EXPECT_EQ(fixed_axis.findClosestIndex(2.5), pointwise_axis.findClosestIndex(2.5));
    EXPECT_EQ(fixed_axis.findClosestIndex(4.5), pointwise_axis.findClosestIndex(4.5));

    std::unique_ptr<FixedBinAxis> clipped_fixed(fixed_axis.createClippedAxis(0.5, 3.5));
    std::unique_ptr<PointwiseAxis> clipped_pointwise(pointwise_axis.createClippedAxis(0.5, 3.5));
    EXPECT_EQ(clipped_fixed->size(), clipped_pointwise->size());
    EXPECT_DOUBLE_EQ(clipped_fixed->getBinCenter(0), clipped_pointwise->getBinCenter(0));
    EXPECT_DOUBLE_EQ(clipped_fixed->getBinCenter(3), clipped_pointwise->getBinCenter(3));

    clipped_fixed.reset(fixed_axis.createClippedAxis(1.0, 3.0));
    clipped_pointwise.reset(pointwise_axis.createClippedAxis(1.0, 3.0));
    EXPECT_EQ(clipped_fixed->size(), clipped_pointwise->size());
    EXPECT_DOUBLE_EQ(clipped_fixed->getBinCenter(0), clipped_pointwise->getBinCenter(0));
    EXPECT_DOUBLE_EQ(clipped_fixed->getBinCenter(2), clipped_pointwise->getBinCenter(2));
}

TEST_F(PointwiseAxisTest, FixedBinAxisComparisonWithMask)
{
    FixedBinAxis axis("reference", 10, 0.0, 10.0);

    const std::vector<size_t> mask{0u, 2u, 3u, 4u, 7u, 8u, 9u};
    std::vector<double> coordinates;
    for (auto index : mask)
        coordinates.push_back(axis.getBinCenter(index));
    PointwiseAxis pointwise_axis("pointwise", coordinates);

    // comparing on-axis values
    for (size_t i = 0; i < mask.size(); ++i)
        EXPECT_DOUBLE_EQ(axis.getBinCenter(mask[i]), pointwise_axis.getBinCenter(i));
}
