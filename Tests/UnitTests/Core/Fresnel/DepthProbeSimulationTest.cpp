#include "Core/Simulation/DepthProbeSimulation.h"
#include "Base/Const/Units.h"
#include "Base/Math/Constants.h"
#include "Device/Histo/Histogram2D.h"
#include "Param/Base/RealParameter.h"
#include "Param/Distrib/Distributions.h"
#include "Param/Varia/ParameterPattern.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/SampleBuilderEngine/ISampleBuilder.h"
#include "Tests/GTestWrapper/google_test.h"

class DepthProbeSimulationTest : public ::testing::Test {
protected:
    DepthProbeSimulationTest();

    std::unique_ptr<DepthProbeSimulation> defaultSimulation();
    void checkBeamState(const DepthProbeSimulation& sim);
    void checkEmptySimulation(DepthProbeSimulation& sim);

    MultiLayer multilayer;
};

DepthProbeSimulationTest::DepthProbeSimulationTest() {
    Material mat0 = HomogeneousMaterial("ambience", 0.0, 0.0);
    Material mat1 = HomogeneousMaterial("PartA", 5e-6, 0.0);
    Material mat2 = HomogeneousMaterial("substrate", 15e-6, 0.0);

    Layer layer0(mat0);
    Layer layer1(mat1, 10 * Units::nm);
    Layer layer2(mat2);

    multilayer.addLayer(layer0);
    multilayer.addLayer(layer1);
    multilayer.addLayer(layer2);
}

std::unique_ptr<DepthProbeSimulation> DepthProbeSimulationTest::defaultSimulation() {
    std::unique_ptr<DepthProbeSimulation> result = std::make_unique<DepthProbeSimulation>();
    result->setBeamParameters(1.0, 10, 0.0 * Units::deg, 2.0 * Units::deg);
    result->setZSpan(12, -30.0 * Units::nm, 10.0 * Units::nm);
    result->setSample(multilayer);
    return result;
}

void DepthProbeSimulationTest::checkBeamState(const DepthProbeSimulation& sim) {
    const auto* inclination = sim.instrument().beam().parameter("InclinationAngle");
    const auto test_limits = RealLimits::limited(-M_PI_2, M_PI_2);
    EXPECT_EQ(test_limits, inclination->limits());
    EXPECT_EQ(0.0, inclination->value());
}

void DepthProbeSimulationTest::checkEmptySimulation(DepthProbeSimulation& sim) {
    ASSERT_THROW(sim.runSimulation(), std::runtime_error);
    ASSERT_THROW(sim.getAlphaAxis(), std::runtime_error);
    ASSERT_THROW(sim.getZAxis(), std::runtime_error);
    EXPECT_EQ(nullptr, sim.sample());
    ASSERT_THROW(sim.result(), std::runtime_error);

    checkBeamState(sim);
}

TEST_F(DepthProbeSimulationTest, InitialState) {
    std::unique_ptr<DepthProbeSimulation> sim = std::make_unique<DepthProbeSimulation>();
    std::unique_ptr<DepthProbeSimulation> sim_clone(sim->clone());
    checkEmptySimulation(*sim);
    sim.reset();
    checkEmptySimulation(*sim_clone);
}

TEST_F(DepthProbeSimulationTest, CheckAxesOfDefaultSimulation) {
    auto sim = defaultSimulation();

    const auto alpha_axis = sim->getAlphaAxis();
    EXPECT_TRUE(dynamic_cast<const FixedBinAxis*>(alpha_axis));
    EXPECT_EQ(alpha_axis->size(), 10u);
    EXPECT_EQ(alpha_axis->lowerBound(), 0.0 * Units::deg);
    EXPECT_EQ(alpha_axis->upperBound(), 2.0 * Units::deg);

    const auto z_axis = sim->getZAxis();
    EXPECT_TRUE(dynamic_cast<const FixedBinAxis*>(z_axis));
    EXPECT_EQ(z_axis->size(), 12u);
    EXPECT_EQ(z_axis->lowerBound(), -30.0 * Units::nm);
    EXPECT_EQ(z_axis->upperBound(), 10.0 * Units::nm);

    const auto sim_clone = sim->clone();
    EXPECT_FALSE(alpha_axis == sim_clone->getAlphaAxis());
    EXPECT_FALSE(z_axis == sim_clone->getZAxis());
}

