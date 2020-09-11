#include "Core/Detector/SphericalDetector.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Detector/ConvolutionDetectorResolution.h"
#include "Core/Detector/DetectorFunctions.h"
#include "Core/Detector/RegionOfInterest.h"
#include "Core/Detector/ResolutionFunction2DGaussian.h"
#include "Core/Detector/SimulationArea.h"
#include "Core/Intensity/OutputData.h"
#include "Core/Mask/Polygon.h"
#include "Core/Mask/Rectangle.h"
#include "Tests/GTestWrapper/google_test.h"
#include <memory>

class SphericalDetectorTest : public ::testing::Test
{
};

// Default detector construction
TEST_F(SphericalDetectorTest, initialState)
{
    SphericalDetector detector;

    // checking size
    EXPECT_EQ(0u, detector.dimension());
    EXPECT_EQ(AxesUnits::RADIANS, detector.defaultAxesUnits());

    // masks
    EXPECT_FALSE(detector.detectorMask()->hasMasks());
    EXPECT_EQ(0, detector.detectorMask()->numberOfMaskedChannels());

    // resolution function
    EXPECT_EQ(nullptr, detector.detectorResolution());

    // region of interest
    EXPECT_EQ(nullptr, detector.regionOfInterest());

    // behavior
    ASSERT_THROW(detector.getAxis(0), std::runtime_error);
    OutputData<double>* p_intensity_map(nullptr);
    ASSERT_THROW(detector.applyDetectorResolution(p_intensity_map), std::runtime_error);
}

// Construction of the detector with axes.
TEST_F(SphericalDetectorTest, constructionWithAxes)
{
    SphericalDetector detector;
    FixedBinAxis axis0("axis0", 10, 0.0, 10.0);
    FixedBinAxis axis1("axis1", 20, 0.0, 20.0);
    detector.addAxis(axis0);
    detector.addAxis(axis1);

    // checking dimension and axes
    EXPECT_EQ(2u, detector.dimension());
    EXPECT_EQ(axis0.getMin(), detector.getAxis(0).getMin());
    EXPECT_EQ(axis0.getMax(), detector.getAxis(0).getMax());
    EXPECT_EQ(axis1.getMin(), detector.getAxis(1).getMin());
    EXPECT_EQ(axis1.getMax(), detector.getAxis(1).getMax());

    // clearing detector
    detector.clear();
    EXPECT_EQ(0u, detector.dimension());
}

// Construction of the detector via classical constructor.
TEST_F(SphericalDetectorTest, constructionWithParameters)
{
    SphericalDetector detector(10, -1.0, 1.0, 20, 0.0, 2.0);
    EXPECT_EQ(10u, detector.getAxis(0).size());
    EXPECT_EQ(-1.0, detector.getAxis(0).getMin());
    EXPECT_EQ(1.0, detector.getAxis(0).getMax());
    EXPECT_EQ(20u, detector.getAxis(1).size());
    EXPECT_EQ(0.0, detector.getAxis(1).getMin());
    EXPECT_EQ(2.0, detector.getAxis(1).getMax());
}

// Creation of the detector map with axes in given units
TEST_F(SphericalDetectorTest, createDetectorMap)
{
    SphericalDetector detector(10, -1.0 * Units::deg, 1.0 * Units::deg, 20, 0.0 * Units::deg,
                               2.0 * Units::deg);

    // creating map in default units, which are radians and checking axes
    auto data = detector.createDetectorMap();
    EXPECT_EQ(data->getAxis(0).size(), 10u);
    EXPECT_EQ(data->getAxis(0).getMin(), -1.0 * Units::deg);
    EXPECT_EQ(data->getAxis(0).getMax(), 1.0 * Units::deg);
    EXPECT_EQ(data->getAxis(1).size(), 20u);
    EXPECT_EQ(data->getAxis(1).getMin(), 0.0 * Units::deg);
    EXPECT_EQ(data->getAxis(1).getMax(), 2.0 * Units::deg);
}

