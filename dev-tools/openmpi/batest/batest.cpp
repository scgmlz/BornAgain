#include <iostream>
#include "SimulationFactory.h"
#include "IntensityDataFunctions.h"
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);


    std::cout << "Hello World" << std::endl;

    SimulationFactory sim_registry;
    Simulation *simulation = sim_registry.createItem("isgisaxs01");

    simulation->runOMPISimulation();


    // check
    int world_size(0), world_rank(0);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if(world_rank ==0) {
        OutputData<double> *result = simulation->getOutputData()->clone();

        simulation->runSimulation();
        OutputData<double> *reference = simulation->getOutputData()->clone();

        double diff = OutputDataFunctions::GetDifference(*result,*reference);
        std::cout << " Difference:" << diff << std::endl;
    }


    MPI_Finalize();

    return 0;
}
