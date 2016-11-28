#ifndef OUTPUTDATATEST_H
#define OUTPUTDATATEST_H

#include "OutputData.h"
#include <algorithm>
#include "IntensityDataFunctions.h"
#include "VariableBinAxis.h"
#include "FixedBinAxis.h"
#include "ThreadInfo.h"

class OutputDataTest : public ::testing::Test
{
 protected:
    OutputDataTest();

    OutputData<int> int_data_0d;
    OutputData<float> fl_data_1d;
    OutputData<double> db_data_3d;
    std::vector<size_t> zero_3d_coordinate;

    OutputData<Eigen::Matrix2d> matrix_data_2d;
};

OutputDataTest::OutputDataTest()
{
    zero_3d_coordinate.push_back(0);
    zero_3d_coordinate.push_back(0);
    zero_3d_coordinate.push_back(0);
    FixedBinAxis angle_axis("angle", 20, 0.0, 0.1);
    FixedBinAxis length_axis("length", 10, 0.0, 0.5);
    FixedBinAxis index_axis("index", 10, 1, 10);
    fl_data_1d.addAxis(angle_axis);

    db_data_3d.addAxis(angle_axis);
    db_data_3d.addAxis(length_axis);
    db_data_3d.addAxis(index_axis);
    OutputData<double>::iterator it = db_data_3d.begin();
    for (size_t i=0; i<2000; ++i)
    {
        *it = (double)i;
        ++it;
    }

    matrix_data_2d.addAxis(angle_axis);
    matrix_data_2d.addAxis(length_axis);
    matrix_data_2d.setAllTo(Eigen::Matrix2d::Identity());
}


TEST_F(OutputDataTest, SingleElementAfterConstruction)
{
    EXPECT_EQ(1u, int_data_0d.getAllocatedSize());
}


TEST_F(OutputDataTest, SizeAfterAddingAxes)
{
    EXPECT_EQ(1u, int_data_0d.getAllocatedSize());
    EXPECT_EQ(20u, fl_data_1d.getAllocatedSize());
    EXPECT_EQ(2000u, db_data_3d.getAllocatedSize());

    EXPECT_EQ(200u, matrix_data_2d.getAllocatedSize());
}


TEST_F(OutputDataTest, DataInitialization)
{
    std::vector<int> coordinates;
    coordinates.push_back(11);
    coordinates.push_back(4);
    coordinates.push_back(3);
    EXPECT_DOUBLE_EQ((double)1143, db_data_3d[db_data_3d.toGlobalIndex(coordinates)]);

    std::vector<int> coordinates2;
    coordinates2.push_back(10);
    coordinates2.push_back(5);
    EXPECT_EQ(Eigen::Matrix2d::Identity(),
              matrix_data_2d[matrix_data_2d.toGlobalIndex(coordinates2)]);
}

TEST_F(OutputDataTest, isInitialized)
{
    OutputData<double> data1;
    EXPECT_FALSE(data1.isInitialized());
    data1.addAxis("axis", 10, 0.0, 10.0);
    EXPECT_TRUE(data1.isInitialized());
    data1.clear();
    EXPECT_FALSE(data1.isInitialized());
}

