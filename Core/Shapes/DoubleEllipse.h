// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/DoubleEllipse.h
//! @brief     Defines class DoubleEllipse.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SHAPES_DOUBLEELLIPSE_H
#define BORNAGAIN_CORE_SHAPES_DOUBLEELLIPSE_H

#include "Core/Shapes/IShape.h"

class DoubleEllipse : public IShape
{
public:
    DoubleEllipse(double r0_x, double r0_y, double z, double rz_x, double rz_y);
    ~DoubleEllipse();
};

#endif // BORNAGAIN_CORE_SHAPES_DOUBLEELLIPSE_H
