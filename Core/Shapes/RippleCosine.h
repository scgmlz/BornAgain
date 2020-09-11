// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/RippleCosine.h
//! @brief     Defines class RippleCosine.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SHAPES_RIPPLECOSINE_H
#define BORNAGAIN_CORE_SHAPES_RIPPLECOSINE_H

#include "Core/Shapes/IShape.h"

class RippleCosine : public IShape
{
public:
    RippleCosine(double length, double width, double height);
    ~RippleCosine();
};

#endif // BORNAGAIN_CORE_SHAPES_RIPPLECOSINE_H
