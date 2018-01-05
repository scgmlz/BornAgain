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

#include "IComputation.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"

IComputation::IComputation(const SimulationOptions& options,
                           const std::shared_ptr<ProgressHandler>& progress,
                           std::unique_ptr<IIterHandler> iter_holder,
                           const MultiLayer& sample)
    : m_sim_options(options)
    , m_progress(progress)
    , m_iter_holder(std::move(iter_holder))
    , mP_multi_layer(sample.cloneSliced(options.useAvgMaterials()))
{
    if (!mP_multi_layer)
        throw std::runtime_error("Error in IComputation: empty sample passed.");
}

IComputation::~IComputation() = default;

void IComputation::run()
{
    m_status.setRunning();
    try {
        runProtected();
        m_status.setCompleted();
    } catch(const std::exception &ex) {
        m_status.setErrorMessage(std::string(ex.what()));
        m_status.setFailed();
    }
}
