// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DepthProbeComputation.cpp
//! @brief     Implements class SpecularComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/DepthProbeComputation.h"
#include "Core/Computation/ProgressHandler.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/SimulationElement/DepthProbeElement.h"

static_assert(std::is_copy_constructible<DepthProbeComputation>::value == false,
              "DepthProbeComputation should not be copy constructible");
static_assert(std::is_copy_assignable<DepthProbeComputation>::value == false,
              "DepthProbeComputation should not be copy assignable");

DepthProbeComputation::DepthProbeComputation(const MultiLayer& multilayer,
                                             const SimulationOptions& options,
                                             ProgressHandler& progress,
                                             DepthProbeElementIter begin_it,
                                             DepthProbeElementIter end_it)
    : IComputation(multilayer, options, progress), m_begin_it(begin_it), m_end_it(end_it),
      m_computation_term(mP_processed_sample.get())
{
}

DepthProbeComputation::~DepthProbeComputation() = default;

void DepthProbeComputation::runProtected()
{
    if (!mp_progress->alive())
        return;
    m_computation_term.setProgressHandler(mp_progress);
    for (auto it = m_begin_it; it != m_end_it; ++it) {
        m_computation_term.compute(*it);
    }
}