// Testing region of interest.
TEST_F(SphericalDetectorTest, regionOfInterest)
{
    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("axis0", 8, -3.0, 5.0));
    detector.addAxis(FixedBinAxis("axis1", 4, 0.0, 4.0));

    // creating region of interest
    double xlow(-2.0), ylow(1.0), xup(4.0), yup(3.0);
    detector.setRegionOfInterest(xlow, ylow, xup, yup);
    EXPECT_FALSE(nullptr == detector.regionOfInterest());
    EXPECT_EQ(detector.regionOfInterest()->getXlow(), xlow);
    EXPECT_EQ(detector.regionOfInterest()->getYlow(), ylow);
    EXPECT_EQ(detector.regionOfInterest()->getXup(), xup);
    EXPECT_EQ(detector.regionOfInterest()->getYup(), yup);

    // replacing region of interest with a new one
    double xlow2(-2.1), ylow2(1.1), xup2(4.1), yup2(3.1);
    detector.setRegionOfInterest(xlow2, ylow2, xup2, yup2);
    EXPECT_EQ(detector.regionOfInterest()->getXlow(), xlow2);
    EXPECT_EQ(detector.regionOfInterest()->getYlow(), ylow2);
    EXPECT_EQ(detector.regionOfInterest()->getXup(), xup2);
    EXPECT_EQ(detector.regionOfInterest()->getYup(), yup2);

    // removing region of interest
    detector.resetRegionOfInterest();
    EXPECT_TRUE(nullptr == detector.regionOfInterest());
}

// Create detector map in the presence of region of interest.
TEST_F(SphericalDetectorTest, regionOfInterestAndDetectorMap)
{
    SphericalDetector detector(6, -1.0 * Units::deg, 5.0 * Units::deg, 4, 0.0 * Units::deg,
                               4.0 * Units::deg);

    detector.setRegionOfInterest(0.1 * Units::deg, 1.1 * Units::deg, 3.0 * Units::deg,
                                 2.9 * Units::deg);
    // Creating map in default units, which are radians and checking that axes are clipped
    // to region of interest.
    auto data = detector.createDetectorMap();
    EXPECT_EQ(data->getAxis(0).size(), 4u);
    EXPECT_EQ(data->getAxis(0).getMin(), 0.0 * Units::deg);
    EXPECT_EQ(data->getAxis(0).getMax(), 4.0 * Units::deg);
    EXPECT_EQ(data->getAxis(1).size(), 2u);
    EXPECT_EQ(data->getAxis(1).getMin(), 1.0 * Units::deg);
    EXPECT_EQ(data->getAxis(1).getMax(), 3.0 * Units::deg);
}

TEST_F(SphericalDetectorTest, MaskOfDetector)
{
    SphericalDetector detector;
    detector.addAxis(FixedBinAxis("x-axis", 12, -4.0, 8.0));
    detector.addAxis(FixedBinAxis("y-axis", 6, -2.0, 4.0));

    std::vector<double> x = {4.0, -4.0, -4.0, 4.0, 4.0};
    std::vector<double> y = {2.0, 2.0, -2.0, -2.0, 2.0};

    Polygon polygon(x, y);
    detector.addMask(polygon, true);

    const OutputData<bool>* mask = detector.detectorMask()->getMaskData();
    for (size_t index = 0; index < mask->getAllocatedSize(); ++index) {
        double x = mask->getAxisValue(index, 0);
        double y = mask->getAxisValue(index, 1);
        if (x >= -4.0 && x <= 4.0 && y >= -2.0 && y <= 2.0) {
            EXPECT_TRUE(detector.detectorMask()->isMasked(index));
        } else {
            EXPECT_FALSE(detector.detectorMask()->isMasked(index));
        }
    }

    SphericalDetector detector2(detector);
    mask = detector2.detectorMask()->getMaskData();
    for (size_t index = 0; index < mask->getAllocatedSize(); ++index) {
        double x = mask->getAxisValue(index, 0);
        double y = mask->getAxisValue(index, 1);
        if (x >= -4.0 && x <= 4.0 && y >= -2.0 && y <= 2.0) {
            EXPECT_TRUE(detector2.detectorMask()->isMasked(index));
        } else {
            EXPECT_FALSE(detector2.detectorMask()->isMasked(index));
        }
    }

    mask = detector.detectorMask()->getMaskData();
    for (size_t index = 0; index < mask->getAllocatedSize(); ++index) {
        double x = mask->getAxisValue(index, 0);
        double y = mask->getAxisValue(index, 1);
        if (x >= -4.0 && x <= 4.0 && y >= -2.0 && y <= 2.0) {
            EXPECT_TRUE(detector.detectorMask()->isMasked(index));
        } else {
            EXPECT_FALSE(detector.detectorMask()->isMasked(index));
        }
    }
}

