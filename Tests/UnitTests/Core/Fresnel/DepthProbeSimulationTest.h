#include "google_test.h"
#include "DepthProbeSimulation.h"
#include "Distributions.h"
#include "FixedBinAxis.h"
#include "Histogram2D.h"
#include "IMultiLayerBuilder.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MathConstants.h"
#include "MultiLayer.h"
#include "ParameterPattern.h"
#include "RealParameter.h"
#include "Units.h"

class DepthProbeSimulationTest : public ::testing::Test
{
protected:
    DepthProbeSimulationTest();
    ~DepthProbeSimulationTest();

    std::unique_ptr<DepthProbeSimulation> defaultSimulation();
    void checkBeamState(const DepthProbeSimulation& sim);
    void checkEmptySimulation(DepthProbeSimulation& sim);

    MultiLayer multilayer;
};

DepthProbeSimulationTest::DepthProbeSimulationTest()
{
    Material mat0 = HomogeneousMaterial("ambience", 0.0, 0.0);
    Material mat1 = HomogeneousMaterial("PartA", 5e-6, 0.0);
    Material mat2 = HomogeneousMaterial("substrate", 15e-6, 0.0);

    Layer layer0(mat0);
    Layer layer1(mat1, 10 * Units::nanometer);
    Layer layer2(mat2);

    multilayer.addLayer(layer0);
    multilayer.addLayer(layer1);
    multilayer.addLayer(layer2);
}

DepthProbeSimulationTest::~DepthProbeSimulationTest() = default;

std::unique_ptr<DepthProbeSimulation> DepthProbeSimulationTest::defaultSimulation()
{
    std::unique_ptr<DepthProbeSimulation> result = std::make_unique<DepthProbeSimulation>();
    result->setBeamParameters(1.0, 10, 0.0 * Units::degree, 2.0 * Units::degree);
    result->setZSpan(12, -30.0 * Units::nanometer, 10.0 * Units::nanometer);
    result->setSample(multilayer);
    return result;
}

void DepthProbeSimulationTest::checkBeamState(const DepthProbeSimulation& sim)
{
    const auto* inclination = sim.getInstrument().getBeam().parameter(BornAgain::Inclination);
    const auto test_limits = RealLimits::limited(-M_PI_2, M_PI_2);
    EXPECT_EQ(test_limits, inclination->limits());
    EXPECT_EQ(0.0, inclination->value());
}

void DepthProbeSimulationTest::checkEmptySimulation(DepthProbeSimulation& sim)
{
    ASSERT_THROW(sim.runSimulation(), std::runtime_error);
    ASSERT_THROW(sim.getAlphaAxis(), std::runtime_error);
    ASSERT_THROW(sim.getZAxis(), std::runtime_error);
    EXPECT_EQ(nullptr, sim.sample());
    ASSERT_THROW(sim.result(), std::runtime_error);

    checkBeamState(sim);
}

TEST_F(DepthProbeSimulationTest, InitialState)
{
    std::unique_ptr<DepthProbeSimulation> sim = std::make_unique<DepthProbeSimulation>();
    std::unique_ptr<DepthProbeSimulation> sim_clone(sim->clone());
    checkEmptySimulation(*sim);
    sim.reset();
    checkEmptySimulation(*sim_clone);
}

TEST_F(DepthProbeSimulationTest, CheckAxesOfDefaultSimulation)
{
    auto sim = defaultSimulation();

    const auto alpha_axis = sim->getAlphaAxis();
    EXPECT_TRUE(dynamic_cast<const FixedBinAxis*>(alpha_axis));
    EXPECT_EQ(alpha_axis->size(), 10u);
    EXPECT_EQ(alpha_axis->getMin(), 0.0 * Units::degree);
    EXPECT_EQ(alpha_axis->getMax(), 2.0 * Units::degree);

    const auto z_axis = sim->getZAxis();
    EXPECT_TRUE(dynamic_cast<const FixedBinAxis*>(z_axis));
    EXPECT_EQ(z_axis->size(), 12u);
    EXPECT_EQ(z_axis->getMin(), -30.0 * Units::nanometer);
    EXPECT_EQ(z_axis->getMax(), 10.0 * Units::nanometer);

    const auto sim_clone = sim->clone();
    EXPECT_FALSE(alpha_axis == sim_clone->getAlphaAxis());
    EXPECT_FALSE(z_axis == sim_clone->getZAxis());
}

TEST_F(DepthProbeSimulationTest, SetBeamParameters)
{
    DepthProbeSimulation sim;
    const auto& beam = sim.getInstrument().getBeam();

    sim.setBeamParameters(1.0, 10, 1.0 * Units::degree, 10.0 * Units::degree);
    EXPECT_EQ(10u, sim.getAlphaAxis()->size());
    EXPECT_EQ(1.0 * Units::degree, sim.getAlphaAxis()->getMin());
    EXPECT_EQ(10.0 * Units::degree, sim.getAlphaAxis()->getMax());
    EXPECT_EQ(1.0, beam.getIntensity());
    EXPECT_EQ(1.0, beam.getWavelength());
    EXPECT_EQ(0.0, beam.getAlpha());
    EXPECT_EQ(0.0, beam.getPhi());

    checkBeamState(sim);

    sim.setBeamIntensity(2.0);
    EXPECT_EQ(2.0, beam.getIntensity());

    EXPECT_THROW(sim.setBeamParameters(1.0, 10, -2.0, 3.0),
                 std::runtime_error);
    EXPECT_THROW(sim.setBeamParameters(1.0, 10, 2.0, 1.0),
                 std::runtime_error);
    EXPECT_THROW(sim.setBeamParameters(1.0, 0, 1.0, 2.0),
                 std::runtime_error);
    EXPECT_THROW(sim.setBeamParameters(-1.0, 1, 1.0, 2.0),
                 std::runtime_error);

    EXPECT_EQ(10u, sim.getAlphaAxis()->size());
    EXPECT_EQ(1.0 * Units::degree, sim.getAlphaAxis()->getMin());
    EXPECT_EQ(10.0 * Units::degree, sim.getAlphaAxis()->getMax());
    EXPECT_EQ(2.0, beam.getIntensity());
    EXPECT_EQ(1.0, beam.getWavelength());
    EXPECT_EQ(0.0, beam.getAlpha());
    EXPECT_EQ(0.0, beam.getPhi());

    checkBeamState(sim);

    sim.setInstrument(Instrument());

    checkBeamState(sim);
}

