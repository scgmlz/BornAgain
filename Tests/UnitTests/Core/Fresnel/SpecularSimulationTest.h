#ifndef SPECULARSIMULATIONTEST_H
#define SPECULARSIMULATIONTEST_H

#include "SpecularSimulation.h"
#include "HomogeneousMaterial.h"
#include "IMultiLayerBuilder.h"
#include "Exceptions.h"
#include "FixedBinAxis.h"
#include "Layer.h"
#include "MultiLayer.h"
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
    HomogeneousMaterial mat0("ambience", 0.0, 0.0);
    HomogeneousMaterial mat1("PartA", 5e-6, 0.0);
    HomogeneousMaterial mat2("substrate", 15e-6, 0.0);

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
    ASSERT_THROW( sim.runSimulation(), Exceptions::ClassInitializationException);
    EXPECT_EQ(nullptr, sim.getAlphaAxis());
    EXPECT_EQ(nullptr, sim.getSample());
    EXPECT_EQ(nullptr, sim.getSampleBuilder().get());
    ASSERT_THROW( sim.getScalarR(0), Exceptions::ClassInitializationException);
    ASSERT_THROW( sim.getScalarT(0), Exceptions::ClassInitializationException);
    ASSERT_THROW( sim.getScalarKz(0), Exceptions::ClassInitializationException);
}

TEST_F(SpecularSimulationTest, CloneOfEmpty)
{
    SpecularSimulation sim;

    SpecularSimulation *clone = sim.clone();
    ASSERT_THROW( clone->runSimulation(), Exceptions::ClassInitializationException);
    EXPECT_EQ(nullptr, clone->getAlphaAxis());
    EXPECT_EQ(nullptr, clone->getSample());
    EXPECT_EQ(nullptr, clone->getSampleBuilder().get());
    ASSERT_THROW( clone->getScalarR(0), Exceptions::ClassInitializationException);
    ASSERT_THROW( clone->getScalarT(0), Exceptions::ClassInitializationException);
    ASSERT_THROW( clone->getScalarKz(0), Exceptions::ClassInitializationException);
    delete clone;
}

TEST_F(SpecularSimulationTest, SetBeamParameters)
{
    SpecularSimulation sim;

    sim.setBeamParameters(1.0, 10, -2.0, 3.0);
    EXPECT_EQ(size_t(10), sim.getAlphaAxis()->size());
    EXPECT_EQ(-2.0, sim.getAlphaAxis()->getMin());
    EXPECT_EQ(3.0, sim.getAlphaAxis()->getMax());

    FixedBinAxis axis("axis",2, -1.0, 2.0);
    sim.setBeamParameters(1.0, axis);
    EXPECT_EQ(size_t(2), sim.getAlphaAxis()->size());
    EXPECT_EQ(-1.0, sim.getAlphaAxis()->getMin());
    EXPECT_EQ(2.0, sim.getAlphaAxis()->getMax());
}

TEST_F(SpecularSimulationTest, ConstructSimulation)
{
    SpecularSimulation sim;
    sim.setBeamParameters(1.0, 10, 0.0*Units::degree, 2.0*Units::degree);
    sim.setSample(multilayer);
    EXPECT_EQ( size_t(3), dynamic_cast<MultiLayer *>(sim.getSample())->getNumberOfLayers());

    ASSERT_THROW( sim.getScalarR(0), Exceptions::ClassInitializationException);
    ASSERT_THROW( sim.getScalarT(0), Exceptions::ClassInitializationException);
    ASSERT_THROW( sim.getScalarKz(0), Exceptions::ClassInitializationException);

    sim.runSimulation();
    EXPECT_EQ(size_t(10), sim.getScalarR(0).size());
    EXPECT_EQ(size_t(10), sim.getScalarT(0).size());
    EXPECT_EQ(size_t(10), sim.getScalarKz(0).size());

    ASSERT_THROW( sim.getScalarR(3), Exceptions::OutOfBoundsException);
    ASSERT_THROW( sim.getScalarT(3), Exceptions::OutOfBoundsException);
    ASSERT_THROW( sim.getScalarKz(3), Exceptions::OutOfBoundsException);

}

TEST_F(SpecularSimulationTest, SimulationClone)
{
    SpecularSimulation sim;
    sim.setBeamParameters(1.0, 10, 0.0*Units::degree, 2.0*Units::degree);
    sim.setSample(multilayer);

    SpecularSimulation *clone = sim.clone();

    EXPECT_EQ( size_t(3), dynamic_cast<MultiLayer *>(clone->getSample())->getNumberOfLayers());

    ASSERT_THROW( clone->getScalarR(0), Exceptions::ClassInitializationException);
    ASSERT_THROW( clone->getScalarT(0), Exceptions::ClassInitializationException);
    ASSERT_THROW( clone->getScalarKz(0), Exceptions::ClassInitializationException);
    delete clone;

    sim.runSimulation();

    clone = sim.clone();
    EXPECT_EQ(size_t(10), clone->getScalarR(0).size());
    EXPECT_EQ(size_t(10), clone->getScalarT(0).size());
    EXPECT_EQ(size_t(10), clone->getScalarKz(0).size());
}

#endif // SPECULARSIMULATIONTEST_H
