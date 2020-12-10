//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Detector/RectangularPixel.cpp
//! @brief     Implements class RectangularPixel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Detector/RectangularPixel.h"
#include "Base/Math/Constants.h"

RectangularPixel::RectangularPixel(const kvector_t& corner_pos, const kvector_t& width,
                                   const kvector_t& height)
    : m_corner_pos(std::move(corner_pos))
    , m_width(std::move(width))
    , m_height(std::move(height))
    , m_normal(width.cross(height)) {
    // TODO URGENT: why allow solid angle <=0 ??
    auto solid_angle_value = calculateSolidAngle();
    m_solid_angle = solid_angle_value <= 0.0 ? 1.0 : solid_angle_value;
}

RectangularPixel* RectangularPixel::clone() const {
    return new RectangularPixel(m_corner_pos, m_width, m_height);
}

RectangularPixel* RectangularPixel::createZeroSizePixel(double x, double y) const {
    return new RectangularPixel(getPosition(x, y), kvector_t(), kvector_t());
}

kvector_t RectangularPixel::getK(double x, double y, double wavelength) const {
    kvector_t direction = getPosition(x, y);
    double length = M_TWOPI / wavelength;
    return normalizeLength(direction, length);
}

kvector_t RectangularPixel::getPosition(double x, double y) const {
    return m_corner_pos + x * m_width + y * m_height;
}

double RectangularPixel::integrationFactor(double x, double y) const {
    if (m_solid_angle == 0.0)
        return 1.0;
    kvector_t position = getPosition(x, y);
    double length = position.mag();
    return std::abs(position.dot(m_normal)) / std::pow(length, 3) / m_solid_angle;
}

double RectangularPixel::solidAngle() const {
    return m_solid_angle;
}

kvector_t RectangularPixel::normalizeLength(const kvector_t direction, double length) const {
    return direction.unit() * length;
}

double RectangularPixel::calculateSolidAngle() const {
    kvector_t position = getPosition(0.5, 0.5);
    double length = position.mag();
    return std::abs(position.dot(m_normal)) / std::pow(length, 3);
}
