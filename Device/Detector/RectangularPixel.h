//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/RectangularPixel.h
//! @brief     Defines class RectangularPixel.
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
#ifndef BORNAGAIN_DEVICE_DETECTOR_RECTANGULARPIXEL_H
#define BORNAGAIN_DEVICE_DETECTOR_RECTANGULARPIXEL_H

#include "Base/Pixel/IPixel.h"

//! A pixel in a RectangularDetector.

class RectangularPixel : public IPixel {
public:
    RectangularPixel(const kvector_t& corner_pos, const kvector_t& width, const kvector_t& height);

    RectangularPixel* clone() const override;
    RectangularPixel* createZeroSizePixel(double x, double y) const override;
    kvector_t getK(double x, double y, double wavelength) const override;
    kvector_t getPosition(double x, double y) const;
    double integrationFactor(double x, double y) const override;
    double solidAngle() const override;

private:
    kvector_t normalizeLength(const kvector_t direction, double length) const;
    double calculateSolidAngle() const;

    const kvector_t m_corner_pos;
    const kvector_t m_width;
    const kvector_t m_height;
    const kvector_t m_normal;
    mutable double m_solid_angle;
};

#endif // BORNAGAIN_DEVICE_DETECTOR_RECTANGULARPIXEL_H
#endif // USER_API
