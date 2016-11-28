#ifndef SIMULATIONAREATEST_H
#define SIMULATIONAREATEST_H

#include "SimulationArea.h"
#include "SphericalDetector.h"
#include "Rectangle.h"
#include <memory>
#include <iostream>

class SimulationAreaTest : public ::testing::Test
{
 protected:
    SimulationAreaTest(){}
    virtual ~SimulationAreaTest(){}
};

// Iterators test

TEST_F(SimulationAreaTest, iteratorOperations)
{
    SphericalDetector detector(4, -1.0, 3.0, 2, 0.0, 2.0);
    SimulationArea area(&detector);

    // begin iterator
    SimulationArea::iterator it_begin = area.begin();
    EXPECT_EQ(it_begin.index(), 0u);
    EXPECT_EQ(it_begin.elementIndex(), 0u);
    EXPECT_TRUE(it_begin == area.begin());
    EXPECT_FALSE(it_begin != area.begin());

    // end iterator
    SimulationArea::iterator it_end = area.end();
    EXPECT_EQ(it_end.index(), detector.getTotalSize());
    EXPECT_EQ(it_end.elementIndex(), 0u); // has initial value

    // begin/end comparison
    EXPECT_TRUE(it_begin != it_end);
    EXPECT_FALSE(it_begin == it_end);

    // assignment
    SimulationArea::iterator it = area.begin();
    EXPECT_TRUE(it == it_begin);
    EXPECT_FALSE(it != it_begin);

    // increment
    it++;
    EXPECT_EQ(it.index(), 1u);
    EXPECT_EQ(it.elementIndex(), 1u);
    EXPECT_TRUE(it != it_begin);
    EXPECT_FALSE(it == it_begin);
    ++it;
    EXPECT_EQ(it.index(), 2u);
    EXPECT_EQ(it.elementIndex(), 2u);

    // incrementing well behind the end
    for(size_t i=0; i<100; ++i) ++it;
    EXPECT_EQ(it.index(), detector.getTotalSize());
    EXPECT_EQ(it.elementIndex(), detector.getTotalSize());
}

//! Iteration over non-masked detector

TEST_F(SimulationAreaTest, detectorIteration)
{
    SphericalDetector detector(4, -1.0, 3.0, 2, 0.0, 2.0);
    SimulationArea area(&detector);

    std::vector<int> expectedIndexes = {0, 1, 2, 3, 4, 5, 6, 7};
    std::vector<int> expectedElementIndexes = {0, 1, 2, 3, 4, 5, 6, 7};

    std::vector<int> indexes;
    std::vector<int> elementIndexes;
    std::vector<int> detectorIndexes;
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        indexes.push_back(it.index());
        elementIndexes.push_back(it.elementIndex());
        detectorIndexes.push_back(it.detectorIndex());
    }
    EXPECT_EQ(indexes, expectedIndexes);
    EXPECT_EQ(elementIndexes, expectedElementIndexes);
    EXPECT_EQ(detectorIndexes, expectedIndexes);
}

//! Iteration over masked detector

TEST_F(SimulationAreaTest, maskedIteration)
{
    SphericalDetector detector(5, -1.0, 4.0, 4, 0.0, 4.0);
    detector.addMask(Rectangle(0.1, 1.1, 2.9, 2.9), true);
    detector.addMask(Rectangle(3.1, 3.1, 3.9, 3.9), true);
    SimulationArea area(&detector);

    std::vector<int> expectedIndexes = {0, 1, 2, 3, 4, 7, 8, 11, 12, 15, 16, 17, 18};
    std::vector<int> expectedElementIndexes = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::vector<int> indexes;
    std::vector<int> elementIndexes;
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        indexes.push_back(it.index());
        elementIndexes.push_back(it.elementIndex());
    }
    EXPECT_EQ(indexes, expectedIndexes);
    EXPECT_EQ(elementIndexes, expectedElementIndexes);
}

//! Iteration over the detector with first and alst bin masked

