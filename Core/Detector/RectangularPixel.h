// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/RectangularPixel.h
//! @brief     Defines class RectangularPixel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_DETECTOR_RECTANGULARPIXEL_H
#define BORNAGAIN_CORE_DETECTOR_RECTANGULARPIXEL_H

#include "Core/Binning/IPixel.h"

//! A pixel in a RectangularDetector.

class BA_CORE_API_ RectangularPixel : public IPixel
{
public:
    RectangularPixel(kvector_t corner_pos, kvector_t width, kvector_t height);

    RectangularPixel* clone() const override;
    RectangularPixel* createZeroSizePixel(double x, double y) const override;
    kvector_t getK(double x, double y, double wavelength) const override;
    kvector_t getPosition(double x, double y) const;
    double getIntegrationFactor(double x, double y) const override;
    double getSolidAngle() const override;

private:
    kvector_t normalizeLength(const kvector_t direction, double length) const;
    double calculateSolidAngle() const;
    kvector_t m_corner_pos;
    kvector_t m_width;
    kvector_t m_height;
    double m_solid_angle;
    kvector_t m_normal;
};

#endif // BORNAGAIN_CORE_DETECTOR_RECTANGULARPIXEL_H