// Checking clone in the presence of ROI and masks.
TEST_F(SphericalDetectorTest, Clone)
{
    SphericalDetector detector(6, -1.0 * Units::deg, 5.0 * Units::deg, 4, 0.0 * Units::deg,
                               4.0 * Units::deg);
    detector.setRegionOfInterest(0.1 * Units::deg, 1.1 * Units::deg, 3.0 * Units::deg,
                                 2.9 * Units::deg);
    detector.addMask(
        Rectangle(-0.9 * Units::deg, 0.1 * Units::deg, 0.9 * Units::deg, 1.9 * Units::deg), true);
    detector.addMask(
        Rectangle(3.1 * Units::deg, 2.1 * Units::deg, 4.9 * Units::deg, 3.9 * Units::deg), true);
    detector.setDetectorResolution(
        ConvolutionDetectorResolution(ResolutionFunction2DGaussian(1, 1)));

    std::unique_ptr<SphericalDetector> clone(detector.clone());

    auto data = clone->createDetectorMap();
    EXPECT_EQ(data->getAxis(0).size(), 4u);
    EXPECT_EQ(data->getAxis(0).getMin(), 0.0 * Units::deg);
    EXPECT_EQ(data->getAxis(0).getMax(), 4.0 * Units::deg);
    EXPECT_EQ(data->getAxis(1).size(), 2u);
    EXPECT_EQ(data->getAxis(1).getMin(), 1.0 * Units::deg);
    EXPECT_EQ(data->getAxis(1).getMax(), 3.0 * Units::deg);

    EXPECT_EQ(clone->detectorMask()->numberOfMaskedChannels(), 8);

    // checking iteration over the map of cloned detector
    SimulationArea area(clone.get());
    std::vector<size_t> expectedDetectorIndexes = {6, 9, 10, 13, 14, 17};
    std::vector<size_t> expectedElementIndexes = {0, 1, 2, 3, 4, 5};
    std::vector<size_t> detectorIndexes;
    std::vector<size_t> elementIndexes;
    for (SimulationArea::iterator it = area.begin(); it != area.end(); ++it) {
        detectorIndexes.push_back(it.detectorIndex());
        elementIndexes.push_back(it.elementIndex());
    }
    EXPECT_EQ(detectorIndexes, expectedDetectorIndexes);
    EXPECT_EQ(elementIndexes, expectedElementIndexes);
}

