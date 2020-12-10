//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Shapes/RippleSawtooth.h
//! @brief     Defines class RippleSawtooth.
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
#ifndef BORNAGAIN_SAMPLE_SHAPES_RIPPLESAWTOOTH_H
#define BORNAGAIN_SAMPLE_SHAPES_RIPPLESAWTOOTH_H

#include "Sample/Shapes/IShape.h"

class RippleSawtooth : public IShape {
public:
    RippleSawtooth(double length, double width, double height, double asymmetry);
    ~RippleSawtooth();
};

#endif // BORNAGAIN_SAMPLE_SHAPES_RIPPLESAWTOOTH_H
#endif // USER_API
