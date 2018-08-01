#include "google_test.h"
#include "ArrayUtils.h"
#include "IAxis.h"
#include <vector>


class ArrayUtilsTest : public ::testing::Test
{
protected:
    ~ArrayUtilsTest();
};

ArrayUtilsTest::~ArrayUtilsTest() = default;


TEST_F(ArrayUtilsTest, OutputDataFromVector1D)
{
    // double
    const std::vector<double> vec_double = {10.0, 20.0, 30.0, 40.0};
    auto data1 = std::unique_ptr<OutputData<double>>(ArrayUtils::createData1D(vec_double));

    EXPECT_EQ(data1->getAllocatedSize(), vec_double.size());
    EXPECT_EQ(data1->getRawDataVector(), vec_double);
    EXPECT_EQ(data1->getAxis(0).getMin(), 0.0);
    EXPECT_EQ(data1->getAxis(0).getMax(), 4.0);
}

TEST_F(ArrayUtilsTest, OutputDataFromVector2D)
{
    const std::vector<std::vector<double>> vec_double = {
        {0.0, 1.0, 2.0,  3.0},
        {4.0, 5.0, 6.0,  7.0},
        {8.0, 9.0, 10.0, 11.0}
    };
    auto data = std::unique_ptr<OutputData<double>>(ArrayUtils::createData2D(vec_double));

    EXPECT_EQ(data->getRank(), 2u);
    EXPECT_EQ(data->getAllocatedSize(), 12u);
    EXPECT_EQ(data->getAxis(0).size(), 4u);
    EXPECT_EQ(data->getAxis(0).getMin(), 0.0);
    EXPECT_EQ(data->getAxis(0).getMax(), 4.0);
    EXPECT_EQ(data->getAxis(1).size(), 3u);
    EXPECT_EQ(data->getAxis(1).getMin(), 0.0);
    EXPECT_EQ(data->getAxis(1).getMax(), 3.0);

    const std::vector<double> expected =
        {8.0, 4.0, 0.0, 9.0, 5.0, 1.0, 10.0, 6.0, 2.0, 11.0, 7.0, 3.0};

    EXPECT_EQ(data->getRawDataVector(), expected);
}
