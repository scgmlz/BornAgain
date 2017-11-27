// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputationTerm.h
//! @brief     Defines interface IComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   J. Burle, J. M. Fisher, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPUTATIONTERM_H
#define ICOMPUTATIONTERM_H

#include "SlicedParticle.h"
#include <vector>
#include <map>

class IFresnelMap;
class MultiLayer;
class ProgressHandler;
class SimulationElement;
class SimulationOptions;

//! Computes an independent term of the scattering intensity.
//! Used by DWBAComputation, which adds up all contributions from subclasses
//! of IComputationTerm
//! @ingroup algorithms_internal

class IComputationTerm
{
public:
    IComputationTerm(const MultiLayer* p_multilayer, const IFresnelMap* p_fresnel_map);
    virtual ~IComputationTerm();

    //! Calculate scattering intensity for each SimulationElement
    //! returns false if nothing needed to be calculated
    virtual void eval(ProgressHandler* progress,
                      const std::vector<SimulationElement>::iterator& begin_it,
                      const std::vector<SimulationElement>::iterator& end_it) const =0;

    //! Merges its region map into the given one (notice non-const reference parameter)
    void mergeRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& region_map) const;

protected:
    const MultiLayer* mp_multilayer;
    const IFresnelMap* mp_fresnel_map;
    std::map<size_t, std::vector<HomogeneousRegion>> m_region_map;
};

#endif // ICOMPUTATIONTERM_H
