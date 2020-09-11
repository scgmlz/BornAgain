#include "Core/Intensity/ArrayUtils.h"
#include "Core/Binning/IAxis.h"
#include "Tests/GTestWrapper/google_test.h"
#include <vector>

class ArrayUtilsTest : public ::testing::Test
{
};

TEST_F(ArrayUtilsTest, OutputDataFromVector1D)
{
    // double
    const std::vector<double> vec_double = {10.0, 20.0, 30.0, 40.0};
    auto data1 = ArrayUtils::createData(vec_double);

    EXPECT_EQ(data1->getAllocatedSize(), vec_double.size());
    EXPECT_EQ(data1->getRawDataVector(), vec_double);
    EXPECT_EQ(data1->getAxis(0).getMin(), 0.0);
    EXPECT_EQ(data1->getAxis(0).getMax(), 4.0);

    // int
    const std::vector<int> vec_int = {10, 20, 30};
    auto data2 = ArrayUtils::createData(vec_int);

    EXPECT_EQ(data2->getAllocatedSize(), vec_int.size());
    EXPECT_EQ(data2->getRawDataVector(), vec_int);
    EXPECT_EQ(data2->getAxis(0).getMin(), 0.0);
    EXPECT_EQ(data2->getAxis(0).getMax(), 3.0);
}

TEST_F(ArrayUtilsTest, OutputDataToVector1D)
{
    const std::vector<double> expected = {10.0, 20.0, 30.0, 40.0};
    OutputData<double> data;
    data.addAxis("axis0", 4, 10.0, 20.0);
    data.setRawDataVector(expected);

    auto vec = ArrayUtils::createVector1D(data);

    EXPECT_EQ(vec.size(), data.getAllocatedSize());
    EXPECT_EQ(vec, expected);
}

TEST_F(ArrayUtilsTest, OutputDataFromVector2D)
{
    const std::vector<std::vector<double>> vec_double = {
        {0.0, 1.0, 2.0, 3.0}, {4.0, 5.0, 6.0, 7.0}, {8.0, 9.0, 10.0, 11.0}};
    auto data = ArrayUtils::createData(vec_double);

    EXPECT_EQ(data->getRank(), 2u);
    EXPECT_EQ(data->getAllocatedSize(), 12u);
    EXPECT_EQ(data->getAxis(0).size(), 4u);
    EXPECT_EQ(data->getAxis(0).getMin(), 0.0);
    EXPECT_EQ(data->getAxis(0).getMax(), 4.0);
    EXPECT_EQ(data->getAxis(1).size(), 3u);
    EXPECT_EQ(data->getAxis(1).getMin(), 0.0);
    EXPECT_EQ(data->getAxis(1).getMax(), 3.0);

    const std::vector<double> expected = {8.0,  4.0, 0.0, 9.0,  5.0, 1.0,
                                          10.0, 6.0, 2.0, 11.0, 7.0, 3.0};

    EXPECT_EQ(data->getRawDataVector(), expected);
}

TEST_F(ArrayUtilsTest, OutputDataToVector2D)
{
    OutputData<double> data;
    data.addAxis("axis0", 4, 10.0, 20.0);
    data.addAxis("axis1", 3, 30.0, 40.0);
    const std::vector<double> values = {8.0,  4.0, 0.0, 9.0,  5.0, 1.0,
                                        10.0, 6.0, 2.0, 11.0, 7.0, 3.0};

    data.setRawDataVector(values);

    auto vec = ArrayUtils::createVector2D(data);
    const std::vector<std::vector<double>> expected = {
        {0.0, 1.0, 2.0, 3.0}, {4.0, 5.0, 6.0, 7.0}, {8.0, 9.0, 10.0, 11.0}};
    EXPECT_EQ(vec, expected);
}
