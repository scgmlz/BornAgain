//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Pixel/IPixel.h
//! @brief     Defines and implements interface IPixel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_BASE_PIXEL_IPIXEL_H
#define BORNAGAIN_BASE_PIXEL_IPIXEL_H

#include "Base/Vector/Vectors3D.h"

//! Interface for a function that maps [0,1]x[0,1] to the kvectors in a pixel.
//! Abstract base class for SphericalPixel and RectangularPixel.
//! @ingroup detector

class IPixel {
public:
    virtual ~IPixel() {}

    virtual IPixel* clone() const = 0;
    virtual IPixel* createZeroSizePixel(double x, double y) const = 0;
    virtual kvector_t getK(double x, double y, double wavelength) const = 0;
    virtual double integrationFactor(double x, double y) const = 0;
    virtual double solidAngle() const = 0;
};

#endif // BORNAGAIN_BASE_PIXEL_IPIXEL_H
#endif // USER_API
