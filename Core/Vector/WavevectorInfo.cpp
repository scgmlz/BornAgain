// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vector/WavevectorInfo.cpp
//! @brief     Implements WavevectorInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Vector/WavevectorInfo.h"
#include "Core/Vector/Transform3D.h"

// TODO: can be removed when IFormFactor::volume() is refactored
// (static function is provided to easily track usage of default constructor)
WavevectorInfo WavevectorInfo::GetZeroQ()
{
    return {};
}

WavevectorInfo WavevectorInfo::transformed(const Transform3D& transform) const
{
    return WavevectorInfo(transform.transformed(m_ki), transform.transformed(m_kf),
                          m_vacuum_wavelength);
}

// same as GetZeroQ
WavevectorInfo::WavevectorInfo() : m_ki(1, 0, 0), m_kf(1, 0, 0), m_vacuum_wavelength(1) {}
