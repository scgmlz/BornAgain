#include "Core/Simulation/SpecularSimulation.h"
#include "Base/Axis/VariableBinAxis.h"
#include "Base/Const/Units.h"
#include "Base/Math/Constants.h"
#include "Core/Scan/AngularSpecScan.h"
#include "Core/Scan/QSpecScan.h"
#include "Device/Histo/Histogram1D.h"
#include "Param/Base/RealParameter.h"
#include "Param/Distrib/Distributions.h"
#include "Param/Varia/ParameterPattern.h"
#include "Sample/Material/MaterialFactoryFuncs.h"
#include "Sample/Multilayer/Layer.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/SampleBuilderEngine/ISampleBuilder.h"
#include "Tests/GTestWrapper/google_test.h"
#include <iostream>

class SpecularSimulationTest : public ::testing::Test {
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
    Layer layer1(mat1, 10 * Units::nm);
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
    AngularSpecScan scan(1.0, FixedBinAxis("axis", 10, 0.0 * Units::deg, 2.0 * Units::deg));
    result->setScan(scan);
    result->setSample(multilayer);
    return result;
}

void SpecularSimulationTest::checkBeamState(const SpecularSimulation& sim)
{
    const auto* inclination = sim.beam().parameter("InclinationAngle");
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
    const auto& beam = sim.beam();

    EXPECT_EQ(2u, sim.coordinateAxis()->size());
    EXPECT_EQ(1.0 * Units::deg, sim.coordinateAxis()->lowerBound());
    EXPECT_EQ(3.0 * Units::deg, sim.coordinateAxis()->upperBound());
    EXPECT_EQ(1.0, beam.intensity());
    EXPECT_EQ(1.0, beam.wavelength());
    EXPECT_EQ(0.0, beam.direction().alpha());
    EXPECT_EQ(0.0, beam.direction().phi());

    checkBeamState(sim);

    sim.beam().setIntensity(2.0);
    EXPECT_EQ(2.0, beam.intensity());

    SpecularSimulation sim2;
    AngularSpecScan scan2(1.0, 10, 1.0 * Units::deg, 10.0 * Units::deg);
    sim2.setScan(scan2);
    EXPECT_EQ(10u, sim2.coordinateAxis()->size());
    EXPECT_EQ(1.0 * Units::deg, sim2.coordinateAxis()->lowerBound());
    EXPECT_EQ(10.0 * Units::deg, sim2.coordinateAxis()->upperBound());
    EXPECT_EQ(2.0, beam.intensity());
    EXPECT_EQ(1.0, beam.wavelength());
    EXPECT_EQ(0.0, beam.direction().alpha());
    EXPECT_EQ(0.0, beam.direction().phi());
    checkBeamState(sim2);

    SpecularSimulation sim3;
    AngularSpecScan scan3(1.0, 10, -1.0 * Units::deg, 2.0 * Units::deg);
    EXPECT_THROW(sim3.setScan(scan3), std::runtime_error);

    checkBeamState(sim3);

    EXPECT_THROW(sim2.setScan(scan2), std::runtime_error);
    EXPECT_EQ(10u, sim2.coordinateAxis()->size());
    EXPECT_EQ(1.0 * Units::deg, sim2.coordinateAxis()->lowerBound());
    EXPECT_EQ(10.0 * Units::deg, sim2.coordinateAxis()->upperBound());
    EXPECT_EQ(2.0, beam.intensity());
    EXPECT_EQ(1.0, beam.wavelength());
    EXPECT_EQ(0.0, beam.direction().alpha());
    EXPECT_EQ(0.0, beam.direction().phi());

    sim3.setInstrument(Instrument());
    checkBeamState(sim3);

    SpecularSimulation sim4;
    AngularSpecScan scan4(1.0, 10, .0 * Units::deg, 2.0 * Units::deg);
    const auto polarization = kvector_t({0., 0., 1.});
    const auto analyzer     = kvector_t({0., 0., 1.});
    sim4.beam().setPolarization(polarization);
    sim4.detector().setAnalyzerProperties(analyzer, 0.33, 0.22);
    sim4.setScan(scan4);
//    EXPECT_THROW(sim4.setScan(scan4), std::runtime_error);

    EXPECT_EQ(.0 * Units::deg, sim4.coordinateAxis()->lowerBound());
    EXPECT_EQ(2.0 * Units::deg, sim4.coordinateAxis()->upperBound());
    EXPECT_EQ(10u, sim4.coordinateAxis()->size());
    EXPECT_EQ(1.0, sim4.beam().intensity());
    EXPECT_EQ(1.0, sim4.beam().wavelength());
    EXPECT_EQ(0.0, sim4.beam().direction().alpha());
    EXPECT_EQ(0.0, sim4.beam().direction().phi());

    EXPECT_EQ(sim4.beam().getBlochVector(), polarization);
    EXPECT_EQ(sim4.detector().detectionProperties().analyzerDirection(), analyzer);

    sim3.setInstrument(Instrument());
    checkBeamState(sim3);
}

