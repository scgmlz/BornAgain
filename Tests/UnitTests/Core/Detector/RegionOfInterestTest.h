#ifndef REGIONOFINTERESTTEST_H
#define REGIONOFINTERESTTEST_H

#include "RegionOfInterest.h"
#include "SphericalDetector.h"
#include "Exceptions.h"
#include <memory>

class RegionOfInterestTest : public ::testing::Test
{
 protected:
    RegionOfInterestTest(){}
    virtual ~RegionOfInterestTest(){}
};

//! Testing region of interest with reasonable area within the detector.

TEST_F(RegionOfInterestTest, constructor)
{
    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("axis0", 8, -3.0, 5.0));
    detector.addAxis(FixedBinAxis("axis1", 4, 0.0, 4.0));

    // creating region of interest
    double xlow(-1.9), ylow(1.1), xup(2.9), yup(2.85);
    RegionOfInterest roi(detector, xlow, ylow, xup, yup);
    EXPECT_EQ(roi.getXlow(), xlow);
    EXPECT_EQ(roi.getYlow(), ylow);
    EXPECT_EQ(roi.getXup(), xup);
    EXPECT_EQ(roi.getYup(), yup);

    // checking total size of the detector and roi in it
    EXPECT_EQ(roi.detectorSize(), 32u);
    EXPECT_EQ(roi.roiSize(), 10u);

    // converting global detector index to local roi index
    EXPECT_EQ(roi.roiIndex(5), 0u);
    EXPECT_EQ(roi.roiIndex(6), 1u);
    EXPECT_EQ(roi.roiIndex(9), 2u);
    EXPECT_EQ(roi.roiIndex(21), 8u);
    EXPECT_EQ(roi.roiIndex(22), 9u);
    EXPECT_THROW(roi.roiIndex(23), Exceptions::RuntimeErrorException);

    // converting local ro index to global detector index
    EXPECT_EQ(roi.detectorIndex(0), 5u);
    EXPECT_EQ(roi.detectorIndex(1), 6u);
    EXPECT_EQ(roi.detectorIndex(2), 9u);
    EXPECT_EQ(roi.detectorIndex(9), 22u);
}


//! Testing region of interest which is larger than the detector.

TEST_F(RegionOfInterestTest, largeArea)
{
    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("axis0", 8, -3.0, 5.0));
    detector.addAxis(FixedBinAxis("axis1", 4, 0.0, 4.0));

    // creating region of interest
    double xlow(-3.9), ylow(-1.1), xup(6.9), yup(5.85);
    RegionOfInterest roi(detector, xlow, ylow, xup, yup);

    // checking total size of the detector and roi in it
    EXPECT_EQ(roi.detectorSize(), 32u);
    EXPECT_EQ(roi.roiSize(), 32u);

    // converting global detector index to local roi index
    EXPECT_EQ(roi.roiIndex(5), 5u);
    EXPECT_EQ(roi.roiIndex(6), 6u);
    EXPECT_EQ(roi.roiIndex(9), 9u);
    EXPECT_EQ(roi.roiIndex(27), 27u);

    // converting local ro index to global detector index
    EXPECT_EQ(roi.detectorIndex(0), 0u);
    EXPECT_EQ(roi.detectorIndex(27), 27u);
}

//! Testing clone

TEST_F(RegionOfInterestTest, clone)
{
    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("axis0", 8, -3.0, 5.0));
    detector.addAxis(FixedBinAxis("axis1", 4, 0.0, 4.0));

    // creating region of interest
    double xlow(-1.9), ylow(1.1), xup(2.9), yup(2.85);
    RegionOfInterest roi(detector, xlow, ylow, xup, yup);

    std::unique_ptr<RegionOfInterest> clone(roi.clone());

    EXPECT_EQ(clone->getXlow(), xlow);
    EXPECT_EQ(clone->getYlow(), ylow);
    EXPECT_EQ(clone->getXup(), xup);
    EXPECT_EQ(clone->getYup(), yup);

    // checking total size of the detector and roi in it
    EXPECT_EQ(clone->detectorSize(), 32u);
    EXPECT_EQ(clone->roiSize(), 10u);

    // converting global detector index to local roi index
    EXPECT_EQ(clone->roiIndex(5), 0u);
    EXPECT_EQ(clone->roiIndex(6), 1u);
    EXPECT_EQ(clone->roiIndex(9), 2u);
    EXPECT_EQ(clone->roiIndex(21), 8u);
    EXPECT_EQ(clone->roiIndex(22), 9u);
    EXPECT_THROW(clone->roiIndex(23), Exceptions::RuntimeErrorException);

    // converting local ro index to global detector index
    EXPECT_EQ(clone->detectorIndex(0), 5u);
    EXPECT_EQ(clone->detectorIndex(1), 6u);
    EXPECT_EQ(clone->detectorIndex(2), 9u);
    EXPECT_EQ(clone->detectorIndex(9), 22u);
}

#endif
