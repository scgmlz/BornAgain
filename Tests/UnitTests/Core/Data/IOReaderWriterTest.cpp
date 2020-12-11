#include "Device/InputOutput/OutputDataReadWriteINT.h"
#include "Device/InputOutput/OutputDataReadWriteNumpyTXT.h"
#include "Device/InputOutput/OutputDataReadWriteTiff.h"
#include "Tests/GTestWrapper/google_test.h"

class IOReaderWriterTest : public ::testing::Test {
protected:
    IOReaderWriterTest();

    OutputData<double> m_model_data;
};

IOReaderWriterTest::IOReaderWriterTest() {
    FixedBinAxis axis1("x", 5, 1.0, 5.0);
    FixedBinAxis axis2("y", 10, 6.0, 7.0);
    m_model_data.addAxis(axis1);
    m_model_data.addAxis(axis2);
    for (size_t i = 0, size = m_model_data.getAllocatedSize(); i < size; ++i)
        m_model_data[i] = static_cast<double>(i);
}

TEST_F(IOReaderWriterTest, TestOutputDataReadWriteINT) {
    std::stringstream ss;
    OutputDataReadWriteINT write_int;
    write_int.writeOutputData(m_model_data, ss);
    OutputDataReadWriteINT read_int;
    auto result = std::unique_ptr<OutputData<double>>(read_int.readOutputData(ss));

    auto compare_axis = [this, &result](size_t index) {
        EXPECT_EQ(m_model_data.axis(index).size(), result->axis(index).size());
        EXPECT_EQ(m_model_data.axis(index).lowerBound(), result->axis(index).lowerBound());
        EXPECT_EQ(m_model_data.axis(index).upperBound(), result->axis(index).upperBound());
    };

    EXPECT_EQ(m_model_data.rank(), result->rank());
    EXPECT_EQ(m_model_data.getAllSizes(), result->getAllSizes());
    compare_axis(0);
    compare_axis(1);
    for (size_t i = 0, size = m_model_data.getAllocatedSize(); i < size; ++i)
        EXPECT_EQ(m_model_data[i], (*result)[i]);
}

TEST_F(IOReaderWriterTest, TestOutputDataReadWriteNumpyTXT) {
    std::stringstream ss;
    OutputDataReadWriteNumpyTXT write_txt;
    write_txt.writeOutputData(m_model_data, ss);

    OutputDataReadWriteNumpyTXT read_txt;
    auto result = std::unique_ptr<OutputData<double>>(read_txt.readOutputData(ss));
    EXPECT_EQ(m_model_data.rank(), result->rank());
    EXPECT_EQ(m_model_data.getAllSizes(), result->getAllSizes());
    for (size_t i = 0, size = m_model_data.getAllocatedSize(); i < size; ++i)
        EXPECT_EQ(m_model_data[i], (*result)[i]);
}

#ifdef BORNAGAIN_TIFF_SUPPORT

TEST_F(IOReaderWriterTest, TestOutputDataReadWriteTiff) {
    std::stringstream ss;
    OutputDataReadWriteTiff write_tiff;
    write_tiff.writeOutputData(m_model_data, ss);

    OutputDataReadWriteTiff read_tiff;
    auto result = std::unique_ptr<OutputData<double>>(read_tiff.readOutputData(ss));
    EXPECT_EQ(m_model_data.rank(), result->rank());
    EXPECT_EQ(m_model_data.getAllSizes(), result->getAllSizes());
    for (size_t i = 0, size = m_model_data.getAllocatedSize(); i < size; ++i)
        EXPECT_EQ(m_model_data[i], (*result)[i]);
}

#endif // BORNAGAIN_TIFF_SUPPORT
