#include "Core/Simulation/GISASSimulation.h"
#include "Core/Beam/Beam.h"
#include "Core/Intensity/OutputData.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Multilayer/Layer.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Tests/GTestWrapper/google_test.h"
#include <cmath>
#include <memory>

class GISASSimulationTest : public ::testing::Test
{
protected:
    GISASSimulation m_simulation;
};

TEST_F(GISASSimulationTest, SimulationInitialState)
{
    EXPECT_EQ(nullptr, m_simulation.sample());
    EXPECT_EQ(0u, m_simulation.intensityMapSize());
    EXPECT_THROW(m_simulation.result(), std::runtime_error);
    EXPECT_EQ(1u, m_simulation.getChildren().size());
}

TEST_F(GISASSimulationTest, SimulationConstruction)
{
    MultiLayer multi_layer;
    GISASSimulation simulation(multi_layer);
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

TEST_F(GISASSimulationTest, SimulationClone)
{
    auto p_clone = m_simulation.clone();
    EXPECT_EQ(nullptr, p_clone->sample());
    EXPECT_EQ(0u, p_clone->intensityMapSize());
    EXPECT_THROW(p_clone->result(), std::runtime_error);
    EXPECT_EQ(1u, p_clone->getChildren().size());
    delete p_clone;

    MultiLayer multi_layer;
    GISASSimulation simulation(multi_layer);
    simulation.setDetectorParameters(10, -2.0, 2.0, 20, 0.0, 2.0);
    p_clone = simulation.clone();
    EXPECT_NE(nullptr, p_clone->sample());
    EXPECT_EQ(200u, p_clone->intensityMapSize());
    EXPECT_NO_THROW(p_clone->result());
    EXPECT_EQ(2u, p_clone->getChildren().size());
    delete p_clone;
}
