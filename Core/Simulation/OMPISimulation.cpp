// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      unused/OMPISimulation.cpp
//! @brief     Implements class OMPISimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OMPISimulation.h"

#ifdef BORNAGAIN_OPENMPI
#include <mpi.h>
#include "Simulation.h"
// -----------------------------------------------------------------------------
// OpenMPI support
// -----------------------------------------------------------------------------

void OMPISimulation::runSimulation(Simulation* simulation)
{
    MPI_Status st;

    int world_size(0), world_rank(0);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if(world_size == 1) {
        simulation->runSimulation();
        return;
    }

    if(world_rank != 0) {
        SimulationOptions sim_options = simulation->getOptions();
        unsigned n_threads = sim_options.getNumberOfThreads();
        unsigned n_batches = world_size - 1;
        unsigned current_batch = world_rank - 1;
        ThreadInfo info;
        info.n_threads = n_threads;
        info.n_batches = n_batches;
        info.current_batch = current_batch;
        sim_options.setThreadInfo(info);
        simulation->runSimulation();

        std::vector<double> raw = simulation->result().data()->getRawDataVector();
        MPI_Send(&raw[0], raw.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    if(world_rank == 0) {
        size_t total_size = simulation->numberOfSimulationElements();
        std::vector<double> sum_of_raw;
        sum_of_raw.resize(total_size, 0.0);
        for(int i=1; i<world_size; ++i) {
            std::vector<double> raw;
            raw.resize(total_size, 0.0);
            MPI_Recv(&raw[0], total_size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &st);
            for(size_t i_raw=0; i_raw<total_size; ++i_raw)
                sum_of_raw[i_raw] += raw[i_raw];
        }
        simulation->setRawResultVector(sum_of_raw);
    }
}
#else
// -----------------------------------------------------------------------------
// No OpenMPI support
// -----------------------------------------------------------------------------

void OMPISimulation::runSimulation(Simulation* /* simulation */)
{
    throw Exceptions::RuntimeErrorException(
        "OMPISimulation::runSimulation() -> Error! Can't run OpenMPI simulation. "
        "The package was compiled without OpenMPI support (compile with -DBORNAGAIN_OPENMPI=ON)" );
}
#endif
