#include "Core/Simulation/SpecularSimulation.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Basics/Units.h"
#include "Core/Binning/FixedBinAxis.h"
#include "Core/Binning/VariableBinAxis.h"
#include "Core/Instrument/AngularSpecScan.h"
#include "Core/Instrument/QSpecScan.h"
#include "Core/Intensity/Histogram1D.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterPattern.h"
#include "Core/Parametrization/RealParameter.h"
#include "Tests/GTestWrapper/google_test.h"
#include <iostream>

class SpecularSimulationTest : public ::testing::Test
{
protected:
    SpecularSimulationTest();

    std::unique_ptr<SpecularSimulation> defaultSimulation();
    void checkBeamState(const SpecularSimulation& sim);

    MultiLayer multilayer;
};

SpecularSimulationTest::SpecularSimulationTest()
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

TEST_F(SpecularSimulationTest, InitialState)
{
    SpecularSimulation sim;
    ASSERT_THROW(sim.runSimulation(), std::runtime_error);
    ASSERT_THROW(sim.coordinateAxis(), std::runtime_error);
    EXPECT_EQ(nullptr, sim.sample());
    ASSERT_THROW(sim.result(), std::runtime_error);
}

std::unique_ptr<SpecularSimulation> SpecularSimulationTest::defaultSimulation()
{
    auto result = std::make_unique<SpecularSimulation>();
    AngularSpecScan scan(1.0, FixedBinAxis("axis", 10, 0.0 * Units::degree, 2.0 * Units::degree));
    result->setScan(scan);
    result->setSample(multilayer);
    return result;
}

void SpecularSimulationTest::checkBeamState(const SpecularSimulation& sim)
{
    const auto* inclination = sim.getInstrument().getBeam().parameter("InclinationAngle");
    const auto test_limits = RealLimits::limited(-M_PI_2, M_PI_2);
    EXPECT_EQ(test_limits, inclination->limits());
    EXPECT_EQ(0.0, inclination->value());
}

TEST_F(SpecularSimulationTest, CloneOfEmpty)
{
    SpecularSimulation sim;

    std::unique_ptr<SpecularSimulation> clone(sim.clone());
    ASSERT_THROW(clone->runSimulation(), std::runtime_error);
    ASSERT_THROW(clone->coordinateAxis(), std::runtime_error);
    EXPECT_EQ(nullptr, clone->sample());
    ASSERT_THROW(clone->result(), std::runtime_error);

    checkBeamState(sim);
    checkBeamState(*clone);
}

TEST_F(SpecularSimulationTest, SetAngularScan)
{
    SpecularSimulation sim;
    AngularSpecScan scan(1.0, std::vector<double>{1.0 * Units::deg, 3.0 * Units::deg});
    sim.setScan(scan);
    const auto& beam = sim.getInstrument().getBeam();

    EXPECT_EQ(2u, sim.coordinateAxis()->size());
    EXPECT_EQ(1.0 * Units::deg, sim.coordinateAxis()->getMin());
    EXPECT_EQ(3.0 * Units::deg, sim.coordinateAxis()->getMax());
    EXPECT_EQ(1.0, beam.getIntensity());
    EXPECT_EQ(1.0, beam.getWavelength());
    EXPECT_EQ(0.0, beam.getAlpha());
    EXPECT_EQ(0.0, beam.getPhi());

    checkBeamState(sim);

    sim.setBeamIntensity(2.0);
    EXPECT_EQ(2.0, beam.getIntensity());

    AngularSpecScan scan2(1.0, 10, 1.0 * Units::degree, 10.0 * Units::degree);
    sim.setScan(scan2);
    EXPECT_EQ(10u, sim.coordinateAxis()->size());
    EXPECT_EQ(1.0 * Units::degree, sim.coordinateAxis()->getMin());
    EXPECT_EQ(10.0 * Units::degree, sim.coordinateAxis()->getMax());
    EXPECT_EQ(2.0, beam.getIntensity());
    EXPECT_EQ(1.0, beam.getWavelength());
    EXPECT_EQ(0.0, beam.getAlpha());
    EXPECT_EQ(0.0, beam.getPhi());
    checkBeamState(sim);

    AngularSpecScan scan3(1.0, 10, -1.0 * Units::degree, 2.0 * Units::degree);
    EXPECT_THROW(sim.setScan(scan3), std::runtime_error);

    EXPECT_EQ(10u, sim.coordinateAxis()->size());
    EXPECT_EQ(1.0 * Units::degree, sim.coordinateAxis()->getMin());
    EXPECT_EQ(10.0 * Units::degree, sim.coordinateAxis()->getMax());
    EXPECT_EQ(2.0, beam.getIntensity());
    EXPECT_EQ(1.0, beam.getWavelength());
    EXPECT_EQ(0.0, beam.getAlpha());
    EXPECT_EQ(0.0, beam.getPhi());
    checkBeamState(sim);

    sim.setInstrument(Instrument());
    checkBeamState(sim);
}

