// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice2DParameters.cpp
//! @brief     Implements class Lattice2DParameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Lattice2DParameters.h"

double Lattice2DParameters::getUnitCellArea() const
{
    return std::abs(m_length_1 * m_length_2 * std::sin(m_angle));
}