TEST_F(SpecularSimulationTest, SetQScan)
{
    SpecularSimulation sim;

    QSpecScan scan(std::vector<double>{1.0, 3.0});
    sim.setScan(scan);

    const auto& beam = sim.beam();

    EXPECT_EQ(2u, sim.coordinateAxis()->size());
    EXPECT_EQ(1.0, sim.coordinateAxis()->lowerBound());
    EXPECT_EQ(3.0, sim.coordinateAxis()->upperBound());
    EXPECT_EQ(1.0, beam.intensity());
    EXPECT_EQ(1.0, beam.wavelength());
    EXPECT_EQ(0.0, beam.direction().alpha());
    EXPECT_EQ(0.0, beam.direction().phi());

    checkBeamState(sim);

    sim.beam().setIntensity(2.0);
    EXPECT_EQ(2.0, beam.intensity());

    SpecularSimulation sim2;
    QSpecScan scan2(10, 1.0, 10.0);
    sim2.setScan(scan2);
    EXPECT_EQ(10u, sim2.coordinateAxis()->size());
    EXPECT_EQ(1.0, sim2.coordinateAxis()->lowerBound());
    EXPECT_EQ(10.0, sim2.coordinateAxis()->upperBound());
    EXPECT_EQ(2.0, beam.intensity());
    EXPECT_EQ(1.0, beam.wavelength());
    EXPECT_EQ(0.0, beam.direction().alpha());
    EXPECT_EQ(0.0, beam.direction().phi());
    checkBeamState(sim2);
}

TEST_F(SpecularSimulationTest, ConstructSimulation)
{
    auto sim = defaultSimulation();

    EXPECT_EQ(3u, sim->sample()->numberOfLayers());

    SimulationResult sim_result = sim->result();
    auto data = sim_result.data();
    EXPECT_EQ(data->getAllocatedSize(), 10u);
    EXPECT_EQ(data->totalSum(), 0.0);
    EXPECT_EQ(data->rank(), 1u);

    sim->runSimulation();
    sim_result = sim->result();

    data = sim_result.data();
    EXPECT_EQ(data->getAllocatedSize(), 10u);
    EXPECT_EQ(data->rank(), 1u);

    EXPECT_NEAR(0.1 * Units::deg, sim_result.axis(Axes::Units::RADIANS).front(),
                Units::deg * 1e-11);
    EXPECT_NEAR(1.9 * Units::deg, sim_result.axis(Axes::Units::RADIANS).back(), Units::deg * 1e-10);

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
    auto& beam = sim->beam();
    beam.parameter("InclinationAngle")->setValue(-0.2 * Units::deg);

    sim->runSimulation();
    auto sim_result = sim->result();

    std::unique_ptr<OutputData<double>> data(sim_result.data());
    EXPECT_EQ(0.0, (*data)[0]);
    EXPECT_NE(0.0, (*data)[1]);
}
