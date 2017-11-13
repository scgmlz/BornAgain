#include "SpecularSimulation.h"
#include "IMultiLayerBuilder.h"
#include "Exceptions.h"
#include "FixedBinAxis.h"
#include "Histogram1D.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MultiLayer.h"
#include "VariableBinAxis.h"
#include "Units.h"
#include <iostream>

class SpecularSimulationTest : public ::testing::Test
{
 protected:
    SpecularSimulationTest();
    MultiLayer multilayer;
};

SpecularSimulationTest::SpecularSimulationTest()
{
    Material mat0 = HomogeneousMaterial("ambience", 0.0, 0.0);
    Material mat1 = HomogeneousMaterial("PartA", 5e-6, 0.0);
    Material mat2 = HomogeneousMaterial("substrate", 15e-6, 0.0);

    Layer layer0(mat0);
    Layer layer1(mat1, 10*Units::nanometer);
    Layer layer2(mat2);

    multilayer.addLayer(layer0);
    multilayer.addLayer(layer1);
    multilayer.addLayer(layer2);
}

TEST_F(SpecularSimulationTest, InitialState)
{
    SpecularSimulation sim;
    ASSERT_THROW( sim.runSimulation(), std::runtime_error);
    EXPECT_EQ(nullptr, sim.getAlphaAxis());
    EXPECT_EQ(nullptr, sim.sample());
    ASSERT_THROW( sim.getScalarR(0), std::runtime_error);
    ASSERT_THROW( sim.getScalarT(0), std::runtime_error);
    ASSERT_THROW( sim.getScalarKz(0), std::runtime_error);
    ASSERT_THROW( sim.reflectivity(), std::runtime_error);
    ASSERT_THROW( sim.transmissivity(), std::runtime_error);
}

TEST_F(SpecularSimulationTest, CloneOfEmpty)
{
    SpecularSimulation sim;

    SpecularSimulation *clone = sim.clone();
    ASSERT_THROW( clone->runSimulation(), std::runtime_error);
    EXPECT_EQ(nullptr, clone->getAlphaAxis());
    EXPECT_EQ(nullptr, clone->sample());
    ASSERT_THROW( clone->getScalarR(0), std::runtime_error);
    ASSERT_THROW( clone->getScalarT(0), std::runtime_error);
    ASSERT_THROW( clone->getScalarKz(0), std::runtime_error);
    ASSERT_THROW( clone->reflectivity(), std::runtime_error);
    ASSERT_THROW( clone->transmissivity(), std::runtime_error);
    delete clone;
}

TEST_F(SpecularSimulationTest, SetBeamParameters)
{
    SpecularSimulation sim;

    VariableBinAxis axis("axis",2, std::vector<double>{1.0, 2.0, 3.0});
    sim.setBeamParameters(1.0, axis);
    EXPECT_EQ(2u, sim.getAlphaAxis()->size());
    EXPECT_EQ(1.0, sim.getAlphaAxis()->getMin());
    EXPECT_EQ(3.0, sim.getAlphaAxis()->getMax());

    sim.setBeamParameters(1.0, 10, 1.0 * Units::degree, 10.0 * Units::degree);
    EXPECT_EQ(10u, sim.getAlphaAxis()->size());
    EXPECT_EQ(1.0 * Units::degree, sim.getAlphaAxis()->getMin());
    EXPECT_EQ(10.0 * Units::degree, sim.getAlphaAxis()->getMax());

    EXPECT_THROW(sim.setBeamParameters(1.0, 10, -2.0, 3.0),
                 Exceptions::ClassInitializationException);
}

