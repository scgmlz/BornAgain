#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Binning/VariableBinAxis.h"
#include "Tests/GTestWrapper/google_test.h"

class IntensityDataFunctionsTest : public ::testing::Test
{
};

TEST_F(IntensityDataFunctionsTest, ClipDataSetFixed)
{
    OutputData<double> data;
    FixedBinAxis axis0("axis0", 10, -5.0, 5.0);
    data.addAxis(axis0);
    FixedBinAxis axis1("axis1", 3, 0.0, 3.0);
    data.addAxis(axis1);

    for (size_t i = 0; i < data.getAllocatedSize(); ++i)
        data[i] = static_cast<double>(i);

    auto clip = IntensityDataFunctions::createClippedDataSet(data, -5.0, 0.0, -1.5, 1.5);
    std::vector<double> vref = {0.0, 1.0, 3.0, 4.0, 6.0, 7.0, 9.0, 10.0};
    EXPECT_EQ(clip->getAllocatedSize(), size_t(8));
    size_t index(0);
    for (size_t i = 0; i < clip->getAllocatedSize(); ++i)
        EXPECT_EQ(vref[index++], (*clip)[i]);
}

TEST_F(IntensityDataFunctionsTest, ClipDataSetVariable)
{
    static const double arr[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values(arr, arr + sizeof(arr) / sizeof(arr[0]));

    OutputData<double> data;
    VariableBinAxis axis0("axis0", 4, values);
    data.addAxis(axis0);
    VariableBinAxis axis1("axis1", 4, values);
    data.addAxis(axis1);

    for (size_t i = 0; i < data.getAllocatedSize(); ++i)
        data[i] = static_cast<double>(i);

    auto clip = IntensityDataFunctions::createClippedDataSet(data, -0.5, 0.5, 0.99, 2.0);
    std::vector<double> vref = {6.0, 7.0, 10.0, 11.0};
    EXPECT_EQ(clip->getAllocatedSize(), size_t(4));
    size_t index(0);
    for (size_t i = 0; i < clip->getAllocatedSize(); ++i)
        EXPECT_EQ(vref[index++], (*clip)[i]);
}

TEST_F(IntensityDataFunctionsTest, createRearrangedDataSet)
{
    OutputData<double> input_data;
    input_data.addAxis("axis0", 2, 1.0, 2.0);
    input_data.addAxis("axis1", 3, 3.0, 4.0);
    input_data.setRawDataVector(std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0});

    std::unique_ptr<OutputData<double>> output_data =
        IntensityDataFunctions::createRearrangedDataSet(input_data, 5);

    EXPECT_EQ(3.0, output_data->getAxis(0).getBinBoundaries().front());
    EXPECT_EQ(4.0, output_data->getAxis(0).getBinBoundaries().back());
    EXPECT_EQ(1.0, output_data->getAxis(1).getBinBoundaries().front());
    EXPECT_EQ(2.0, output_data->getAxis(1).getBinBoundaries().back());
    EXPECT_EQ(size_t(3), output_data->getAxis(0).size());
    EXPECT_EQ(size_t(2), output_data->getAxis(1).size());

    EXPECT_EQ(input_data[2], (*output_data)[0]);
    EXPECT_EQ(input_data[5], (*output_data)[1]);
    EXPECT_EQ(input_data[1], (*output_data)[2]);
    EXPECT_EQ(input_data[4], (*output_data)[3]);
    EXPECT_EQ(input_data[0], (*output_data)[4]);
    EXPECT_EQ(input_data[3], (*output_data)[5]);

    output_data = IntensityDataFunctions::createRearrangedDataSet(input_data, -6);

    EXPECT_EQ(1.0, output_data->getAxis(0).getBinBoundaries().front());
    EXPECT_EQ(2.0, output_data->getAxis(0).getBinBoundaries().back());
    EXPECT_EQ(3.0, output_data->getAxis(1).getBinBoundaries().front());
    EXPECT_EQ(4.0, output_data->getAxis(1).getBinBoundaries().back());
    EXPECT_EQ(size_t(2), output_data->getAxis(0).size());
    EXPECT_EQ(size_t(3), output_data->getAxis(1).size());

    EXPECT_EQ(input_data[5], (*output_data)[0]);
    EXPECT_EQ(input_data[4], (*output_data)[1]);
    EXPECT_EQ(input_data[3], (*output_data)[2]);
    EXPECT_EQ(input_data[2], (*output_data)[3]);
    EXPECT_EQ(input_data[1], (*output_data)[4]);
    EXPECT_EQ(input_data[0], (*output_data)[5]);

    output_data = IntensityDataFunctions::createRearrangedDataSet(input_data, 3);

    EXPECT_EQ(3.0, output_data->getAxis(0).getBinBoundaries().front());
    EXPECT_EQ(4.0, output_data->getAxis(0).getBinBoundaries().back());
    EXPECT_EQ(1.0, output_data->getAxis(1).getBinBoundaries().front());
    EXPECT_EQ(2.0, output_data->getAxis(1).getBinBoundaries().back());
    EXPECT_EQ(size_t(3), output_data->getAxis(0).size());
    EXPECT_EQ(size_t(2), output_data->getAxis(1).size());

    EXPECT_EQ(input_data[3], (*output_data)[0]);
    EXPECT_EQ(input_data[0], (*output_data)[1]);
    EXPECT_EQ(input_data[4], (*output_data)[2]);
    EXPECT_EQ(input_data[1], (*output_data)[3]);
    EXPECT_EQ(input_data[5], (*output_data)[4]);
    EXPECT_EQ(input_data[2], (*output_data)[5]);
}

