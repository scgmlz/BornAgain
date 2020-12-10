//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ParticleLayoutComputation.h
//! @brief     Defines class ParticleLayoutComputation.
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
#ifndef BORNAGAIN_CORE_COMPUTATION_PARTICLELAYOUTCOMPUTATION_H
#define BORNAGAIN_CORE_COMPUTATION_PARTICLELAYOUTCOMPUTATION_H

#include "Sample/Particle/HomogeneousRegion.h"
#include <map>
#include <memory>
#include <vector>

class IInterferenceFunctionStrategy;
class ProcessedLayout;
class SimulationElement;
class SimulationOptions;

//! Computes the scattering contribution from one particle layout.
//! Used by DWBAComputation.
//! @ingroup algorithms_internal

class ParticleLayoutComputation final {
public:
    ParticleLayoutComputation(const ProcessedLayout& layout, const SimulationOptions& options,
                              bool polarized);
    ~ParticleLayoutComputation();

    void compute(SimulationElement& elem) const;

    //! Merges its region map into the given one (notice non-const reference parameter)
    void mergeRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& region_map) const;

private:
    const ProcessedLayout& m_layout;
    const std::map<size_t, std::vector<HomogeneousRegion>> m_region_map;
    std::unique_ptr<const IInterferenceFunctionStrategy> m_interference_function_strategy;
};

#endif // BORNAGAIN_CORE_COMPUTATION_PARTICLELAYOUTCOMPUTATION_H
#endif // USER_API
