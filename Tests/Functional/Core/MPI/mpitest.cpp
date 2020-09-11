#include <mpi.h>

#include "Core/InputOutput/IntensityDataIOFactory.h"
#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Simulation/SimulationFactory.h"
#include "Core/StandardSamples/SampleBuilderFactory.h"

#include <iostream>

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int world_size(0), world_rank(0);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    SimulationFactory sim_factory;
    Simulation* p_simulation = sim_factory.createItem("BasicGISAS");
    SampleBuilderFactory sample_factory;
    const std::unique_ptr<MultiLayer> P_sample(
        sample_factory.createSample("CylindersInDWBABuilder"));
    p_simulation->setSample(*P_sample);

    // make backup of original simulation options
    SimulationOptions sim_options;
    if (world_rank == 0) {
        sim_options = p_simulation->getOptions();
    }

    std::cout << "Running MPI simulation: rank " << world_rank << " of " << world_size << std::endl;
    p_simulation->runMPISimulation();

    if (world_rank == 0) {
        auto result = p_simulation->result();

        // restore original simulation options
        p_simulation->setOptions(sim_options);

        std::cout << "Running normal simulation..." << std::endl;
        p_simulation->runSimulation();
        auto reference = p_simulation->result();

        double diff = IntensityDataFunctions::RelativeDifference(result, reference);
        std::cout << "Difference: " << diff << std::endl;
    }
    MPI_Finalize();
    return 0;
}
