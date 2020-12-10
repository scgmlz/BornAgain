//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Shapes/Box.h
//! @brief     Defines class Box.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SHAPES_BOX_H
#define BORNAGAIN_SAMPLE_SHAPES_BOX_H

#include "Sample/Shapes/IShape.h"

class Box : public IShape {
public:
    Box(double length, double width, double height);
    ~Box();
};

#endif // BORNAGAIN_SAMPLE_SHAPES_BOX_H
#endif // USER_API