TEST_F(DepthProbeSimulationTest, SetBeamParameters) {
    DepthProbeSimulation sim;
    const auto& beam = sim.instrument().beam();

    sim.setBeamParameters(1.0, 10, 1.0 * Units::deg, 10.0 * Units::deg);
    EXPECT_EQ(10u, sim.getAlphaAxis()->size());
    EXPECT_EQ(1.0 * Units::deg, sim.getAlphaAxis()->lowerBound());
    EXPECT_EQ(10.0 * Units::deg, sim.getAlphaAxis()->upperBound());
    EXPECT_EQ(1.0, beam.intensity());
    EXPECT_EQ(1.0, beam.wavelength());
    EXPECT_EQ(0.0, beam.direction().alpha());
    EXPECT_EQ(0.0, beam.direction().phi());

    checkBeamState(sim);

    sim.beam().setIntensity(2.0);
    EXPECT_EQ(2.0, beam.intensity());

    EXPECT_THROW(sim.setBeamParameters(1.0, 10, -2.0, 3.0), std::runtime_error);
    EXPECT_THROW(sim.setBeamParameters(1.0, 10, 2.0, 1.0), std::runtime_error);
    EXPECT_THROW(sim.setBeamParameters(1.0, 0, 1.0, 2.0), std::runtime_error);
    EXPECT_THROW(sim.setBeamParameters(-1.0, 1, 1.0, 2.0), std::runtime_error);

    EXPECT_EQ(10u, sim.getAlphaAxis()->size());
    EXPECT_EQ(1.0 * Units::deg, sim.getAlphaAxis()->lowerBound());
    EXPECT_EQ(10.0 * Units::deg, sim.getAlphaAxis()->upperBound());
    EXPECT_EQ(2.0, beam.intensity());
    EXPECT_EQ(1.0, beam.wavelength());
    EXPECT_EQ(0.0, beam.direction().alpha());
    EXPECT_EQ(0.0, beam.direction().phi());

    checkBeamState(sim);

    sim.setInstrument(Instrument());

    checkBeamState(sim);
}

TEST_F(DepthProbeSimulationTest, ResultAquisition) {
    auto sim = defaultSimulation();

    EXPECT_EQ(3u, sim->sample()->numberOfLayers());

    ASSERT_THROW(sim->result(), std::runtime_error);

    sim->runSimulation();
    SimulationResult sim_result = sim->result();

    EXPECT_THROW(sim_result.histogram2d(Axes::Units::MM), std::runtime_error);

    const std::unique_ptr<Histogram2D> depth_map(sim_result.histogram2d());
    EXPECT_EQ(10u * 12u, depth_map->getTotalNumberOfBins());
    EXPECT_EQ(2u, depth_map->rank());
    EXPECT_EQ(0.0, depth_map->xAxis().lowerBound());
    EXPECT_EQ(2.0, depth_map->xAxis().upperBound());
    EXPECT_EQ(-30.0, depth_map->yAxis().lowerBound());
    EXPECT_EQ(10.0, depth_map->yAxis().upperBound());

    EXPECT_THROW(sim_result.data(Axes::Units::MM), std::runtime_error);

    const auto output = sim_result.data();
    EXPECT_EQ(depth_map->getTotalNumberOfBins(), output->getAllocatedSize());
    EXPECT_EQ(depth_map->rank(), output->rank());
    EXPECT_EQ(depth_map->xAxis().lowerBound(), output->axis(0).lowerBound());
    EXPECT_EQ(depth_map->xAxis().upperBound(), output->axis(0).upperBound());

    checkBeamState(*sim);
}

TEST_F(DepthProbeSimulationTest, SimulationClone) {
    auto sim = defaultSimulation();

    sim->runSimulation();
    SimulationResult sim_result = sim->result();
    std::unique_ptr<DepthProbeSimulation> clone(sim->clone());
    sim.reset();

    SimulationResult clone_result = clone->result();

    auto sim_output = sim_result.data();
    auto clone_output = clone_result.data();

    EXPECT_EQ(sim_output->getAllocatedSize(), clone_output->getAllocatedSize());
    for (size_t i = 0; i < sim_output->getAllocatedSize(); ++i) {
        EXPECT_EQ((*sim_output)[i], (*clone_output)[i]);
    }
}

TEST_F(DepthProbeSimulationTest, AddingBeamDistributions) {
    auto sim = defaultSimulation();
    DistributionGaussian distribution(1.0, 2.0);

    ParameterPattern wl_pattern;
    wl_pattern.beginsWith("*").add("Beam").add("Wavelength");
    ParameterPattern incl_ang_pattern;
    incl_ang_pattern.beginsWith("*").add("Beam").add("InclinationAngle");
    ParameterPattern beam_pattern;
    beam_pattern.beginsWith("*").add("Beam").add("*");

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