TEST_F(OutputDataTest, DataCopying)
{
    OutputData<double> data1;
    OutputData<double> data2;
    data1.addAxis("axis1", 10, 0., 10.);
    data2.addAxis("axis1", 10, 0., 10.);
    EXPECT_TRUE( data1.hasSameDimensions(data2));
    EXPECT_TRUE( data1.hasSameShape(data2));

    data1.addAxis("axis2", 10, 0., 10.);
    data2.addAxis("axis2", 10, 1., 10.);
    EXPECT_TRUE( data1.hasSameDimensions(data2));
    EXPECT_FALSE( data1.hasSameShape(data2));

    data2.copyFrom(data1);
    EXPECT_TRUE( data1.hasSameDimensions(data2));
    EXPECT_TRUE( data1.hasSameShape(data2));

    data1.addAxis("axis3", 10, 0., 10.);
    data2.addAxis("axis3another", 10, 0., 10.);
    EXPECT_TRUE( data1.hasSameDimensions(data2));
    EXPECT_FALSE( data1.hasSameShape(data2));

    data1.setAllTo(10);
    data2.copyFrom(data1);
    EXPECT_TRUE( data1.totalSum() == data2.totalSum() );
    EXPECT_TRUE( data1.hasSameDimensions(data2));
    EXPECT_TRUE( data1.hasSameShape(data2));
    EXPECT_TRUE( data2.hasSameDimensions(data1));
    EXPECT_TRUE( data2.hasSameShape(data1));
    EXPECT_TRUE( data1.hasSameDimensions(data1));
    EXPECT_TRUE( data1.hasSameShape(data1));
    EXPECT_TRUE( data2.hasSameDimensions(data2));
    EXPECT_TRUE( data2.hasSameShape(data2));

    OutputData<Eigen::Matrix2d> mdata1;
    OutputData<Eigen::Matrix2d> mdata2;
    mdata1.addAxis("axis1", 10, 0., 10.);
    mdata2.addAxis("axis1", 10, 0., 10.);
    EXPECT_TRUE( mdata1.hasSameDimensions(mdata2));
    EXPECT_TRUE( mdata1.hasSameShape(mdata2));

    mdata1.addAxis("axis2", 10, 0., 10.);
    mdata2.addAxis("axis2", 10, 1., 10.);
    EXPECT_TRUE( mdata1.hasSameDimensions(mdata2));
    EXPECT_FALSE( mdata1.hasSameShape(mdata2));

    mdata2.copyFrom(mdata1);
    EXPECT_TRUE( mdata1.hasSameDimensions(mdata2));
    EXPECT_TRUE( mdata1.hasSameShape(mdata2));

    mdata1.setAllTo(Eigen::Matrix2d::Identity());
    mdata2.copyFrom(mdata1);
    EXPECT_TRUE( mdata1.hasSameDimensions(mdata2));
    EXPECT_TRUE( mdata1.hasSameShape(mdata2));
    EXPECT_TRUE( mdata2.hasSameDimensions(mdata1));
    EXPECT_TRUE( mdata2.hasSameShape(mdata1));
    EXPECT_TRUE( mdata1.hasSameDimensions(mdata1));
    EXPECT_TRUE( mdata1.hasSameShape(mdata1));
    EXPECT_TRUE( mdata2.hasSameDimensions(mdata2));
    EXPECT_TRUE( mdata2.hasSameShape(mdata2));
}


TEST_F(OutputDataTest, MaxElement)
{
    OutputData<double > data;
    data.addAxis("axis1", 10, 0., 10.);
    data.addAxis("axis2", 2, 0., 10.);
    data.setAllTo(1.0);

    OutputData<double >::iterator it = data.begin();
    for (size_t i=0; i<data.getAllocatedSize(); ++i) if(i==10) (*it)=10.0;
    OutputData<double >::const_iterator cit = std::max_element(data.begin(), data.end());
    EXPECT_EQ( double(10.0), (*cit));
}