TEST_F(SpecularSimulationTest, SetQScan)
{
    SpecularSimulation sim;

    QSpecScan scan(std::vector<double>{1.0, 3.0});
    sim.setScan(scan);

    const auto& beam = sim.getInstrument().getBeam();

    EXPECT_EQ(2u, sim.coordinateAxis()->size());
    EXPECT_EQ(1.0, sim.coordinateAxis()->getMin());
    EXPECT_EQ(3.0, sim.coordinateAxis()->getMax());
    EXPECT_EQ(1.0, beam.getIntensity());
    EXPECT_EQ(1.0, beam.getWavelength());
    EXPECT_EQ(0.0, beam.getAlpha());
    EXPECT_EQ(0.0, beam.getPhi());

    checkBeamState(sim);

    sim.setBeamIntensity(2.0);
    EXPECT_EQ(2.0, beam.getIntensity());

    QSpecScan scan2(10, 1.0, 10.0);
    sim.setScan(scan2);
    EXPECT_EQ(10u, sim.coordinateAxis()->size());
    EXPECT_EQ(1.0, sim.coordinateAxis()->getMin());
    EXPECT_EQ(10.0, sim.coordinateAxis()->getMax());
    EXPECT_EQ(2.0, beam.getIntensity());
    EXPECT_EQ(1.0, beam.getWavelength());
    EXPECT_EQ(0.0, beam.getAlpha());
    EXPECT_EQ(0.0, beam.getPhi());
    checkBeamState(sim);
}

TEST_F(SpecularSimulationTest, ConstructSimulation)
{
    auto sim = defaultSimulation();

    EXPECT_EQ(3u, sim->sample()->numberOfLayers());

    SimulationResult sim_result = sim->result();
    auto data = sim_result.data();
    EXPECT_EQ(data->getAllocatedSize(), 10u);
    EXPECT_EQ(data->totalSum(), 0.0);
    EXPECT_EQ(data->getRank(), 1u);

    sim->runSimulation();
    sim_result = sim->result();

    data = sim_result.data();
    EXPECT_EQ(data->getAllocatedSize(), 10u);
    EXPECT_EQ(data->getRank(), 1u);

    EXPECT_NEAR(0.1 * Units::degree, sim_result.axis(AxesUnits::RADIANS).front(),
                Units::degree * 1e-11);
    EXPECT_NEAR(1.9 * Units::degree, sim_result.axis(AxesUnits::RADIANS).back(),
                Units::degree * 1e-10);

    checkBeamState(*sim);
}

TEST_F(SpecularSimulationTest, SimulationClone)
{
    auto sim = defaultSimulation();

    std::unique_ptr<SpecularSimulation> clone(sim->clone());

    EXPECT_EQ(3u, clone->sample()->numberOfLayers());

    SimulationResult clone_result = clone->result();
    auto data = clone_result.data();
    EXPECT_EQ(data->getAllocatedSize(), 10u);
    EXPECT_EQ(data->totalSum(), 0.0);

    checkBeamState(*clone);

    sim->runSimulation();

    std::unique_ptr<SpecularSimulation> clone2(sim->clone());
    clone_result = clone2->result();

    const auto output_data = clone_result.data();
    EXPECT_EQ(10u, output_data->getAllocatedSize());

    checkBeamState(*clone2);
}

TEST_F(SpecularSimulationTest, AddingBeamDistributions)
{
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

TEST_F(SpecularSimulationTest, OutOfRangeAngles)
{
    auto sim = defaultSimulation();
    auto& beam = sim->getInstrument().getBeam();
    beam.parameter("InclinationAngle")->setValue(-0.2 * Units::deg);

    sim->runSimulation();
    auto sim_result = sim->result();

    std::unique_ptr<OutputData<double>> data(sim_result.data());
    EXPECT_EQ(0.0, (*data)[0]);
    EXPECT_NE(0.0, (*data)[1]);
}
