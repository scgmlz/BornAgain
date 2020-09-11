// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/DetectionProperties.cpp
//! @brief     Implements class DetectionProperties.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/DetectionProperties.h"
#include "Core/Basics/Complex.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Parametrization/RealParameter.h"

DetectionProperties::DetectionProperties(kvector_t direction, double efficiency,
                                         double total_transmission)
    : m_direction(direction), m_efficiency(efficiency), m_total_transmission(total_transmission)
{
    setName("Analyzer");
    registerVector("Direction", &m_direction, "");
    registerParameter("Efficiency", &m_efficiency);
    registerParameter("Transmission", &m_total_transmission).setNonnegative();
}

DetectionProperties::DetectionProperties() : DetectionProperties({}, {}, 1.0) {}

DetectionProperties::DetectionProperties(const DetectionProperties& other)
    : DetectionProperties(other.m_direction, other.m_efficiency, other.m_total_transmission)
{
}

void DetectionProperties::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                                double total_transmission)
{
    if (!checkAnalyzerProperties(direction, efficiency, total_transmission))
        throw Exceptions::ClassInitializationException("IDetector2D::setAnalyzerProperties: the "
                                                       "given properties are not physical");
    if (efficiency == 0.0 || total_transmission == 0.0 || direction.mag() == 0.0) {
        m_direction = kvector_t{};
        m_efficiency = 0.0;
    } else {
        m_direction = direction.unit();
        m_efficiency = efficiency;
    }
    m_total_transmission = total_transmission;
}

Eigen::Matrix2cd DetectionProperties::analyzerOperator() const
{
    if (m_direction.mag() == 0.0 || m_efficiency == 0.0)
        return m_total_transmission * Eigen::Matrix2cd::Identity();
    Eigen::Matrix2cd result;
    double x = m_direction.x() / m_direction.mag();
    double y = m_direction.y() / m_direction.mag();
    double z = m_direction.z() / m_direction.mag();
    double sum = m_total_transmission * 2.0;
    double diff = m_total_transmission * m_efficiency * 2.0;
    complex_t im(0.0, 1.0);
    result(0, 0) = (sum + diff * z) / 2.0;
    result(0, 1) = diff * (x - im * y) / 2.0;
    result(1, 0) = diff * (x + im * y) / 2.0;
    result(1, 1) = (sum - diff * z) / 2.0;
    return result;
}

kvector_t DetectionProperties::analyzerDirection() const
{
    return m_direction;
}

double DetectionProperties::analyzerEfficiency() const
{
    return m_efficiency;
}

double DetectionProperties::analyzerTotalTransmission() const
{
    return m_total_transmission;
}

bool DetectionProperties::checkAnalyzerProperties(const kvector_t direction, double efficiency,
                                                  double total_transmission) const
{
    if (direction.mag() == 0.0)
        return false;
    double aplus = total_transmission * (1.0 + efficiency);
    double amin = total_transmission * (1.0 - efficiency);
    if (aplus < 0.0 || aplus > 1.0)
        return false;
    if (amin < 0.0 || amin > 1.0)
        return false;
    return true;
}
