// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/DetectionProperties.cpp
//! @brief     Implements class DetectionProperties.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "DetectionProperties.h"
#include "Complex.h"
#include "Exceptions.h"

DetectionProperties::DetectionProperties() { initPolarizationOperator(); }

void DetectionProperties::setAnalyzerProperties(
    const kvector_t direction, double efficiency, double total_transmission)
{
    if (!checkAnalyzerProperties(direction, efficiency, total_transmission))
        throw Exceptions::ClassInitializationException("IDetector2D::setAnalyzerProperties: the "
                                                       "given properties are not physical");

    m_analyzer_operator = calculateAnalyzerOperator(direction, efficiency, total_transmission);
}

Eigen::Matrix2cd DetectionProperties::analyzerOperator() const { return m_analyzer_operator; }

void DetectionProperties::initPolarizationOperator()
{
    m_analyzer_operator = Eigen::Matrix2cd::Identity();
}

bool DetectionProperties::checkAnalyzerProperties(
    const kvector_t direction, double efficiency, double total_transmission) const
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

Eigen::Matrix2cd DetectionProperties::calculateAnalyzerOperator(
    const kvector_t direction, double efficiency, double total_transmission) const
{
    Eigen::Matrix2cd result;
    double x = direction.x() / direction.mag();
    double y = direction.y() / direction.mag();
    double z = direction.z() / direction.mag();
    double sum = total_transmission * 2.0;
    double diff = total_transmission * efficiency * 2.0;
    complex_t im(0.0, 1.0);
    result(0, 0) = (sum + diff * z) / 2.0;
    result(0, 1) = diff * (x - im * y) / 2.0;
    result(1, 0) = diff * (x + im * y) / 2.0;
    result(1, 1) = (sum - diff * z) / 2.0;
    return result;
}