TEST_F(IntensityDataFunctionsTest, coordinateToFromBinf)
{
    FixedBinAxis axis("axis", 8, -5.0, 3.0);
    EXPECT_EQ(0.5, IntensityDataFunctions::coordinateToBinf(-4.5, axis));
    EXPECT_EQ(-4.5, IntensityDataFunctions::coordinateFromBinf(0.5, axis));

    EXPECT_EQ(1.0, IntensityDataFunctions::coordinateToBinf(-4.0, axis));
    EXPECT_EQ(-4.0, IntensityDataFunctions::coordinateFromBinf(1.0, axis));

    EXPECT_EQ(-0.5, IntensityDataFunctions::coordinateToBinf(-5.5, axis));
    EXPECT_EQ(-5.5, IntensityDataFunctions::coordinateFromBinf(-0.5, axis));

    EXPECT_EQ(8.0, IntensityDataFunctions::coordinateToBinf(3.0, axis));
    EXPECT_EQ(3.0, IntensityDataFunctions::coordinateFromBinf(8.0, axis));

    EXPECT_EQ(8.5, IntensityDataFunctions::coordinateToBinf(3.5, axis));
    EXPECT_EQ(3.5, IntensityDataFunctions::coordinateFromBinf(8.5, axis));
}

//! Transformation of coordinates from one OutputData to another using conversion from axes
//! coordinates to bin-fraction-coordinates and then to another axes coordinates.

TEST_F(IntensityDataFunctionsTest, outputDataCoordinatesToFromBinf)
{
    OutputData<double> data1;
    data1.addAxis("axis0", 8, -5.0, 3.0);
    data1.addAxis("axis1", 3, 2.0, 5.0);

    OutputData<double> data2;
    data2.addAxis("axis0", 8, -10.0, 70.0);
    data2.addAxis("axis1", 3, -10.0, 20.0);

    double x(-4.5), y(2.5);
    IntensityDataFunctions::coordinateToBinf(x, y, data1);
    IntensityDataFunctions::coordinateFromBinf(x, y, data2);
    EXPECT_DOUBLE_EQ(x, -5.0);
    EXPECT_DOUBLE_EQ(y, -5.0);

    x = 3.1;
    y = 5.1;
    IntensityDataFunctions::coordinateToBinf(x, y, data1);
    IntensityDataFunctions::coordinateFromBinf(x, y, data2);
    EXPECT_DOUBLE_EQ(x, 71.0);
    EXPECT_DOUBLE_EQ(y, 21.0);
}

TEST_F(IntensityDataFunctionsTest, create2DArrayfromOutputDataTest)
{
    OutputData<double> out_data;
    out_data.addAxis("axis0", 2, 1.0, 2.0);
    out_data.addAxis("axis1", 3, 3.0, 4.0);
    EXPECT_EQ(6u, out_data.getAllocatedSize());

    EXPECT_EQ(2u, out_data.getAxis(0).size()); // no. of rows
    EXPECT_EQ(3u, out_data.getAxis(1).size()); // no. of cols

    std::vector<double> arr_in{1, 2, 3, 4, 5, 6};
    out_data.setRawDataVector(arr_in);

    EXPECT_EQ(arr_in[0], out_data[0]);
    EXPECT_EQ(arr_in[1], out_data[1]);
    EXPECT_EQ(arr_in[2], out_data[2]);
    EXPECT_EQ(arr_in[3], out_data[3]);
    EXPECT_EQ(arr_in[4], out_data[4]);
    EXPECT_EQ(arr_in[5], out_data[5]);

    auto arr_out = out_data.getRawDataVector();
    EXPECT_EQ(arr_in, arr_out);

    auto array_2d = IntensityDataFunctions::create2DArrayfromOutputData(out_data);

    std::vector<std::vector<double>> array_expected_2d{{arr_in[0], arr_in[1], arr_in[2]},
                                                       {arr_in[3], arr_in[4], arr_in[5]}};
    EXPECT_EQ(array_expected_2d, array_2d);
}

TEST_F(IntensityDataFunctionsTest, createOutputDatafrom2DArrayTest)
{
    std::vector<double> arr_in{1, 2, 3, 4, 5, 6};
    std::vector<std::vector<double>> array_2d{{arr_in[0], arr_in[1], arr_in[2]},
                                              {arr_in[3], arr_in[4], arr_in[5]}};
    auto data = IntensityDataFunctions::createOutputDatafrom2DArray(array_2d);
    EXPECT_EQ(arr_in, data->getRawDataVector());
}
