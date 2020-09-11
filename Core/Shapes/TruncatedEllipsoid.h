// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/TruncatedEllipsoid.h
//! @brief     Defines class TruncatedEllipsoid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SHAPES_TRUNCATEDELLIPSOID_H
#define BORNAGAIN_CORE_SHAPES_TRUNCATEDELLIPSOID_H

#include "Core/Shapes/IShape.h"

class TruncatedEllipsoid : public IShape
{
public:
    TruncatedEllipsoid(double r_x, double r_y, double r_z, double height, double dh);
    ~TruncatedEllipsoid();
};

#endif // BORNAGAIN_CORE_SHAPES_TRUNCATEDELLIPSOID_H