// Test retrieval of analyzer properties
TEST_F(SphericalDetectorTest, AnalyzerProperties)
{
    SphericalDetector detector(6, -1.0 * Units::deg, 5.0 * Units::deg, 4, 0.0 * Units::deg,
                               4.0 * Units::deg);

    kvector_t direction;
    double efficiency = 0.0;
    double total_transmission = 1.0;
    kvector_t unit_direction;

    // if direction is the zero vector, an exception is thrown
    EXPECT_THROW(detector.setAnalyzerProperties(direction, efficiency, total_transmission),
                 Exceptions::ClassInitializationException);

    // zero efficiency
    direction = kvector_t(1.0, 0.0, 0.0);
    unit_direction = direction.unit();
    detector.setAnalyzerProperties(direction, efficiency, total_transmission);
    const DetectionProperties& detect_properties = detector.detectionProperties();

    EXPECT_NEAR(detect_properties.analyzerEfficiency(), efficiency, 1e-8);
    EXPECT_NEAR(detect_properties.analyzerTotalTransmission(), total_transmission, 1e-8);
    // direction vector returned is zero vector because efficiency is zero
    EXPECT_NEAR(detect_properties.analyzerDirection().x(), 0.0, 1e-8);
    EXPECT_NEAR(detect_properties.analyzerDirection().y(), 0.0, 1e-8);
    EXPECT_NEAR(detect_properties.analyzerDirection().z(), 0.0, 1e-8);

    // intermediate efficiency
    direction = kvector_t(1.0, 0.0, 0.0);
    efficiency = 0.5;
    total_transmission = 0.6;
    unit_direction = direction.unit();
    detector.setAnalyzerProperties(direction, efficiency, total_transmission);
    const DetectionProperties& detect_properties2 = detector.detectionProperties();

    EXPECT_NEAR(detect_properties2.analyzerEfficiency(), efficiency, 1e-8);
    EXPECT_NEAR(detect_properties2.analyzerTotalTransmission(), total_transmission, 1e-8);
    EXPECT_NEAR(detect_properties2.analyzerDirection().x(), unit_direction.x(), 1e-8);
    EXPECT_NEAR(detect_properties2.analyzerDirection().y(), unit_direction.y(), 1e-8);
    EXPECT_NEAR(detect_properties2.analyzerDirection().z(), unit_direction.z(), 1e-8);

    // maximum efficiency
    direction = kvector_t(1.0, 0.0, 0.0);
    efficiency = 1.0;
    total_transmission = 0.5;
    unit_direction = direction.unit();
    detector.setAnalyzerProperties(direction, efficiency, total_transmission);
    const DetectionProperties& detect_properties3 = detector.detectionProperties();

    EXPECT_NEAR(detect_properties3.analyzerEfficiency(), efficiency, 1e-8);
    EXPECT_NEAR(detect_properties3.analyzerTotalTransmission(), total_transmission, 1e-8);
    EXPECT_NEAR(detect_properties3.analyzerDirection().x(), unit_direction.x(), 1e-8);
    EXPECT_NEAR(detect_properties3.analyzerDirection().y(), unit_direction.y(), 1e-8);
    EXPECT_NEAR(detect_properties3.analyzerDirection().z(), unit_direction.z(), 1e-8);

    // non-axis direction
    direction = kvector_t(1.0, 2.0, 3.0);
    efficiency = 1.0;
    total_transmission = 0.5;
    unit_direction = direction.unit();
    detector.setAnalyzerProperties(direction, efficiency, total_transmission);
    const DetectionProperties& detect_properties4 = detector.detectionProperties();

    EXPECT_NEAR(detect_properties4.analyzerEfficiency(), efficiency, 1e-8);
    EXPECT_NEAR(detect_properties4.analyzerTotalTransmission(), total_transmission, 1e-8);
    EXPECT_NEAR(detect_properties4.analyzerDirection().x(), unit_direction.x(), 1e-8);
    EXPECT_NEAR(detect_properties4.analyzerDirection().y(), unit_direction.y(), 1e-8);
    EXPECT_NEAR(detect_properties4.analyzerDirection().z(), unit_direction.z(), 1e-8);

    // maximum efficiency and negative efficiency
    direction = kvector_t(0.0, -1.0, -1.0);
    efficiency = -1.0;
    total_transmission = 0.5;
    unit_direction = direction.unit();
    detector.setAnalyzerProperties(direction, efficiency, total_transmission);
    const DetectionProperties& detect_properties5 = detector.detectionProperties();

    EXPECT_NEAR(detect_properties5.analyzerEfficiency(), efficiency, 1e-8);
    EXPECT_NEAR(detect_properties5.analyzerTotalTransmission(), total_transmission, 1e-8);
    EXPECT_NEAR(detect_properties5.analyzerDirection().x(), unit_direction.x(), 1e-8);
    EXPECT_NEAR(detect_properties5.analyzerDirection().y(), unit_direction.y(), 1e-8);
    EXPECT_NEAR(detect_properties5.analyzerDirection().z(), unit_direction.z(), 1e-8);
}
