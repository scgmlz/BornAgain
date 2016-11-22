#ifndef FITOBJECTTEST_H
#define FITOBJECTTEST_H

#include "FitObject.h"
#include "GISASSimulation.h"
#include "BornAgainNamespace.h"
#include "Units.h"
#include <iostream>
#include "gtest/gtest.h"


class FitObjectTest : public ::testing::Test
{
 protected:
    FitObjectTest(){}
    virtual ~FitObjectTest(){}
};

//! Test of standard simulation/real_data pair.

TEST_F(FitObjectTest, StandardPair)
{
    size_t nx(5), ny(4);
    double xmin(-1.0), xmax(4.0), ymin(0.0), ymax(4.0);

    GISASSimulation simulation;
    simulation.setDetectorParameters(nx, xmin, xmax, ny, ymin, ymax);

    OutputData<double> data;
    data.addAxis(FixedBinAxis(BornAgain::PHI_AXIS_NAME, nx, xmin, xmax));
    data.addAxis(FixedBinAxis(BornAgain::ALPHA_AXIS_NAME, ny, ymin, ymax));
    double intensity(10.0);
    data.setAllTo(intensity);

    double weight(0.5);
    FitObject obj(simulation, data, weight);

    EXPECT_EQ(obj.weight(), weight);
    EXPECT_EQ(obj.numberOfFitElements(), size_t(nx*ny));

    EXPECT_EQ(obj.realData().getAxis(0).size(), nx);
    EXPECT_EQ(obj.realData().getAxis(1).size(), ny);
    EXPECT_EQ(obj.realData().getAxis(0).getMin(), xmin);
    EXPECT_EQ(obj.realData().getAxis(0).getMax(), xmax);
    EXPECT_EQ(obj.realData().getAxis(1).getMin(), ymin);
    EXPECT_EQ(obj.realData().getAxis(1).getMax(), ymax);

    EXPECT_EQ(obj.chiSquaredMap().getAxis(0).size(), nx);
    EXPECT_EQ(obj.chiSquaredMap().getAxis(1).size(), ny);
    EXPECT_EQ(obj.chiSquaredMap().getAxis(0).getMin(), xmin);
    EXPECT_EQ(obj.chiSquaredMap().getAxis(0).getMax(), xmax);
    EXPECT_EQ(obj.chiSquaredMap().getAxis(1).getMin(), ymin);
    EXPECT_EQ(obj.chiSquaredMap().getAxis(1).getMax(), ymax);
}

//! Test of the case when simulation has ROI.

TEST_F(FitObjectTest, RoiPair)
{
    int nx(5), ny(4);
    double xmin(-1.0), xmax(4.0), ymin(0.0), ymax(4.0);

    GISASSimulation simulation;
    simulation.setDetectorParameters(nx, xmin, xmax, ny, ymin, ymax);
    simulation.setRegionOfInterest(0.1, 1.1, 2.9, 3.9);

    // so new axes should be
    size_t roi_nx(3), roi_ny(3);
    double roi_xmin(0.0), roi_xmax(3.0), roi_ymin(1.0), roi_ymax(4.0);

    OutputData<double> data;
    data.addAxis(FixedBinAxis(BornAgain::PHI_AXIS_NAME, nx, xmin, xmax));
    data.addAxis(FixedBinAxis(BornAgain::ALPHA_AXIS_NAME, ny, ymin, ymax));
    double intensity(10.0);
    data.setAllTo(intensity);

    double weight(0.5);
    FitObject obj(simulation, data, weight);

    EXPECT_EQ(obj.weight(), weight);
    EXPECT_EQ(obj.numberOfFitElements(), size_t(roi_nx*roi_ny));

    EXPECT_EQ(obj.realData().getAxis(0).size(), roi_nx);
    EXPECT_EQ(obj.realData().getAxis(1).size(), roi_ny);
    EXPECT_EQ(obj.realData().getAxis(0).getMin(), roi_xmin);
    EXPECT_EQ(obj.realData().getAxis(0).getMax(), roi_xmax);
    EXPECT_EQ(obj.realData().getAxis(1).getMin(), roi_ymin);
    EXPECT_EQ(obj.realData().getAxis(1).getMax(), roi_ymax);

    EXPECT_EQ(obj.chiSquaredMap().getAxis(0).size(), roi_nx);
    EXPECT_EQ(obj.chiSquaredMap().getAxis(1).size(), roi_ny);
    EXPECT_EQ(obj.chiSquaredMap().getAxis(0).getMin(), roi_xmin);
    EXPECT_EQ(obj.chiSquaredMap().getAxis(0).getMax(), roi_xmax);
    EXPECT_EQ(obj.chiSquaredMap().getAxis(1).getMin(), roi_ymin);
    EXPECT_EQ(obj.chiSquaredMap().getAxis(1).getMax(), roi_ymax);
}

#endif // FITOBJECTTEST_H
