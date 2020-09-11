// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/SimulationOptions.cpp
//! @brief     Implements class SimulationOptions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Parametrization/SimulationOptions.h"
#include <stdexcept>
#include <thread>

SimulationOptions::SimulationOptions()
    : m_mc_integration(false), m_include_specular(false), m_use_avg_materials(false), m_mc_points(1)
{
    m_thread_info.n_threads = getHardwareConcurrency();
}

bool SimulationOptions::isIntegrate() const
{
    return m_mc_integration && m_mc_points > 1;
}

void SimulationOptions::setMonteCarloIntegration(bool flag, size_t mc_points)
{
    m_mc_integration = flag;
    m_mc_points = mc_points;
}

void SimulationOptions::setNumberOfThreads(int nthreads)
{
    if (nthreads == 0)
        m_thread_info.n_threads = getHardwareConcurrency();
    else if (nthreads > 0)
        m_thread_info.n_threads = nthreads;
    else
        m_thread_info.n_threads = 1;
}

unsigned SimulationOptions::getNumberOfThreads() const
{
    if (m_thread_info.n_threads < 1)
        throw std::runtime_error("Error in SimulationOptions::getNumberOfThreads: Number of "
                                 "threads must be positive");
    return m_thread_info.n_threads;
}

void SimulationOptions::setNumberOfBatches(int nbatches)
{
    if (nbatches < 1)
        throw std::runtime_error("Error in SimulationOptions::setNumberOfBatches: Number of "
                                 "batches must be positive");
    m_thread_info.n_batches = nbatches;
}

unsigned SimulationOptions::getNumberOfBatches() const
{
    if (m_thread_info.n_batches < 1)
        throw std::runtime_error("Error in SimulationOptions::getNumberOfBatches: Number of "
                                 "batches must be positive");
    return m_thread_info.n_batches;
}

unsigned SimulationOptions::getCurrentBatch() const
{
    if (m_thread_info.current_batch >= getNumberOfBatches())
        throw std::runtime_error(
            "Error in SimulationOptions::getCurrentBatch: current batch is out of range");
    return m_thread_info.current_batch;
}

unsigned SimulationOptions::getHardwareConcurrency() const
{
    return std::thread::hardware_concurrency();
}
