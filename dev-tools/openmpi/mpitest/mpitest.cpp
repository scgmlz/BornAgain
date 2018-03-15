#include <mpi.h>

#include <iostream>
#include "MultiLayer.h"
#include "SampleBuilderFactory.h"
#include "SimulationFactory.h"
#include "IntensityDataFunctions.h"

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int world_size(0), world_rank(0);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    std::cout << "MPI world size: " << world_size << std::endl;
    std::cout << "MPI world rank: " << world_rank << std::endl;
    std::cout << std::endl;

    SimulationFactory sim_factory;
    Simulation *p_simulation = sim_factory.createItem("BasicGISAS");
    SampleBuilderFactory sample_factory;
    const std::unique_ptr<MultiLayer> P_sample(
                sample_factory.createSample("CylindersInDWBABuilder"));
    p_simulation->setSample(*P_sample);

    std::cout << "Running a MPI simulation..." << std::endl;
    p_simulation->runOMPISimulation();

    if(world_rank ==0) {
        auto result = p_simulation->result();

        std::cout << "Running normal simulation..." << std::endl;
        p_simulation->runSimulation();
        auto reference = p_simulation->result();

        double diff = IntensityDataFunctions::RelativeDifference(result, reference);
        std::cout << "Difference: " << diff << std::endl;
    }
    MPI_Finalize();

    return 0;
}
