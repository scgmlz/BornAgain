#include "Core/Intensity/OutputData.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Binning/VariableBinAxis.h"
#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Parametrization/ThreadInfo.h"
#include "Tests/GTestWrapper/google_test.h"
#include <algorithm>

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
    for (size_t i = 0; i < 2000; ++i) {
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
    std::vector<unsigned> coordinates;
    coordinates.push_back(11);
    coordinates.push_back(4);
    coordinates.push_back(3);
    EXPECT_DOUBLE_EQ((double)1143, db_data_3d[db_data_3d.toGlobalIndex(coordinates)]);

    std::vector<unsigned> coordinates2;
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
    EXPECT_TRUE(data1.hasSameDimensions(data2));
    EXPECT_TRUE(data1.hasSameShape(data2));

    data1.addAxis("axis2", 10, 0., 10.);
    data2.addAxis("axis2", 10, 1., 10.);
    EXPECT_TRUE(data1.hasSameDimensions(data2));
    EXPECT_FALSE(data1.hasSameShape(data2));

    data2.copyFrom(data1);
    EXPECT_TRUE(data1.hasSameDimensions(data2));
    EXPECT_TRUE(data1.hasSameShape(data2));

    data1.addAxis("axis3", 10, 0., 10.);
    data2.addAxis("axis3another", 10, 0., 10.);
    EXPECT_TRUE(data1.hasSameDimensions(data2));
    EXPECT_FALSE(data1.hasSameShape(data2));

    data1.setAllTo(10);
    data2.copyFrom(data1);
    EXPECT_TRUE(data1.totalSum() == data2.totalSum());
    EXPECT_TRUE(data1.hasSameDimensions(data2));
    EXPECT_TRUE(data1.hasSameShape(data2));
    EXPECT_TRUE(data2.hasSameDimensions(data1));
    EXPECT_TRUE(data2.hasSameShape(data1));
    EXPECT_TRUE(data1.hasSameDimensions(data1));
    EXPECT_TRUE(data1.hasSameShape(data1));
    EXPECT_TRUE(data2.hasSameDimensions(data2));
    EXPECT_TRUE(data2.hasSameShape(data2));

    OutputData<Eigen::Matrix2d> mdata1;
    OutputData<Eigen::Matrix2d> mdata2;
    mdata1.addAxis("axis1", 10, 0., 10.);
    mdata2.addAxis("axis1", 10, 0., 10.);
    EXPECT_TRUE(mdata1.hasSameDimensions(mdata2));
    EXPECT_TRUE(mdata1.hasSameShape(mdata2));

    mdata1.addAxis("axis2", 10, 0., 10.);
    mdata2.addAxis("axis2", 10, 1., 10.);
    EXPECT_TRUE(mdata1.hasSameDimensions(mdata2));
    EXPECT_FALSE(mdata1.hasSameShape(mdata2));

    mdata2.copyFrom(mdata1);
    EXPECT_TRUE(mdata1.hasSameDimensions(mdata2));
    EXPECT_TRUE(mdata1.hasSameShape(mdata2));

    mdata1.setAllTo(Eigen::Matrix2d::Identity());
    mdata2.copyFrom(mdata1);
    EXPECT_TRUE(mdata1.hasSameDimensions(mdata2));
    EXPECT_TRUE(mdata1.hasSameShape(mdata2));
    EXPECT_TRUE(mdata2.hasSameDimensions(mdata1));
    EXPECT_TRUE(mdata2.hasSameShape(mdata1));
    EXPECT_TRUE(mdata1.hasSameDimensions(mdata1));
    EXPECT_TRUE(mdata1.hasSameShape(mdata1));
    EXPECT_TRUE(mdata2.hasSameDimensions(mdata2));
    EXPECT_TRUE(mdata2.hasSameShape(mdata2));
}

TEST_F(OutputDataTest, MaxElement)
{
    OutputData<double> data;
    data.addAxis("axis1", 10, 0., 10.);
    data.addAxis("axis2", 2, 0., 10.);
    data.setAllTo(1.0);

    OutputData<double>::iterator it = data.begin();
    for (size_t i = 0; i < data.getAllocatedSize(); ++i)
        if (i == 10)
            (*it) = 10.0;
    OutputData<double>::const_iterator cit = std::max_element(data.begin(), data.end());
    EXPECT_EQ(double(10.0), (*cit));
}