// y |
// --------------------------------------------
// 1 | 1   3   5   7   9   11  13  15  17  19 |
// 0 | 0   2   4   6   8   10  12  14  16  18 |
// --------------------------------------------
//   | 0   1   2   3   4   5   6   7   8   9  | x
TEST_F(OutputDataTest, ValueOfAxis)
{
    OutputData<double > data;
    data.addAxis("axis1", 10, 0., 10.);
    data.addAxis("axis2", 2, 0., 10.);
    EXPECT_EQ( 0.5, data.getAxisValue(0, "axis1"));
    EXPECT_EQ( 0.5, data.getAxisValue(1, "axis1"));
    EXPECT_EQ( 1.5, data.getAxisValue(2, "axis1"));
    EXPECT_EQ( 1.5, data.getAxisValue(3, "axis1"));
    EXPECT_EQ( 9.5, data.getAxisValue(18, "axis1"));
    EXPECT_EQ( 9.5, data.getAxisValue(19, "axis1"));

    EXPECT_EQ( 2.5, data.getAxisValue(0, "axis2"));
    EXPECT_EQ( 7.5, data.getAxisValue(1, "axis2"));
    EXPECT_EQ( 2.5, data.getAxisValue(2, "axis2"));
    EXPECT_EQ( 7.5, data.getAxisValue(3, "axis2"));
    EXPECT_EQ( 2.5, data.getAxisValue(18, "axis2"));
    EXPECT_EQ( 7.5, data.getAxisValue(19, "axis2"));

    std::vector<double > coordinates = data.getAxesValues(18);
    EXPECT_EQ(9.5, coordinates[0]);
    EXPECT_EQ(2.5, coordinates[1]);

    OutputData<Eigen::Matrix2d > mdata;
    mdata.addAxis("axis1", 10, 0., 10.);
    mdata.addAxis("axis2", 2, 0., 10.);
    EXPECT_EQ( 0.5, mdata.getAxisValue(0, "axis1"));
    EXPECT_EQ( 0.5, mdata.getAxisValue(1, "axis1"));
    EXPECT_EQ( 1.5, mdata.getAxisValue(2, "axis1"));
    EXPECT_EQ( 1.5, mdata.getAxisValue(3, "axis1"));
    EXPECT_EQ( 9.5, mdata.getAxisValue(18, "axis1"));
    EXPECT_EQ( 9.5, mdata.getAxisValue(19, "axis1"));

    EXPECT_EQ( 2.5, mdata.getAxisValue(0, "axis2"));
    EXPECT_EQ( 7.5, mdata.getAxisValue(1, "axis2"));
    EXPECT_EQ( 2.5, mdata.getAxisValue(2, "axis2"));
    EXPECT_EQ( 7.5, mdata.getAxisValue(3, "axis2"));
    EXPECT_EQ( 2.5, mdata.getAxisValue(18, "axis2"));
    EXPECT_EQ( 7.5, mdata.getAxisValue(19, "axis2"));
}

// y |
// --------------------------------------------
// 1 | 1   3   5   7   9   11  13  15  17  19 |
// 0 | 0   2   4   6   8   10  12  14  16  18 |
// --------------------------------------------
//   | 0   1   2   3   4   5   6   7   8   9  | x
TEST_F(OutputDataTest, GetAxisBin)
{
    OutputData<double > data;
    data.addAxis("axis1", 10, 0., 10.);
    data.addAxis("axis2", 2, 0., 10.);

    EXPECT_EQ(0.5, data.getAxisBin(0, "axis1").getMidPoint());
    EXPECT_EQ(0.5, data.getAxisBin(1, "axis1").getMidPoint());
    EXPECT_EQ(9.5, data.getAxisBin(18, "axis1").getMidPoint());
    EXPECT_EQ(9.5, data.getAxisBin(19, "axis1").getMidPoint());
    EXPECT_EQ(2.5, data.getAxisBin(0, "axis2").getMidPoint());
    EXPECT_EQ(7.5, data.getAxisBin(1, "axis2").getMidPoint());
    EXPECT_EQ(2.5, data.getAxisBin(18, "axis2").getMidPoint());
    EXPECT_EQ(7.5, data.getAxisBin(19, "axis2").getMidPoint());
}



// y |
// --------------------------------------------
// 5 | 5   11  17  23  29  35  41  47  53  59 |
// 4 | 4   10  16  22  28  34  40  46  52  58 |
// 3 | 3   9   15  21  27  33  39  45  51  57 |
// 2 | 2   8   14  20  26  32  38  44  50  56 |
// 1 | 1   7   13  19  25  31  37  43  49  55 |
// 0 | 0   6   12  18  24  30  36  42  48  54 |
// --------------------------------------------
//   | 0   1   2   3   4   5   6   7   8   9  | x

//TEST_F(OutputDataTest, SetInverseRectangularMask)
//{
//    OutputData<double > data;
//    data.addAxis("x", 10, 0., 10.);
//    data.addAxis("y", 6, 0., 6.);
//    data.setAllTo(0.0);
//    IntensityDataFunctions::setRectangularMask(data, 1.0, 1.0, 4.99, 2.99, true);

//    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
//        data[i] = i;
//    }

