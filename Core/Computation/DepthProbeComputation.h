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

#ifndef DEPTHPROBECOMPUTATION_H
#define DEPTHPROBECOMPUTATION_H

#include "IComputation.h"
#include "Complex.h"
#include "SimulationOptions.h"
#include "DepthProbeComputationTerm.h"

class IFresnelMap;
class MultiLayer;
struct HomogeneousRegion;

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
    virtual ~DepthProbeComputation();

private:
    void runProtected() override;
    std::unique_ptr<IFresnelMap> createFresnelMap();

    DepthProbeElementIter m_begin_it, m_end_it;
    std::unique_ptr<IFresnelMap> mP_fresnel_map;
    DepthProbeComputationTerm m_computation_term;
};

#endif // DEPTHPROBECOMPUTATION_H
