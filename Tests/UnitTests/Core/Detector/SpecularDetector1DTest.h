#include "Beam.h"
#include "BornAgainNamespace.h"
#include "FixedBinAxis.h"
#include "OutputData.h"
#include "SimulationArea.h"
#include "SimulationElement.h"
#include "SimulationElementsProvider.h"
#include "SpecularDetector1D.h"
#include "Units.h"
#include "google_test.h"
#include <memory>

class SpecularDetectorTest : public ::testing::Test
{
protected:
    ~SpecularDetectorTest();

    std::vector<SimulationElement>
    extractSimulationElements(std::unique_ptr<ISimulationElementsProvider> agent_base)
    {
        auto agent
            = dynamic_cast<SimulationElementsProvider<SimulationElement>*>(agent_base.get());
        std::vector<SimulationElement> result;
        if (agent)
            result = agent->releaseSimElements();
        return result;
    }
};

SpecularDetectorTest::~SpecularDetectorTest() = default;

// Default detector construction
TEST_F(SpecularDetectorTest, basicBehaviour)
{
    FixedBinAxis axis("axis0", 10, 0.0, 10.0);
    SpecularDetector1D detector(axis);

    // detector units
    EXPECT_EQ(AxesUnits::RADIANS, detector.defaultAxesUnits());
    std::vector<AxesUnits> validUnits = {AxesUnits::NBINS, AxesUnits::RADIANS, AxesUnits::DEGREES};
    EXPECT_EQ(validUnits, detector.validAxesUnits());

    // masks, regions of interest, detector resolution
    EXPECT_EQ(nullptr, detector.detectorMask());
    EXPECT_EQ(nullptr, detector.regionOfInterest());
    EXPECT_EQ(nullptr, detector.detectorResolution());

    // checking size and axis
    EXPECT_EQ(1u, detector.dimension());
    EXPECT_EQ(axis.getMin(), detector.getAxis(0).getMin());
    EXPECT_EQ(axis.getMax(), detector.getAxis(0).getMax());
    EXPECT_EQ(axis.getName(), detector.getAxis(0).getName());

    // throwing exceptions
    OutputData<double>* p_intensity_map(nullptr);
    ASSERT_THROW(detector.applyDetectorResolution(p_intensity_map), std::runtime_error);

    // clearing detector
    detector.clear();
    EXPECT_EQ(0u, detector.dimension());
    ASSERT_THROW(detector.getAxis(0), std::runtime_error);
}

// Init external data with detector axes.
TEST_F(SpecularDetectorTest, initOutputData)
{
    FixedBinAxis axis("axis0", 10, 0.0, 10.0);
    SpecularDetector1D detector(axis);
    OutputData<double> data;
    detector.initOutputData(data);

    EXPECT_EQ(data.getAllocatedSize(), 10u);

    EXPECT_EQ(10u, data.getAxis(0).size());
    EXPECT_EQ(0.0, data.getAxis(0).getMin());
    EXPECT_EQ(10.0, data.getAxis(0).getMax());
    EXPECT_EQ(axis.getName(), data.getAxis(0).getName());

    EXPECT_EQ(1u, data.getRank());
}

