#include "Core/Intensity/OutputDataIterator.h"
#include "Core/Intensity/OutputData.h"
#include "Tests/GTestWrapper/google_test.h"

class OutputDataIteratorTest : public ::testing::Test
{
protected:
    OutputDataIteratorTest();

    OutputData<double> _data;
};

OutputDataIteratorTest::OutputDataIteratorTest()
{
    int* dims = new int[2];
    dims[0] = 3;
    dims[1] = 5;
    _data.setAxisSizes(2, dims);
    double value = 0.0;
    OutputData<double>::iterator it = _data.begin();
    while (it != _data.end()) {
        *it = value;
        value += 1.0;
        ++it;
    }
}

TEST_F(OutputDataIteratorTest, Iterate)
{
    OutputData<double>::iterator it = _data.begin();
    EXPECT_EQ(0.0, *it);
    for (size_t i = 0; i < 14; ++i) {
        ++it;
    }
    EXPECT_DOUBLE_EQ(14.0, *it);
    ++it;
    EXPECT_EQ(it, _data.end());
    ++it;
    EXPECT_EQ(it, _data.end());
}

TEST_F(OutputDataIteratorTest, ConstIterate)
{
    OutputData<double>::const_iterator it = _data.begin();
    EXPECT_EQ(0.0, *it);
    for (size_t i = 0; i < 14; ++i) {
        ++it;
    }
    EXPECT_DOUBLE_EQ(14.0, *it);
    ++it;
    EXPECT_EQ(it, _data.end());
    ++it;
    EXPECT_EQ(it, _data.end());
}
