//  ************************************************************************************************
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
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_CORE_COMPUTATION_SPECULARCOMPUTATION_H
#define BORNAGAIN_CORE_COMPUTATION_SPECULARCOMPUTATION_H

#include "Core/Computation/IComputation.h"

class MultiLayer;
class SpecularComputationTerm;
class SpecularSimulationElement;

//! Performs a single-threaded specular computation with given sample.
//!
//! Controlled by the multi-threading machinery in ISimulation::runSingleSimulation().
//!
//! @ingroup algorithms_internal

class SpecularComputation : public IComputation {
    using SpecularElementIter = std::vector<SpecularSimulationElement>::iterator;

public:
    SpecularComputation(const MultiLayer& multilayer, const SimulationOptions& options,
                        ProgressHandler& progress, SpecularElementIter begin_it,
                        SpecularElementIter end_it);
    ~SpecularComputation() override;

private:
    void runProtected() override;

    //! these iterators define the span of detector bins this simulation will work on
    const SpecularElementIter m_begin_it, m_end_it;
    mutable std::unique_ptr<SpecularComputationTerm> m_computation_term;
};

#endif // BORNAGAIN_CORE_COMPUTATION_SPECULARCOMPUTATION_H
#endif // USER_API
