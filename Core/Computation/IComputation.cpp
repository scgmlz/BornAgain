// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputation.cpp
//! @brief     Implements interface IComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/IComputation.h"
#include "Core/Computation/ProcessedSample.h"
#include "Core/Computation/ProgressHandler.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/SimulationElement/SimulationElement.h"

IComputation::IComputation(const MultiLayer& sample, const SimulationOptions& options,
                           ProgressHandler& progress)
    : m_sim_options(options), mp_progress(&progress),
      mP_processed_sample(std::make_unique<ProcessedSample>(sample, options))
{
}

IComputation::~IComputation() = default;

void IComputation::run()
{
    m_status.setRunning();
    try {
        runProtected();
        m_status.setCompleted();
    } catch (const std::exception& ex) {
        m_status.setErrorMessage(std::string(ex.what()));
        m_status.setFailed();
    }
}
