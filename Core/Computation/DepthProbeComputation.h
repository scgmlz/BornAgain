// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DepthProbeComputation.h
//! @brief     Declares class DepthProbeComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_COMPUTATION_DEPTHPROBECOMPUTATION_H
#define BORNAGAIN_CORE_COMPUTATION_DEPTHPROBECOMPUTATION_H

#include "Core/Computation/DepthProbeComputationTerm.h"
#include "Core/Computation/IComputation.h"
#include "Core/Parametrization/SimulationOptions.h"

class MultiLayer;

//! Performs a single-threaded depth probe computation with given sample.
//!
//! Controlled by the multi-threading machinery in Simulation::runSingleSimulation().
//!
//! @ingroup algorithms_internal

class DepthProbeComputation : public IComputation
{
    using DepthProbeElementIter = std::vector<DepthProbeElement>::iterator;

public:
    DepthProbeComputation(const MultiLayer& multilayer, const SimulationOptions& options,
                          ProgressHandler& progress, DepthProbeElementIter begin_it,
                          DepthProbeElementIter end_it);
    ~DepthProbeComputation() override;

private:
    void runProtected() override;

    DepthProbeElementIter m_begin_it, m_end_it;
    DepthProbeComputationTerm m_computation_term;
};

#endif // BORNAGAIN_CORE_COMPUTATION_DEPTHPROBECOMPUTATION_H
