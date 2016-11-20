#ifndef DETECTORMASKTEST_H
#define DETECTORMASKTEST_H

#include "DetectorMask.h"
#include "SphericalDetector.h"
#include "Polygon.h"
#include <memory>

class DetectorMaskTest : public ::testing::Test
{
public:
};


TEST_F(DetectorMaskTest, InitialState)
{
    DetectorMask test;
    EXPECT_FALSE(test.isMasked(0));
    EXPECT_FALSE(test.getMaskData()->isInitialized());
}


//  4.0  -------------------------------------------------------------------------
//       |  5  |  11 |  17 | 23  | 29  | 35  | 41  | 47  | 53  | 59  | 65  | 71  |
//  3.0  -------------------------------------------------------------------------
//       |  4  |  10 |  16 | 22  | 28  | 34  | 40  | 46  | 52  | 58  | 64  | 70  |
//  2.0  -------------------------------------------------------------------------
//       |  3  |  9  |  15 | 21  | 27  | 33  | 39  | 45  | 51  | 57  | 63  | 69  |
//  1.0  -------------------------------------------------------------------------
//       |  2  |  8  |  14 | 20  | 26  | 32  | 38  | 44  | 50  | 56  | 62  | 68  |
//  0.0  -------------------------------------------------------------------------
//       |  1  |  7  |  13 | 19  | 25  | 31  | 37  | 43  | 49  | 55  | 61  | 67  |
// -1.0  -------------------------------------------------------------------------
//       |  0  |  6  |  12 | 18  | 24  | 30  | 36  | 42  | 48  | 54  | 60  | 66  |
// -2.0  -------------------------------------------------------------------------
//     -4.0  -3.0  -2.0  -1.0   0.0   1.0   2.0   3.0   4.0   5.0   6.0   7.0   8.0

TEST_F(DetectorMaskTest, AddMask)
{
    DetectorMask detectorMask;

    std::vector<double> x = {4.0, -4.0, -4.0, 4.0, 4.0};
    std::vector<double> y = {2.0, 2.0, -2.0, -2.0, 2.0};
    Polygon polygon(x, y);

    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("x-axis", 12, -4.0, 8.0));
    detector.addAxis(FixedBinAxis("y-axis", 6, -2.0, 4.0));

    // initializing mask with detector and one shape
    detectorMask.addMask(polygon, true);
    detectorMask.initMaskData(detector);

    EXPECT_TRUE(detectorMask.getMaskData()->isInitialized());

    for(size_t index=0; index<detectorMask.getMaskData()->getAllocatedSize(); ++index) {
        double x = detectorMask.getMaskData()->getAxisValue(index, 0);
        double y = detectorMask.getMaskData()->getAxisValue(index, 1);
        if( x>= -4.0 && x <=4.0 && y>=-2.0 && y<=2.0) {
            EXPECT_TRUE(detectorMask.isMasked(index));
        } else {
            EXPECT_FALSE(detectorMask.isMasked(index));
        }
    }

    EXPECT_EQ(detectorMask.numberOfMaskedChannels(), 32);

    // adding second mask of same size which discard previous one
    detectorMask.addMask(polygon, false);
    detectorMask.initMaskData(detector);

    for(size_t index=0; index<detectorMask.getMaskData()->getAllocatedSize(); ++index) {
        EXPECT_FALSE(detectorMask.isMasked(index));
    }
    EXPECT_EQ(detectorMask.numberOfMaskedChannels(), 0);

    // adding third mask
    x = {5.0, 5.0, 8.0, 8.0, 5.0};
    y = {2.0, 4.0, 4.0, 2.0, 2.0};
    Polygon polygon2(x, y);
    detectorMask.addMask(polygon2, true);
    detectorMask.initMaskData(detector);
    for(size_t index=0; index<detectorMask.getMaskData()->getAllocatedSize(); ++index) {
        double x = detectorMask.getMaskData()->getAxisValue(index, 0);
        double y = detectorMask.getMaskData()->getAxisValue(index, 1);
        if( x>= 5.0 && x <=8.0 && y>=2.0 && y<=4.0) {
            EXPECT_TRUE(detectorMask.isMasked(index));
        } else {
            EXPECT_FALSE(detectorMask.isMasked(index));
        }
    }

    // clearing all masks
    detectorMask.removeMasks();
    detectorMask.initMaskData(detector);
    for(size_t index=0; index<detectorMask.getMaskData()->getAllocatedSize(); ++index) {
        EXPECT_FALSE(detectorMask.isMasked(index));
    }

}


TEST_F(DetectorMaskTest, AssignmentOperator)
{
    DetectorMask detectorMask;

    std::vector<double> x = {4.0, -4.0, -4.0, 4.0, 4.0};
    std::vector<double> y = {2.0, 2.0, -2.0, -2.0, 2.0};
    Polygon polygon(x, y);

    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("x-axis", 12, -4.0, 8.0));
    detector.addAxis(FixedBinAxis("y-axis", 6, -2.0, 4.0));

    // initializing mask with detector and one shape
    detectorMask.addMask(polygon, true);
    detectorMask.initMaskData(detector);

    DetectorMask mask = detectorMask;

    EXPECT_TRUE(mask.getMaskData()->isInitialized());

    for(size_t index=0; index<mask.getMaskData()->getAllocatedSize(); ++index) {
        double x = mask.getMaskData()->getAxisValue(index, 0);
        double y = mask.getMaskData()->getAxisValue(index, 1);
        if( x>= -4.0 && x <=4.0 && y>=-2.0 && y<=2.0) {
            EXPECT_TRUE(mask.isMasked(index));
        } else {
            EXPECT_FALSE(mask.isMasked(index));
        }
    }
    EXPECT_EQ(mask.numberOfMaskedChannels(), 32);

}


TEST_F(DetectorMaskTest, CopyConstructor)
{
    DetectorMask detectorMask;

    std::vector<double> x = {4.0, -4.0, -4.0, 4.0, 4.0};
    std::vector<double> y = {2.0, 2.0, -2.0, -2.0, 2.0};
    Polygon polygon(x, y);

    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("x-axis", 12, -4.0, 8.0));
    detector.addAxis(FixedBinAxis("y-axis", 6, -2.0, 4.0));

    // initializing mask with detector and one shape
    detectorMask.addMask(polygon, true);
    detectorMask.initMaskData(detector);

    DetectorMask mask(detectorMask);

    EXPECT_TRUE(mask.getMaskData()->isInitialized());

    for(size_t index=0; index<mask.getMaskData()->getAllocatedSize(); ++index) {
        double x = mask.getMaskData()->getAxisValue(index, 0);
        double y = mask.getMaskData()->getAxisValue(index, 1);
        if( x>= -4.0 && x <=4.0 && y>=-2.0 && y<=2.0) {
            EXPECT_TRUE(mask.isMasked(index));
        } else {
            EXPECT_FALSE(mask.isMasked(index));
        }
    }
}


#endif // DETECTORMASKTEST_H
