// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Lattice/Lattice2DParameters.h
//! @brief     Defines class Lattice2DParameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef LATTICE2DPARAMETERS_H
#define LATTICE2DPARAMETERS_H

#include <cmath>

//! Additional parameters for 2D lattice.
//! @ingroup samples

class Lattice2DParameters
{
public:
    Lattice2DParameters() : m_length_1(0), m_length_2(0), m_angle(0), m_xi(0) {}

    double getUnitCellArea() const;

    double m_length_1, m_length_2;
    double m_angle;
    double m_xi;
};

#endif // LATTICE2DPARAMETERS_H
