// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/SlicedFormFactorList.h
//! @brief     Defines class SlicedFormFactorList.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SLICEDFORMFACTORLIST_H
#define SLICEDFORMFACTORLIST_H

#include "HomogeneousRegion.h"
#include "IFormFactor.h"
#include <map>
#include <memory>

class MultiLayer;
class Slice;

//! Class that contains and owns a list of form factors and the index of their containing layer.
//! This class also handles the slicing of form factors if they cross layer interfaces.
//!
//! @ingroup intern

class SlicedFormFactorList
{
public:
    SlicedFormFactorList() = default;
    SlicedFormFactorList(SlicedFormFactorList&& other) = default;
    SlicedFormFactorList& operator=(SlicedFormFactorList&& other) = default;
    ~SlicedFormFactorList() = default;

    static SlicedFormFactorList CreateSlicedFormFactors(const IParticle& particle,
                                                        const std::vector<Slice>& slices,
                                                        double z_ref);

    size_t size() const;

    std::pair<const IFormFactor*, size_t> operator[](size_t index) const;

    std::map<size_t, std::vector<HomogeneousRegion>> regionMap() const;

private:
    void addParticle(IParticle& particle, const std::vector<Slice>& slices, double z_ref);
    std::vector<std::pair<std::unique_ptr<IFormFactor>, size_t>> m_ff_list;
    std::map<size_t, std::vector<HomogeneousRegion>> m_region_map;
};

#endif // SLICEDFORMFACTORLIST_H