// y |
// --------------------------------------------
// 1 | 1   3   5   7   9   11  13  15  17  19 |
// 0 | 0   2   4   6   8   10  12  14  16  18 |
// --------------------------------------------
//   | 0   1   2   3   4   5   6   7   8   9  | x
TEST_F(OutputDataTest, ValueOfAxis)
{
    OutputData<double> data;
    data.addAxis("axis1", 10, 0., 10.);
    data.addAxis("axis2", 2, 0., 10.);
    EXPECT_EQ(0.5, data.getAxisValue(0, "axis1"));
    EXPECT_EQ(0.5, data.getAxisValue(1, "axis1"));
    EXPECT_EQ(1.5, data.getAxisValue(2, "axis1"));
    EXPECT_EQ(1.5, data.getAxisValue(3, "axis1"));
    EXPECT_EQ(9.5, data.getAxisValue(18, "axis1"));
    EXPECT_EQ(9.5, data.getAxisValue(19, "axis1"));

    EXPECT_EQ(2.5, data.getAxisValue(0, "axis2"));
    EXPECT_EQ(7.5, data.getAxisValue(1, "axis2"));
    EXPECT_EQ(2.5, data.getAxisValue(2, "axis2"));
    EXPECT_EQ(7.5, data.getAxisValue(3, "axis2"));
    EXPECT_EQ(2.5, data.getAxisValue(18, "axis2"));
    EXPECT_EQ(7.5, data.getAxisValue(19, "axis2"));

    std::vector<double> coordinates = data.getAxesValues(18);
    EXPECT_EQ(9.5, coordinates[0]);
    EXPECT_EQ(2.5, coordinates[1]);

    OutputData<Eigen::Matrix2d> mdata;
    mdata.addAxis("axis1", 10, 0., 10.);
    mdata.addAxis("axis2", 2, 0., 10.);
    EXPECT_EQ(0.5, mdata.getAxisValue(0, "axis1"));
    EXPECT_EQ(0.5, mdata.getAxisValue(1, "axis1"));
    EXPECT_EQ(1.5, mdata.getAxisValue(2, "axis1"));
    EXPECT_EQ(1.5, mdata.getAxisValue(3, "axis1"));
    EXPECT_EQ(9.5, mdata.getAxisValue(18, "axis1"));
    EXPECT_EQ(9.5, mdata.getAxisValue(19, "axis1"));

    EXPECT_EQ(2.5, mdata.getAxisValue(0, "axis2"));
    EXPECT_EQ(7.5, mdata.getAxisValue(1, "axis2"));
    EXPECT_EQ(2.5, mdata.getAxisValue(2, "axis2"));
    EXPECT_EQ(7.5, mdata.getAxisValue(3, "axis2"));
    EXPECT_EQ(2.5, mdata.getAxisValue(18, "axis2"));
    EXPECT_EQ(7.5, mdata.getAxisValue(19, "axis2"));
}

// y |
// --------------------------------------------
// 1 | 1   3   5   7   9   11  13  15  17  19 |
// 0 | 0   2   4   6   8   10  12  14  16  18 |
// --------------------------------------------
//   | 0   1   2   3   4   5   6   7   8   9  | x
TEST_F(OutputDataTest, GetAxisBin)
{
    OutputData<double> data;
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

TEST_F(OutputDataTest, SetCleared)
{
    db_data_3d.clear();
    db_data_3d.setAllTo(1.0);
    EXPECT_EQ(db_data_3d[0], 1.0);

    matrix_data_2d.clear();
    matrix_data_2d.setAllTo(10 * Eigen::Matrix2d::Identity());
    EXPECT_EQ(10 * Eigen::Matrix2d::Identity(), matrix_data_2d[0]);
}

TEST_F(OutputDataTest, MixedTypeOperations)
{
    OutputData<bool> data_bool;
    data_bool.addAxis("axis1", 10, 0.0, 10.0);

    OutputData<bool> data_double;
    data_double.addAxis("axis1", 10, 0.0, 10.0);

    EXPECT_TRUE(data_bool.hasSameShape(data_double));

    data_double.addAxis("axis2", 10, -1.0, 1.0);
    EXPECT_FALSE(data_bool.hasSameShape(data_double));
}
