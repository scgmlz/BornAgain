//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputation.h
//! @brief     Defines interface IComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_CORE_COMPUTATION_ICOMPUTATION_H
#define BORNAGAIN_CORE_COMPUTATION_ICOMPUTATION_H

#include "Core/Computation/ComputationStatus.h"
#include "Sample/RT/SimulationOptions.h"
#include <memory>
#include <vector>

class MultiLayer;
class ProcessedSample;
class ProgressHandler;

//! Interface for a single-threaded computation with given range of SimulationElements
//! and ProgressHandler.
//!
//! Controlled by the multi-threading machinery in ISimulation::runSingleSimulation().
//!
//! @ingroup algorithms_internal

class IComputation {
public:
    IComputation(const MultiLayer& sample, const SimulationOptions& options,
                 ProgressHandler& progress);
    virtual ~IComputation();

    void run();

    bool isCompleted() const { return m_status.isCompleted(); }
    std::string errorMessage() const { return m_status.errorMessage(); }

protected:
    SimulationOptions m_sim_options;
    ProgressHandler* m_progress;
    ComputationStatus m_status;
    std::unique_ptr<ProcessedSample> m_processed_sample;

private:
    virtual void runProtected() = 0;
};

#endif // BORNAGAIN_CORE_COMPUTATION_ICOMPUTATION_H
#endif // USER_API
