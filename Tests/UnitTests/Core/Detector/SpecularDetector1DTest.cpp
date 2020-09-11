#include "Core/Detector/SpecularDetector1D.h"
#include "Core/Basics/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Detector/SimulationArea.h"
#include "Core/Intensity/OutputData.h"
#include "Tests/GTestWrapper/google_test.h"
#include <memory>

class SpecularDetectorTest : public ::testing::Test
{
};

// Default detector construction
TEST_F(SpecularDetectorTest, basicBehaviour)
{
    FixedBinAxis axis("axis0", 10, 0.0, 10.0);
    SpecularDetector1D detector(axis);

    // masks, regions of interest, detector resolution
    EXPECT_EQ(nullptr, detector.detectorMask());
    EXPECT_EQ(nullptr, detector.regionOfInterest());
    EXPECT_EQ(nullptr, detector.detectorResolution());

    // checking size and axis
    EXPECT_EQ(1u, detector.dimension());
    EXPECT_EQ(axis.getMin(), detector.getAxis(0).getMin());
    EXPECT_EQ(axis.getMax(), detector.getAxis(0).getMax());

    // throwing exceptions
    OutputData<double>* p_intensity_map(nullptr);
    ASSERT_THROW(detector.applyDetectorResolution(p_intensity_map), std::runtime_error);

    // clearing detector
    detector.clear();
    EXPECT_EQ(0u, detector.dimension());
    ASSERT_THROW(detector.getAxis(0), std::runtime_error);
}

// Creation of the detector map with axes in given units
TEST_F(SpecularDetectorTest, createDetectorMap)
{
    FixedBinAxis axis("axis0", 10, 1.0 * Units::deg, 10.0 * Units::deg);
    SpecularDetector1D detector(axis);

    // creating map in default units, which are radians and checking axes
    auto data = detector.createDetectorMap();
    EXPECT_EQ(data->getAxis(0).size(), 10u);
    EXPECT_EQ(data->getAxis(0).getMin(), 1.0 * Units::deg);
    EXPECT_EQ(data->getAxis(0).getMax(), 10.0 * Units::deg);
}

TEST_F(SpecularDetectorTest, Clone)
{
    FixedBinAxis axis("axis0", 5, 1.0 * Units::deg, 10.0 * Units::deg);
    SpecularDetector1D detector(axis);
    std::unique_ptr<SpecularDetector1D> clone(detector.clone());

    const auto data = clone->createDetectorMap();
    EXPECT_EQ(data->getAxis(0).size(), 5u);
    EXPECT_EQ(data->getAxis(0).getMin(), 1.0 * Units::deg);
    EXPECT_EQ(data->getAxis(0).getMax(), 10.0 * Units::deg);

    EXPECT_EQ(nullptr, clone->detectorResolution());
    EXPECT_EQ(nullptr, clone->detectorMask());

    // checking iteration over the map of cloned detector
    SimulationArea area(clone.get());
    const std::vector<size_t> expectedDetectorIndexes = {0, 1, 2, 3, 4};
    const std::vector<size_t> expectedElementIndexes = expectedDetectorIndexes;
    std::vector<size_t> detectorIndexes;
    std::vector<size_t> elementIndexes;
    for (SimulationArea::iterator it = area.begin(); it != area.end(); ++it) {
        detectorIndexes.push_back(it.detectorIndex());
        elementIndexes.push_back(it.elementIndex());
    }
    EXPECT_EQ(detectorIndexes, expectedDetectorIndexes);
    EXPECT_EQ(elementIndexes, expectedElementIndexes);
}
