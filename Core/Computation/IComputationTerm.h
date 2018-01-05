// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputationTerm.h
//! @brief     Defines interface IComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ICOMPUTATIONTERM_H
#define ICOMPUTATIONTERM_H

#include "SlicedParticle.h"
#include <vector>
#include <map>

class IFresnelMap;
class MultiLayer;
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

    //! Calculates scattering intensity for a range of simulation elements.
    template <class Iter>
    void eval(Iter begin, Iter end) const
    {
        if (!checkComputation())
            return;
        for (auto it = begin; it != end; ++it)
            evalSingle(*it);
    }

    //! Merges its region map into the given one (notice non-const reference parameter)
    void mergeRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& region_map) const;

protected:
    //! Calculates scattering intensity for single simulation element.
    virtual void evalSingle(SimulationElement& element) const = 0;
    virtual bool checkComputation() const {return true;}
    const MultiLayer* mp_multilayer;
    const IFresnelMap* mp_fresnel_map;
    std::map<size_t, std::vector<HomogeneousRegion>> m_region_map;
};

#endif // ICOMPUTATIONTERM_H