//    int index(0);

//    std::vector<double> xref = {1.5, 1.5, 2.5, 2.5, 3.5, 3.5, 4.5, 4.5);
//    std::vector<double> yref = {1.5, 2.5, 1.5, 2.5, 1.5, 2.5, 1.5, 2.5);
//    std::vector<double> vref = {7, 8, 13, 14, 19, 20, 25, 26);
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


//-------------------------------------------------  2.5
// 2 ||  2  |  5  |  8  | 11  | 14 | 17 | 20 | 23 |
//------------------------------------------------
// 1 ||  1  |  4  |  7  | 10  | 13 | 16 | 19 | 22 |
//------------------------------------------------
// 0 ||  0  |  3  |  6  |  9  | 12 | 15 | 18 | 21 |
//================================================== -0.5
//   ||  0  |  1  |  2  |  3  |  4 |  5 |  6 |  7 |
// -4.5                                         3.5

//TEST_F(OutputDataTest, SetRectangularMask)
//{
//    OutputData<double > data;
//    data.addAxis("x", 8, -4.5, 3.5);
//    data.addAxis("y", 3, -0.5, 2.5);
//    data.setAllTo(0.0);
//    IntensityDataFunctions::setRectangularMask(data, -3.0, -0.5, 1.0, 1.49);

//    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
//        data[i] = i;
//    }

//    int index(0);

//    std::vector<double> xref = {-4.0, -4.0, -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 2.0, 2.0, 3.0, 3.0, 3.0);
//    std::vector<double> yref = {0.0, 1.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 0.0, 1.0, 2.0, 0.0, 1.0, 2.0);
//    std::vector<double> vref = {0, 1, 2, 5, 8, 11, 14, 17, 18, 19, 20, 21, 22, 23);
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


//-------------------------------------------------  2.5
// 2 ||  2  |  5  |  8  | 11  | 14 | 17 | 20 | 23 |
//------------------------------------------------
// 1 ||  1  |  4  |  7  | 10  | 13 | 16 | 19 | 22 |
//------------------------------------------------
// 0 ||  0  |  3  |  6  |  9  | 12 | 15 | 18 | 21 |
//================================================== -0.5
//   ||  0  |  1  |  2  |  3  |  4 |  5 |  6 |  7 |
// -4.5                                         3.5

//TEST_F(OutputDataTest, SetEllipticMask)
//{
//    OutputData<double > data;
//    data.addAxis("x", 8, -4.5, 3.5);
//    data.addAxis("y", 3, -0.5, 2.5);
//    data.setAllTo(0.0);
//    IntensityDataFunctions::setEllipticMask(data, 0.0, 1.0, 2.0, 1.0);

//    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
//        data[i] = i;
//    }

//    int index(0);

//    std::vector<double> vref = {0, 1, 2, 3, 4, 5, 6, 8, 9, 11, 15, 17, 18, 20, 21, 22, 23);
//    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
//        EXPECT_EQ(*it, vref[index]);
//        ++index;
//    }
//    data.removeAllMasks();
//    index=0;
//    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
//        EXPECT_EQ( int(index++), int(it.getIndex()) );
//    }
//}


//TEST_F(OutputDataTest, RectangularMaskVariableAxis)
//{
//    static const double x_arr[] = {-5., -3., -2., 0.0, 0.5, 1.0, 3.0, 5.0, 6.0};
//    std::vector<double> x_values (x_arr, x_arr + sizeof(x_arr) / sizeof(x_arr[0]) );
//    VariableBinAxis xaxis("x", 8, x_values);

//    static const double y_arr[] = {0.0, 1.0, 3.0, 5.0, 6.0};
//    std::vector<double> y_values (y_arr, y_arr + sizeof(y_arr) / sizeof(y_arr[0]) );
//    VariableBinAxis yaxis("y", 4, y_values);

//    OutputData<double > data;
//    data.addAxis(xaxis);
//    data.addAxis(yaxis);
//    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
//        data[i] = i;
//    }

//    IntensityDataFunctions::setRectangularMask(data, -2.5, 1.5, 0.99, 4.99, true);
//    int index(0);

