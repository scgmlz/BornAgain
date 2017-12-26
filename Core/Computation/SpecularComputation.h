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
#include "IFresnelMap.h"
#include "Complex.h"
#include "SimulationOptions.h"
#include "SpecularComputationTerm.h"

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
    template <class Iter>
    explicit SpecularComputation(const MultiLayer& multilayer,
                                 const SimulationOptions& options,
                                 const std::shared_ptr<ProgressHandler>& progress,
                                 Iter begin_it, Iter end_it)
        : IComputation(options, progress, std::make_unique<IterHandler<Iter>>(begin_it, end_it),
                       multilayer)
    {
        init();
    }

    virtual ~SpecularComputation();

    void run();

private:
    void init();
    virtual void runProtected() override;
    std::unique_ptr<IFresnelMap> createFresnelMap();

    std::unique_ptr<IFresnelMap> mP_fresnel_map;
    std::unique_ptr<SpecularComputationTerm> m_computation_term;
};

#endif /* SPECULARCOMPUTATION_H_ */
