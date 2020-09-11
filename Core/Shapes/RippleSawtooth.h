// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Shapes/RippleSawtooth.h
//! @brief     Defines class RippleSawtooth.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SHAPES_RIPPLESAWTOOTH_H
#define BORNAGAIN_CORE_SHAPES_RIPPLESAWTOOTH_H

#include "Core/Shapes/IShape.h"

class RippleSawtooth : public IShape
{
public:
    RippleSawtooth(double length, double width, double height, double asymmetry);
    ~RippleSawtooth();
};

#endif // BORNAGAIN_CORE_SHAPES_RIPPLESAWTOOTH_H
