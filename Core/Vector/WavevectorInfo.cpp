// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vector/WavevectorInfo.cpp
//! @brief     Implements WavevectorInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "WavevectorInfo.h"
#include "Transform3D.h"

WavevectorInfo WavevectorInfo::transformed(const Transform3D& transform) const
{
    return WavevectorInfo(transform.transformed(m_ki), transform.transformed(m_kf));
}
