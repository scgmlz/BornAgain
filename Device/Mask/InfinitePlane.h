//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Mask/InfinitePlane.h
//! @brief     Defines class InfinitePlane.
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
#ifndef BORNAGAIN_DEVICE_MASK_INFINITEPLANE_H
#define BORNAGAIN_DEVICE_MASK_INFINITEPLANE_H

#include "Device/Mask/IShape2D.h"

//! The infinite plane is used for masking the entire detector.
//! @ingroup tools

class InfinitePlane : public IShape2D {
public:
    InfinitePlane() : IShape2D("InfinitePlane") {}
    InfinitePlane* clone() const { return new InfinitePlane(); }

    bool contains(double, double) const { return true; }
    bool contains(const Bin1D&, const Bin1D&) const { return true; }
};

#endif // BORNAGAIN_DEVICE_MASK_INFINITEPLANE_H
#endif // USER_API