//    std::vector<double> xref = {-2.5, -2.5, -1.0, -1.0, 0.25, 0.25, 0.75, 0.75);
//    std::vector<double> yref = {2.0, 4.0, 2.0, 4.0, 2.0, 4.0, 2.0, 4.0);
//    std::vector<double> vref = {5, 6, 9, 10, 13, 14, 17, 18);
//    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
//        double x = data.getAxisValue(it.getIndex(), "x");
//        double y = data.getAxisValue(it.getIndex(), "y");
//        double val = *it;
//        EXPECT_EQ(x, xref[index]);
//        EXPECT_EQ(y, yref[index]);
//        EXPECT_EQ(val, vref[index]);
//        ++index;
//    }
//}


//! FIXME EllipticMask is not working
//TEST_F(OutputDataTest, EllipticMaskVariableAxis)
//{
//    static const double x_arr[] = {-5., -3., -2., 0.0, 0.5, 1.0, 3.0, 5.0, 6.0};
//    std::vector<double> x_values (x_arr, x_arr + sizeof(x_arr) / sizeof(x_arr[0]) );
//    VariableBinAxis xaxis("x", 8, x_values);

//    static const double y_arr[] = {0.0, 1.0, 3.0, 5.0, 6.0};
//    std::vector<double> y_values (y_arr, y_arr + sizeof(y_arr) / sizeof(y_arr[0]) );
//    VariableBinAxis yaxis("y", 4, y_values);

//    OutputData<double > data;
//    data.addAxis(xaxis);
//    data.addAxis(yaxis);
//    for(size_t i=0; i<data.getAllocatedSize(); ++i) {
//        data[i] = i;
//    }

//    IntensityDataHelper::setEllipticMask(data, 1.0, 1.0, 0.49, 0.49);
//    int index(0);

////    std::vector<double> xref = {-2.5, -2.5, -1.0, -1.0, 0.25, 0.25, 0.75, 0.75};
////    std::vector<double> yref = {2.0, 4.0, 2.0, 4.0, 2.0, 4.0, 2.0, 4.0};
//    std::vector<double> vref = {8, 9, 12, 13);
//    for(OutputData<double>::iterator it = data.begin(); it!=data.end(); ++it) {
//        double x = data.getValueOfAxis("x", it.getIndex());
//        double y = data.getValueOfAxis("y", it.getIndex());
//        double val = *it;
////        EXPECT_EQ(x, xref[index]);
////        EXPECT_EQ(y, yref[index]);
////        EXPECT_EQ(val, vref[index]);
//        std::cout << x << " " << y <<  " " << val << std::endl;
//        ++index;
//    }
//}


TEST_F(OutputDataTest, SetCleared)
{
    db_data_3d.clear();
    db_data_3d.setAllTo(1.0);
    EXPECT_EQ( db_data_3d[0], 1.0);

    matrix_data_2d.clear();
    matrix_data_2d.setAllTo(10*Eigen::Matrix2d::Identity());
    EXPECT_EQ(10*Eigen::Matrix2d::Identity(), matrix_data_2d[0]);
}

TEST_F(OutputDataTest, MixedTypeOperations)
{
    OutputData<bool> data_bool;
    data_bool.addAxis("axis1", 10, 0.0, 10.0);

    OutputData<bool> data_double;
    data_double.addAxis("axis1", 10, 0.0, 10.0);

    EXPECT_TRUE(data_bool.hasSameShape(data_double));

    data_double.addAxis("axis2",10, -1.0, 1.0);
    EXPECT_FALSE(data_bool.hasSameShape(data_double));
}

// y |
// --------------------------------------------
// 4 | 4   9   14  19  24  29  34  39  44  49 |
// 3 | 3   8   13  18  23  28  33  38  43  48 |
// 2 | 2   7   12  17  22  27  32  37  42  47 |
// 1 | 1   6   11  16  21  26  31  36  41  46 |
// 0 | 0   5   10  15  20  25  30  35  40  45 |
// --------------------------------------------
//   | 0   1   2   3   4   5   6   7   8   9  | x

#endif // OUTPUTDATATEST_H
