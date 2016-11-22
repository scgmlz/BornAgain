// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/IPixelMap.h
//! @brief     Defines interface IPixelMap.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IPIXELMAP_H
#define IPIXELMAP_H

#include "Vectors3D.h"

//! Pure virtual interface pixel maps. A pixel maps describes the geometry of a single pixel.
//! Therefore, different child classes are needed to support different detector geometries.
//! Each pixel has a fixed solid angle. Furthermore, it has functions that map relative
//! coordinates from [0,1]x[0,1] to the wavevector K and the associated weight (integration factor).
//! @ingroup simulation

class IPixelMap
{
public:
    virtual ~IPixelMap() {}

    virtual IPixelMap* clone() const =0;
    virtual IPixelMap* createZeroSizeMap(double x, double y) const =0;
    virtual kvector_t getK(double x, double y, double wavelength) const =0;
    virtual double getIntegrationFactor(double x, double y) const =0;
    virtual double getSolidAngle() const=0;
};

#endif // IPIXELMAP_H
