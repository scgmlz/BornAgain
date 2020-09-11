// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/MPISimulation.cpp
//! @brief     Implements class MPISimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Core/Simulation/MPISimulation.h"

#ifdef BORNAGAIN_MPI

#include "Core/Simulation/Simulation.h"
#include <mpi.h>

// -----------------------------------------------------------------------------
// MPI support
// -----------------------------------------------------------------------------

void MPISimulation::runSimulation(Simulation* simulation)
{
    MPI_Status st;

    int world_size(0), world_rank(0);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_size == 1) {
        simulation->runSimulation();
        return;
    }

    SimulationOptions& sim_options = simulation->getOptions();
    unsigned n_threads = sim_options.getNumberOfThreads();
    unsigned n_batches = world_size;
    unsigned current_batch = world_rank;
    ThreadInfo info;
    info.n_threads = n_threads;
    info.n_batches = n_batches;
    info.current_batch = current_batch;
    sim_options.setThreadInfo(info);
    simulation->runSimulation();

    if (world_rank != 0) {
        std::vector<double> raw = simulation->rawResults();
        MPI_Send(&raw[0], raw.size(), MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    if (world_rank == 0) {
        auto sum_of_raw = simulation->rawResults();
        size_t total_size = sum_of_raw.size();
        for (int i = 1; i < world_size; ++i) {
            std::vector<double> raw(total_size);
            MPI_Recv(&raw[0], total_size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &st);
            for (size_t i_raw = 0; i_raw < total_size; ++i_raw)
                sum_of_raw[i_raw] += raw[i_raw];
        }
        simulation->setRawResults(sum_of_raw);
    }
}
#else

#include <stdexcept>

// -----------------------------------------------------------------------------
// No MPI support
// -----------------------------------------------------------------------------

void MPISimulation::runSimulation(Simulation* /* simulation */)
{
    throw std::runtime_error(
        "MPISimulation::runSimulation() -> Error! Can't run MPI simulation. "
        "The package was compiled without MPI support (compile with -DBORNAGAIN_MPI=ON)");
}
#endif // BORNAGAIN_MPI