TEST_F(SpecularSimulationTest, ConstructSimulation)
{
    SpecularSimulation sim;
    sim.setBeamParameters(1.0, 10, 0.0*Units::degree, 2.0*Units::degree);
    sim.setSample(multilayer);
    EXPECT_EQ(3u, sim.sample()->numberOfLayers());

    ASSERT_THROW( sim.getScalarR(0), std::runtime_error);
    ASSERT_THROW( sim.getScalarT(0), std::runtime_error);
    ASSERT_THROW( sim.getScalarKz(0), std::runtime_error);
    ASSERT_THROW( sim.reflectivity(), std::runtime_error);
    ASSERT_THROW( sim.transmissivity(), std::runtime_error);

    sim.runSimulation();
    EXPECT_EQ(10u, sim.getScalarR(0).size());
    EXPECT_EQ(10u, sim.getScalarT(0).size());
    EXPECT_EQ(10u, sim.getScalarKz(0).size());

    Histogram1D* reflectivity = sim.reflectivity();
    EXPECT_EQ(10u, reflectivity->getTotalNumberOfBins());
    EXPECT_EQ(1u, reflectivity->getRank());
    EXPECT_EQ(0.0, reflectivity->getXaxis().getMin());
    EXPECT_EQ(2.0*Units::degree, reflectivity->getXaxis().getMax());
    EXPECT_DOUBLE_EQ(std::norm(sim.getScalarR(0)[5]), reflectivity->getBinValues()[5]);

    const OutputData<double>* output = sim.getDetectorIntensity();
    EXPECT_EQ(reflectivity->getTotalNumberOfBins(), output->getAllocatedSize());
    EXPECT_EQ(reflectivity->getRank(), output->getRank());
    EXPECT_EQ(reflectivity->getXaxis().getMin(), output->getAxis(0).getMin());
    EXPECT_EQ(reflectivity->getXaxis().getMax(), output->getAxis(0).getMax());

    Histogram1D* transmissivity = sim.transmissivity();
    EXPECT_EQ(10u, transmissivity->getTotalNumberOfBins());
    EXPECT_EQ(1u, transmissivity->getRank());
    EXPECT_EQ(0.0, transmissivity->getXaxis().getMin());
    EXPECT_EQ(2.0*Units::degree, transmissivity->getXaxis().getMax());
    EXPECT_DOUBLE_EQ(std::norm(sim.getScalarT(2)[5]), transmissivity->getBinValues()[5]);

    delete reflectivity;
    delete transmissivity;
    delete output;

    ASSERT_THROW(sim.getScalarR(3), std::runtime_error);
    ASSERT_THROW(sim.getScalarT(3), std::runtime_error);
    ASSERT_THROW(sim.getScalarKz(3), std::runtime_error);
    ASSERT_THROW(sim.reflectivity(3), std::runtime_error);
    ASSERT_THROW(sim.transmissivity(3), std::runtime_error);

}

TEST_F(SpecularSimulationTest, SimulationClone)
{
    SpecularSimulation sim;
    sim.setBeamParameters(1.0, 10, 0.0*Units::degree, 2.0*Units::degree);
    sim.setSample(multilayer);

    SpecularSimulation *clone = sim.clone();

    EXPECT_EQ( size_t(3), clone->sample()->numberOfLayers());

    ASSERT_THROW( clone->getScalarR(0), std::runtime_error);
    ASSERT_THROW( clone->getScalarT(0), std::runtime_error);
    ASSERT_THROW( clone->getScalarKz(0), std::runtime_error);
    ASSERT_THROW( clone->reflectivity(), std::runtime_error);
    ASSERT_THROW( clone->transmissivity(), std::runtime_error);
    ASSERT_THROW( clone->getDetectorIntensity(), std::runtime_error);
    delete clone;

    sim.runSimulation();

    clone = sim.clone();
    EXPECT_EQ(size_t(10), clone->getScalarR(0).size());
    EXPECT_EQ(size_t(10), clone->getScalarT(0).size());
    EXPECT_EQ(size_t(10), clone->getScalarKz(0).size());

    Histogram1D* output = clone->reflectivity();
    EXPECT_EQ(10u, output->getTotalNumberOfBins());
    delete output;

    output = clone->transmissivity();
    EXPECT_EQ(10u, output->getTotalNumberOfBins());
    delete output;
}
