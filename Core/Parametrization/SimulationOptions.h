// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/SimulationOptions.h
//! @brief     Defines class SimulationOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARAMETRIZATION_SIMULATIONOPTIONS_H
#define BORNAGAIN_CORE_PARAMETRIZATION_SIMULATIONOPTIONS_H

#include "Core/Parametrization/ThreadInfo.h"
#include <cstddef>

using std::size_t;

//! Collect the different options for simulation.
//! @ingroup simulation
//! @ref SimulationOptions

class BA_CORE_API_ SimulationOptions
{
public:
    SimulationOptions();

    bool isIntegrate() const;
    size_t getMcPoints() const { return m_mc_points; }

    //! @brief Enables/disables MonetCarlo integration
    //! @param flag If true, MonteCarlo integration will be used, otherwise analytical calculations
    //! @param mc_points Number of points for MonteCarlo integrator
    void setMonteCarloIntegration(bool flag = true, size_t mc_points = 50);

    //! @brief Sets number of threads to use during the simulation (0 - take the default value from
    //! the hardware)
    void setNumberOfThreads(int nthreads);

    unsigned getNumberOfThreads() const;

    //! @brief Sets number of batches to split
    void setNumberOfBatches(int nbatches);

    unsigned getNumberOfBatches() const;

    unsigned getCurrentBatch() const;

    //! @brief Sets the batch and thread information to be used
    void setThreadInfo(const ThreadInfo& thread_info) { m_thread_info = thread_info; }

    unsigned getHardwareConcurrency() const;

    void setIncludeSpecular(bool include_specular) { m_include_specular = include_specular; }

    bool includeSpecular() const { return m_include_specular; }

    void setUseAvgMaterials(bool use_avg_materials) { m_use_avg_materials = use_avg_materials; }

    bool useAvgMaterials() const { return m_use_avg_materials; }

private:
    bool m_mc_integration;
    bool m_include_specular;
    bool m_use_avg_materials;
    size_t m_mc_points;
    ThreadInfo m_thread_info;
};

#endif // BORNAGAIN_CORE_PARAMETRIZATION_SIMULATIONOPTIONS_H
