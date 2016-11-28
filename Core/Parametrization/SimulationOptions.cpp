// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/SimulationOptions.cpp
//! @brief     Implements class SimulationOptions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SimulationOptions.h"
#include <thread>

SimulationOptions::SimulationOptions()
    : m_mc_integration(false)
    , m_include_specular(false)
    , m_mc_points(1)
{
    m_thread_info.n_threads = getHardwareConcurrency();
}

bool SimulationOptions::isIntegrate() const
{
    return m_mc_integration && m_mc_points>1;
}

void SimulationOptions::setMonteCarloIntegration(bool flag, size_t mc_points)
{
    m_mc_integration = flag;
    m_mc_points = mc_points;
}

void SimulationOptions::setNumberOfThreads(int nthreads)
{
    if(nthreads == 0)
        m_thread_info.n_threads = (int)std::thread::hardware_concurrency();
    else if(nthreads > 0)
        m_thread_info.n_threads = nthreads;
    else
        m_thread_info.n_threads = 1;
}

int SimulationOptions::getNumberOfThreads() const
{
    return m_thread_info.n_threads;
}

void SimulationOptions::setNumberOfBatches(int nbatches)
{
    m_thread_info.n_batches = nbatches;
}

int SimulationOptions::getNumberOfBatches() const
{
    return m_thread_info.n_batches;
}

int SimulationOptions::getCurrentBatch() const
{
    return m_thread_info.current_batch;
}

int SimulationOptions::getHardwareConcurrency() const
{
    return (int)std::thread::hardware_concurrency();
}
