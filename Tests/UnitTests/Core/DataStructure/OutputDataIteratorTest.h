#ifndef OUTPUTDATAITERATORTEST_H
#define OUTPUTDATAITERATORTEST_H

#include "OutputDataIterator.h"

class OutputDataIteratorTest : public ::testing::Test
{
 protected:
    OutputDataIteratorTest();
    virtual ~OutputDataIteratorTest();

    OutputData<double> *p_data;
};

OutputDataIteratorTest::OutputDataIteratorTest()
{
    p_data = new OutputData<double>();
    int *dims = new int[2];
    dims[0] = 3;
    dims[1] = 5;
    p_data->setAxisSizes(2, dims);
    double value = 0.0;
    OutputData<double>::iterator it = p_data->begin();
    while (it != p_data->end()) {
        *it = value;
        value += 1.0;
        ++it;
    }
}

OutputDataIteratorTest::~OutputDataIteratorTest()
{
    delete p_data;
}

TEST_F(OutputDataIteratorTest, Iterate)
{
    OutputData<double>::iterator it = p_data->begin();
    EXPECT_EQ(0.0, *it);
    for (size_t i=0; i<14; ++i) {
        ++it;
    }
    EXPECT_DOUBLE_EQ(14.0, *it);
    ++it;
    EXPECT_EQ(it, p_data->end());
    ++it;
    EXPECT_EQ(it, p_data->end());
}

TEST_F(OutputDataIteratorTest, ConstIterate)
{
    OutputData<double>::const_iterator it = p_data->begin();
    EXPECT_EQ(0.0, *it);
    for (size_t i=0; i<14; ++i) {
        ++it;
    }
    EXPECT_DOUBLE_EQ(14.0, *it);
    ++it;
    EXPECT_EQ(it, p_data->end());
    ++it;
    EXPECT_EQ(it, p_data->end());
}

#endif // OUTPUTDATAITERATORTEST_H
