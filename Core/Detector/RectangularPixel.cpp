// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/RectangularPixel.cpp
//! @brief     Implements class RectangularPixel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/RectangularPixel.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Basics/Units.h"
#include "Core/Beam/Beam.h"
#include "Core/Detector/IDetectorResolution.h"
#include "Core/Detector/RegionOfInterest.h"
#include "Core/SimulationElement/SimulationElement.h"

RectangularPixel::RectangularPixel(kvector_t corner_pos, kvector_t width, kvector_t height)
    : m_corner_pos(std::move(corner_pos)), m_width(std::move(width)), m_height(std::move(height))
{
    m_normal = m_width.cross(m_height);
    auto solid_angle_value = calculateSolidAngle();
    m_solid_angle = solid_angle_value <= 0.0 ? 1.0 : solid_angle_value;
}

RectangularPixel* RectangularPixel::clone() const
{
    return new RectangularPixel(m_corner_pos, m_width, m_height);
}

RectangularPixel* RectangularPixel::createZeroSizePixel(double x, double y) const
{
    kvector_t position = m_corner_pos + x * m_width + y * m_height;
    kvector_t null_vector;
    return new RectangularPixel(position, null_vector, null_vector);
}

kvector_t RectangularPixel::getK(double x, double y, double wavelength) const
{
    kvector_t direction = m_corner_pos + x * m_width + y * m_height;
    double length = M_TWOPI / wavelength;
    return normalizeLength(direction, length);
}

kvector_t RectangularPixel::getPosition(double x, double y) const
{
    return m_corner_pos + x * m_width + y * m_height;
}

double RectangularPixel::getIntegrationFactor(double x, double y) const
{
    if (m_solid_angle == 0.0)
        return 1.0;
    kvector_t position = m_corner_pos + x * m_width + y * m_height;
    double length = position.mag();
    return std::abs(position.dot(m_normal)) / std::pow(length, 3) / m_solid_angle;
}

double RectangularPixel::getSolidAngle() const
{
    return m_solid_angle;
}

kvector_t RectangularPixel::normalizeLength(const kvector_t direction, double length) const
{
    return direction.unit() * length;
}

double RectangularPixel::calculateSolidAngle() const
{
    kvector_t position = m_corner_pos + 0.5 * m_width + 0.5 * m_height;
    double length = position.mag();
    return std::abs(position.dot(m_normal)) / std::pow(length, 3);
}
