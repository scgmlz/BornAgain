// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputation.h
//! @brief     Defines class SpecularComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARCOMPUTATION_H_
#define SPECULARCOMPUTATION_H_

#include "IComputation.h"
#include "Complex.h"
#include "SimulationOptions.h"

class IFresnelMap;
class MultiLayer;
struct HomogeneousRegion;
class IComputationTerm;
class SpecularComputationTerm;

//! Performs a single-threaded specular computation with given sample.
//!
//! Controlled by the multi-threading machinery in Simulation::runSingleSimulation().
//!
//! @ingroup algorithms_internal

class SpecularComputation : public IComputation
{
public:
    SpecularComputation(const MultiLayer& multilayer, const SimulationOptions& options,
                        ProgressHandler& progress,
                        std::vector<SimulationElement>::iterator begin_it,
                        std::vector<SimulationElement>::iterator end_it);
    virtual ~SpecularComputation();

private:
    void runProtected() override;
    std::unique_ptr<IFresnelMap> createFresnelMap();

    std::vector<SimulationElement>::iterator m_begin_it, m_end_it; //!< these iterators define the span of detector bins this simulation will work on
    std::unique_ptr<IFresnelMap> mP_fresnel_map;
    std::unique_ptr<SpecularComputationTerm> m_computation_term;
};

#endif /* SPECULARCOMPUTATION_H_ */
