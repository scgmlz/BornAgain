#ifndef INTENSITYDATAFUNCTIONSTEST_H
#define INTENSITYDATAFUNCTIONSTEST_H



#include "IntensityDataFunctions.h"
#include "VariableBinAxis.h"

class IntensityDataFunctionsTest : public ::testing::Test
{
 protected:
    IntensityDataFunctionsTest(){}
    virtual ~IntensityDataFunctionsTest(){}

};



TEST_F(IntensityDataFunctionsTest, ClipDataSetFixed)
{
    OutputData<double> data;
    FixedBinAxis axis0("axis0",10, -5.0, 5.0);
    data.addAxis(axis0);
    FixedBinAxis axis1("axis1",3, 0.0, 3.0);
    data.addAxis(axis1);

    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
        data[i] = i;
    }

    OutputData<double> *clip = IntensityDataFunctions::createClippedDataSet(data, -5.0, 0.0, -1.5, 1.5);
    std::vector<double> vref = {0.0, 1.0, 3.0, 4.0, 6.0, 7.0, 9.0, 10.0};
    EXPECT_EQ(clip->getAllocatedSize(), size_t(8));
    int index(0);
    for(size_t i=0; i<clip->getAllocatedSize(); ++i) {
        EXPECT_EQ(vref[index++], (*clip)[i]);
    }
    delete clip;
}


TEST_F(IntensityDataFunctionsTest, ClipDataSetVariable)
{
    static const double arr[] = {-1.0, -0.5, 0.5, 1.0, 2.0};
    std::vector<double> values (arr, arr + sizeof(arr) / sizeof(arr[0]) );

    OutputData<double> data;
    VariableBinAxis axis0("axis0",4, values);
    data.addAxis(axis0);
    VariableBinAxis axis1("axis1",4, values);
    data.addAxis(axis1);

    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
        data[i] = i;
    }

    OutputData<double> *clip = IntensityDataFunctions::createClippedDataSet(data, -0.5, 0.5, 0.99, 2.0);
    std::vector<double> vref = {6.0, 7.0, 10.0, 11.0};
    EXPECT_EQ(clip->getAllocatedSize(), size_t(4));
    int index(0);
    for(size_t i=0; i<clip->getAllocatedSize(); ++i) {
        EXPECT_EQ(vref[index++], (*clip)[i]);
    }
    delete clip;


}


//-------------------------------------------------  2.5
// 2 ||  2  |  5  |  8  | 11  | 14 | 17 | 20 | 23 |
//------------------------------------------------
// 1 ||  1  |  4  |  7  | 10  | 13 | 16 | 19 | 22 |
//------------------------------------------------
// 0 ||  0  |  3  |  6  |  9  | 12 | 15 | 18 | 21 |
//================================================== -0.5
//   ||  0  |  1  |  2  |  3  |  4 |  5 |  6 |  7 |
// -4.5                                         3.5

//TEST_F(IntensityDataFunctionsTest, AddRectangularMask)
//{
//    OutputData<double > data;
//    data.addAxis("x", 8, -4.5, 3.5);
//    data.addAxis("y", 3, -0.5, 2.5);
//    data.setAllTo(0.0);
//    IntensityDataFunctions::addRectangularMask(data, -3.0, -0.5, 1.0, 1.49);
//    IntensityDataFunctions::addRectangularMask(data, 1.5, 0.5, 3.5, 2.5);

//    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
//        data[i] = i;
//    }

//    int index(0);

//    std::vector<double> xref = {-4.0, -4.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0);
//    std::vector<double> yref = {0.0, 1.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 0.0, 0.0);
//    std::vector<double> vref = {0, 1, 2, 5, 8, 11, 14, 17, 18, 21);
//    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
//        double x = data.getAxisValue(it.getIndex(), "x");
//        double y = data.getAxisValue(it.getIndex(), "y");
//        EXPECT_EQ(x, xref[index]);
//        EXPECT_EQ(y, yref[index]);
//        EXPECT_EQ(*it, vref[index]);
//        ++index;
//    }
//    data.removeAllMasks();
//    index=0;
//    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
//        EXPECT_EQ( int(index++), int(it.getIndex()) );
//    }
//}


//TEST_F(IntensityDataFunctionsTest, AddRectangularMask2)
//{
//    OutputData<double > data;
//    data.addAxis("x", 8, -4.5, 3.5);
//    data.addAxis("y", 3, -0.5, 2.5);
//    data.setAllTo(0.0);
//    IntensityDataFunctions::addRectangularMask(data, -3.0, -0.5, 1.0, 1.49, false);
//    IntensityDataFunctions::addRectangularMask(data, 1.5, 0.5, 3.5, 2.5, false);

//    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
//        data[i] = i;
//    }

//    int index(0);

//    std::vector<double> xref = {-4.0, -4.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0);
//    std::vector<double> yref = {0.0, 1.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 0.0, 0.0);
//    std::vector<double> vref = {0, 1, 2, 5, 8, 11, 14, 17, 18, 21);
//    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
//        double x = data.getValueOfAxis("x", it.getIndex());
//        double y = data.getValueOfAxis("y", it.getIndex());
//        EXPECT_EQ(x, xref[index]);
//        EXPECT_EQ(y, yref[index]);
//        EXPECT_EQ(*it, vref[index]);
//        ++index;
//    }
//    data.removeAllMasks();
//    index=0;
//    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
//        EXPECT_EQ( int(index++), int(it.getIndex()) );
//    }
//}


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


//! Transformation of coordinates from one OutputData to another using convertion from axes
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
    EXPECT_FLOAT_EQ(x, -5.0);
    EXPECT_FLOAT_EQ(y, -5.0);

    x = 3.1; y = 5.1;
    IntensityDataFunctions::coordinateToBinf(x, y, data1);
    IntensityDataFunctions::coordinateFromBinf(x, y, data2);
    EXPECT_FLOAT_EQ(x, 71.0);
    EXPECT_FLOAT_EQ(y, 21.0);

}

#endif // INTENSITYDATAFUNCTIONSTEST_H