// Creation of the detector map with axes in given units
TEST_F(SpecularDetectorTest, createDetectorMap)
{
    FixedBinAxis axis("axis0", 10, 1.0 * Units::deg, 10.0 * Units::deg);
    SpecularDetector1D detector(axis);

    Beam beam;
    beam.setCentralK(1.0 * Units::angstrom, 1.0 * Units::deg, 0.0);

    // creating map in default units, which are radians and checking axes
    auto data = detector.createDetectorMap(beam, AxesUnits::DEFAULT);
    EXPECT_EQ(data->getAxis(0).size(), 10u);
    EXPECT_EQ(data->getAxis(0).getMin(), 1.0 * Units::deg);
    EXPECT_EQ(data->getAxis(0).getMax(), 10.0 * Units::deg);

    // explicitly creating map in radians and checking axes
    data = detector.createDetectorMap(beam, AxesUnits::RADIANS);
    EXPECT_EQ(data->getAxis(0).size(), 10u);
    EXPECT_EQ(data->getAxis(0).getMin(), 1.0 * Units::deg);
    EXPECT_EQ(data->getAxis(0).getMax(), 10.0 * Units::deg);

    // creating map in degrees and checking axes
    data = detector.createDetectorMap(beam, AxesUnits::DEGREES);
    EXPECT_EQ(data->getAxis(0).size(), 10u);
    EXPECT_DOUBLE_EQ(data->getAxis(0).getMin(), 1.0);
    EXPECT_DOUBLE_EQ(data->getAxis(0).getMax(), 10.0);

    // creating map in nbins and checking axes
    data = detector.createDetectorMap(beam, AxesUnits::NBINS);
    EXPECT_EQ(data->getAxis(0).size(), 10u);
    EXPECT_DOUBLE_EQ(data->getAxis(0).getMin(), 0.0);
    EXPECT_DOUBLE_EQ(data->getAxis(0).getMax(), 10.0);

    // wrong units in input
    EXPECT_THROW(detector.createDetectorMap(beam, AxesUnits::QYQZ), std::runtime_error);
}

TEST_F(SpecularDetectorTest, SimulationElements)
{
    FixedBinAxis axis("axis0", 5, 1.0 * Units::deg, 10.0 * Units::deg);
    SpecularDetector1D detector(axis);
    Beam beam;
    beam.setCentralK(1.0 * Units::angstrom, 0.4 * Units::deg, 0.0);

    auto sim_elements = extractSimulationElements(detector.createSimulationElements(beam));

    EXPECT_EQ(5u, sim_elements.size());

    EXPECT_NEAR(axis.getBinCenter(0), -sim_elements[0].getAlphaI(), 1e-10);
    EXPECT_NEAR(0.0, sim_elements[0].getPhiI(), 1e-10);
    EXPECT_NEAR(beam.getWavelength(), sim_elements[0].getWavelength(), 1e-10);
    EXPECT_NEAR(axis.getBinCenter(0), sim_elements[0].getAlphaMean(), 1e-10);
    EXPECT_NEAR(0.0, sim_elements[0].getPhiMean(), 1e-10);
    EXPECT_EQ(sim_elements[0].getAlphaMean(), sim_elements[0].getAlpha(0, 0));
    EXPECT_EQ(sim_elements[0].getAlphaMean(), sim_elements[0].getAlpha(1, 1));

    EXPECT_NEAR(axis.getBinCenter(4), -sim_elements[4].getAlphaI(), 1e-10);
    EXPECT_NEAR(0.0, sim_elements[4].getPhiI(), 1e-10);
    EXPECT_NEAR(beam.getWavelength(), sim_elements[4].getWavelength(), 1e-10);
    EXPECT_NEAR(axis.getBinCenter(4), sim_elements[4].getAlphaMean(), 1e-10);
    EXPECT_NEAR(0.0, sim_elements[4].getPhiMean(), 1e-10);
    EXPECT_EQ(sim_elements[4].getAlphaMean(), sim_elements[4].getAlpha(0, 0));
    EXPECT_EQ(sim_elements[4].getAlphaMean(), sim_elements[4].getAlpha(1, 1));
}

TEST_F(SpecularDetectorTest, Clone)
{
    FixedBinAxis axis("axis0", 5, 1.0 * Units::deg, 10.0 * Units::deg);
    SpecularDetector1D detector(axis);
    std::unique_ptr<SpecularDetector1D> clone(detector.clone());
    Beam beam;
    beam.setCentralK(1.0 * Units::angstrom, 0.4 * Units::deg, 0.0);

    const auto data = clone->createDetectorMap(beam, AxesUnits::DEGREES);
    EXPECT_EQ(data->getAxis(0).size(), 5u);
    EXPECT_EQ(data->getAxis(0).getMin(), 1.0);
    EXPECT_EQ(data->getAxis(0).getMax(), 10.0);

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