TEST_F(DepthProbeSimulationTest, ResultAquisition)
{
    auto sim = defaultSimulation();

    EXPECT_EQ(3u, sim->sample()->numberOfLayers());

    ASSERT_THROW(sim->result(), std::runtime_error);

    sim->runSimulation();
    SimulationResult sim_result = sim->result();

    EXPECT_THROW(sim_result.histogram1d(), std::runtime_error);
    EXPECT_THROW(sim_result.histogram2d(AxesUnits::DEGREES), std::runtime_error);
    EXPECT_THROW(sim_result.histogram2d(AxesUnits::RADIANS), std::runtime_error);
    EXPECT_THROW(sim_result.histogram2d(AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(sim_result.histogram2d(AxesUnits::NBINS), std::runtime_error);
    EXPECT_THROW(sim_result.histogram2d(AxesUnits::NM), std::runtime_error);
    EXPECT_THROW(sim_result.histogram2d(AxesUnits::MM), std::runtime_error);

    const std::unique_ptr<Histogram2D> depth_map(sim_result.histogram2d());
    EXPECT_EQ(10u * 12u, depth_map->getTotalNumberOfBins());
    EXPECT_EQ(2u, depth_map->getRank());
    EXPECT_EQ(0.0, depth_map->getXaxis().getMin());
    EXPECT_EQ(2.0, depth_map->getXaxis().getMax());
    EXPECT_EQ(-30.0, depth_map->getYaxis().getMin());
    EXPECT_EQ(10.0, depth_map->getYaxis().getMax());

    EXPECT_THROW(sim_result.data(AxesUnits::DEGREES), std::runtime_error);
    EXPECT_THROW(sim_result.data(AxesUnits::RADIANS), std::runtime_error);
    EXPECT_THROW(sim_result.data(AxesUnits::QSPACE), std::runtime_error);
    EXPECT_THROW(sim_result.data(AxesUnits::NBINS), std::runtime_error);
    EXPECT_THROW(sim_result.data(AxesUnits::NM), std::runtime_error);
    EXPECT_THROW(sim_result.data(AxesUnits::MM), std::runtime_error);

    const std::unique_ptr<OutputData<double>> output(sim_result.data());
    EXPECT_EQ(depth_map->getTotalNumberOfBins(), output->getAllocatedSize());
    EXPECT_EQ(depth_map->getRank(), output->getRank());
    EXPECT_EQ(depth_map->getXaxis().getMin(), output->getAxis(0).getMin());
    EXPECT_EQ(depth_map->getXaxis().getMax(), output->getAxis(0).getMax());

    checkBeamState(*sim);
}

TEST_F(DepthProbeSimulationTest, SimulationClone)
{
    auto sim = defaultSimulation();

    sim->runSimulation();
    SimulationResult sim_result = sim->result();
    std::unique_ptr<DepthProbeSimulation> clone(sim->clone());
    sim.reset();

    SimulationResult clone_result = clone->result();

    std::unique_ptr<OutputData<double>> sim_output(sim_result.data());
    std::unique_ptr<OutputData<double>> clone_output(clone_result.data());

    EXPECT_EQ(sim_output->getAllocatedSize(), clone_output->getAllocatedSize());
    for (size_t i = 0; i < sim_output->getAllocatedSize(); ++i) {
        EXPECT_EQ((*sim_output)[i], (*clone_output)[i]);
    }
}

TEST_F(DepthProbeSimulationTest, AddingBeamDistributions)
{
    auto sim = defaultSimulation();
    DistributionGaussian distribution(1.0, 2.0);

    ParameterPattern wl_pattern;
    wl_pattern.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Wavelength);
    ParameterPattern incl_ang_pattern;
    incl_ang_pattern.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Inclination);
    ParameterPattern beam_pattern;
    beam_pattern.beginsWith("*").add(BornAgain::BeamType).add("*");

    EXPECT_THROW(sim->addParameterDistribution(incl_ang_pattern.toStdString(), distribution, 5),
                 std::runtime_error);
    EXPECT_THROW(sim->addParameterDistribution(beam_pattern.toStdString(), distribution, 5),
                 std::runtime_error);
    EXPECT_NO_THROW(sim->addParameterDistribution(wl_pattern.toStdString(), distribution, 5));

    checkBeamState(*sim);

    DistributionGaussian distribution2(0.0, 2.0);
    EXPECT_NO_THROW(
        sim->addParameterDistribution(incl_ang_pattern.toStdString(), distribution2, 5));

    checkBeamState(*sim);
}
