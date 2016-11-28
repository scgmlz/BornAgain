#ifndef GISASSIMULATIONTEST_H
#define GISASSIMULATIONTEST_H

#include "Beam.h"
#include "BornAgainNamespace.h"
#include "GISASSimulation.h"
#include "IMultiLayerBuilder.h"
#include "Layer.h"
#include "MultiLayer.h"
#include "OutputData.h"
#include <memory>
#include <cmath>

class GISASSimulationTest : public ::testing::Test
{
 protected:
    GISASSimulationTest();
    virtual ~GISASSimulationTest();
    GISASSimulation emptySimulation;
    GISASSimulation constructedSimulation;
    OutputData<double> test_data;
};


GISASSimulationTest::GISASSimulationTest()
{
    test_data.addAxis(BornAgain::PHI_AXIS_NAME, 10, 0., 10.);
    test_data.addAxis("theta_f", 20, 0., 20.);
    test_data.setAllTo(2.0);
}

GISASSimulationTest::~GISASSimulationTest()
{
}


TEST_F(GISASSimulationTest, SimulationInitialState)
{
    // TODO FIXME revise
//    EXPECT_EQ( nullptr, emptySimulation.getSample());
//    EXPECT_EQ( size_t(1), emptySimulation.getOutputData()->getAllocatedSize());
//    EXPECT_EQ( size_t(0), emptySimulation.getOutputData()->getRank());
//    EXPECT_TRUE(emptySimulation.getOutputData()->getRank() == emptySimulation.getInstrument().getDetectorDimension() );
}

TEST_F(GISASSimulationTest, SimulationConstruction)
{
    // TODO FIXME revise
//    EXPECT_FALSE( constructedSimulation.getOutputData()->hasSameShape(test_data));
//    constructedSimulation.setDetectorParameters(test_data);
//    EXPECT_TRUE( constructedSimulation.getOutputData()->hasSameShape(test_data));
//    EXPECT_EQ( constructedSimulation.getOutputData()->totalSum(), 0.);
//    MultiLayer ml;
//    Layer layer;
//    ml.addLayer(layer);
//    constructedSimulation.setSample(ml);
//    EXPECT_EQ( size_t(1), dynamic_cast<MultiLayer*>(constructedSimulation.getSample())->getNumberOfLayers());
}

TEST_F(GISASSimulationTest, SimulationInitialStateOfClone)
{
    // TODO FIXME revise
//    GISASSimulation *emptyClonedSimulation = emptySimulation.clone();
//    EXPECT_EQ( nullptr, emptyClonedSimulation->getSample());
//    EXPECT_EQ( size_t(1), emptyClonedSimulation->getOutputData()->getAllocatedSize());
//    EXPECT_EQ( size_t(0), emptyClonedSimulation->getOutputData()->getRank());
//    EXPECT_TRUE(emptyClonedSimulation->getOutputData()->getRank() == emptyClonedSimulation->getInstrument().getDetector()->getDimension() );
//    EXPECT_EQ( emptyClonedSimulation->getInstrument().getBeamIntensity(), 0.);
//    delete emptyClonedSimulation;
}

TEST_F(GISASSimulationTest, SimulationClone)
{
    // TODO FIXME revise
//    EXPECT_EQ(1,1);
//    GISASSimulation *originalSimulation = new GISASSimulation();
//    originalSimulation->setBeamIntensity(10);
//    originalSimulation->setDetectorParameters(test_data);
//    GISASSimulation *clonedSimulation = originalSimulation->clone();
//    delete originalSimulation;

//    EXPECT_TRUE( clonedSimulation->getOutputData()->hasSameShape(test_data));
//    EXPECT_EQ( clonedSimulation->getInstrument().getBeamIntensity(), 10.);
//    EXPECT_TRUE( nullptr == clonedSimulation->getSample());
//    clonedSimulation->prepareSimulation();
//    EXPECT_TRUE( nullptr == clonedSimulation->getSample());

//    delete clonedSimulation;
}

#endif // GISASSIMULATIONTEST_H