TEST_F(SimulationAreaTest, maskedCornerIteration)
{
    SphericalDetector detector(5, -1.0, 4.0, 4, 0.0, 4.0);
    detector.addMask(Rectangle(-0.9, 0.1, -0.1, 0.9), true);
    detector.addMask(Rectangle(3.1, 3.1, 3.9, 3.9), true);
    SimulationArea area(&detector);

    std::vector<int> expectedIndexes
            = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    std::vector<int> expectedElementIndexes
            = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
    std::vector<int> indexes;
    std::vector<int> elementIndexes;
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        indexes.push_back(it.index());
        elementIndexes.push_back(it.elementIndex());
    }
    EXPECT_EQ(indexes, expectedIndexes);
    EXPECT_EQ(elementIndexes, expectedElementIndexes);
}

//! Iteration when whole detector is masked

TEST_F(SimulationAreaTest, allMaskedIteration)
{
    SphericalDetector detector(5, -1.0, 4.0, 4, 0.0, 4.0);
    detector.addMask(Rectangle(-0.9, 0.1, 3.9, 3.9), true);
    SimulationArea area(&detector);

    std::vector<int> indexes;
    std::vector<int> elementIndexes;
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        indexes.push_back(it.index());
        elementIndexes.push_back(it.elementIndex());
    }
    EXPECT_EQ(indexes.size(), size_t(0));
    EXPECT_EQ(elementIndexes.size(), size_t(0));
}

//! Iteration when RegionOfInterest is present

TEST_F(SimulationAreaTest, maskAndRoiIteration)
{
    SphericalDetector detector(5, -1.0, 4.0, 4, 0.0, 4.0);
    detector.setRegionOfInterest(0.1, 1.1, 2.9, 3.9);
    detector.addMask(Rectangle(-0.9, 0.1, 0.9, 1.9), true);
    SimulationArea area(&detector);

    std::vector<int> expectedRoiIndexes = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> expectedDetectorIndexes = {6, 7, 9, 10, 11, 13, 14, 15};
    std::vector<int> expectedElementIndexes = {0, 1, 2, 3, 4, 5, 6, 7};
    std::vector<int> indexes;
    std::vector<int> elementIndexes;
    std::vector<int> detectorIndexes;
    std::vector<int> roiIndexes;
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        indexes.push_back(it.index());
        elementIndexes.push_back(it.elementIndex());
        detectorIndexes.push_back(it.detectorIndex());
        roiIndexes.push_back(it.roiIndex());
    }
    EXPECT_EQ(indexes, expectedRoiIndexes);
    EXPECT_EQ(elementIndexes, expectedElementIndexes);
    EXPECT_EQ(detectorIndexes, expectedDetectorIndexes);
    EXPECT_EQ(roiIndexes, expectedRoiIndexes);
}

//! Checking index of ROI

TEST_F(SimulationAreaTest, indexInRoi)
{
    SphericalDetector detector(5, -1.0, 4.0, 4, 0.0, 4.0);
    detector.setRegionOfInterest(0.1, 1.1, 2.9, 3.9);
    detector.addMask(Rectangle(-0.9, 0.1, 0.9, 1.9), true);
    SimulationArea area(&detector);

    std::vector<int> expectedIndexes = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> expectedDetectorIndexes = {6, 7, 9, 10, 11, 13, 14, 15};
    std::vector<int> expectedElementIndexes = {0, 1, 2, 3, 4, 5, 6, 7};
    std::vector<int> expectedRoi = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> indexes;
    std::vector<int> elementIndexes;
    std::vector<int> roiIndexes;
    std::vector<int> detectorIndexes;
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        indexes.push_back(it.index());
        elementIndexes.push_back(it.elementIndex());
        roiIndexes.push_back(it.roiIndex());
        detectorIndexes.push_back(it.detectorIndex());
    }
    EXPECT_EQ(indexes, expectedIndexes);
    EXPECT_EQ(elementIndexes, expectedElementIndexes);
    EXPECT_EQ(roiIndexes, expectedRoi);
    EXPECT_EQ(detectorIndexes, expectedDetectorIndexes);
}

#endif
