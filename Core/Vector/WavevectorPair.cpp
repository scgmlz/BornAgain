// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Vector/WavevectorPair.cpp
//! @brief     Implements WavevectorPair.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "WavevectorPair.h"
#include "Transform3D.h"

//! Returns a copy with modified z components.

WavevectorPair WavevectorPair::newZZ(complex_t kiz, complex_t kfz) const
{
    return { { m_ki.x(), m_ki.y(), kiz }, { m_kf.x(), m_kf.y(), kfz } };
}

WavevectorPair WavevectorPair::transformed(const Transform3D& transform) const
{
    return WavevectorPair(transform.transformed(m_ki), transform.transformed(m_kf));
}
