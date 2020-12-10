#include "Core/Simulation/GISASSimulation.h"
#include "Sample/Multilayer/MultiLayer.h"
#include "Sample/SampleBuilderEngine/ISampleBuilder.h"
#include "Tests/GTestWrapper/google_test.h"

class GISASSimulationTest : public ::testing::Test {};

TEST_F(GISASSimulationTest, SimulationInitialState) {
    GISASSimulation simulation;
    EXPECT_EQ(nullptr, simulation.sample());
    EXPECT_EQ(0u, simulation.intensityMapSize());
    EXPECT_THROW(simulation.result(), std::runtime_error);
    EXPECT_EQ(1u, simulation.getChildren().size());
}

TEST_F(GISASSimulationTest, SimulationConstruction) {
    GISASSimulation simulation;
    simulation.setSample(MultiLayer());
    EXPECT_NE(nullptr, simulation.sample());
    EXPECT_EQ(0u, simulation.intensityMapSize());
    EXPECT_THROW(simulation.result(), std::runtime_error);
    EXPECT_EQ(2u, simulation.getChildren().size());

    simulation.setDetectorParameters(10, -2.0, 2.0, 20, 0.0, 2.0);
    EXPECT_NE(nullptr, simulation.sample());
    EXPECT_EQ(200u, simulation.intensityMapSize());
    EXPECT_NO_THROW(simulation.result());
    EXPECT_EQ(2u, simulation.getChildren().size());
}

TEST_F(GISASSimulationTest, SimulationClone1) {
    GISASSimulation simulation;
    auto p_clone = simulation.clone();
    EXPECT_EQ(nullptr, p_clone->sample());
    EXPECT_EQ(0u, p_clone->intensityMapSize());
    EXPECT_THROW(p_clone->result(), std::runtime_error);
    EXPECT_EQ(1u, p_clone->getChildren().size());
    delete p_clone;
}

TEST_F(GISASSimulationTest, SimulationClone2) {
    GISASSimulation simulation;
    simulation.setSample(MultiLayer());
    simulation.setDetectorParameters(10, -2.0, 2.0, 20, 0.0, 2.0);
    auto p_clone = simulation.clone();
    EXPECT_NE(nullptr, p_clone->sample());
    EXPECT_EQ(200u, p_clone->intensityMapSize());
    EXPECT_NO_THROW(p_clone->result());
    EXPECT_EQ(2u, p_clone->getChildren().size());
    delete p_clone;
}
