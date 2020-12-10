//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Fresnel/IFresnelMap.cpp
//! @brief     Implements interface IFresnelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Fresnel/IFresnelMap.h"
#include "Sample/Slice/Slice.h"

IFresnelMap::IFresnelMap(std::unique_ptr<ISpecularStrategy> strategy)
    : m_use_cache(true), m_Strategy(std::move(strategy)) {}

void IFresnelMap::setSlices(const std::vector<Slice>& slices) {
    m_slices = slices;
}

const std::vector<Slice>& IFresnelMap::slices() const {
    return m_slices;
}

IFresnelMap::~IFresnelMap() = default;

void IFresnelMap::disableCaching() {
    m_use_cache = false;
}
