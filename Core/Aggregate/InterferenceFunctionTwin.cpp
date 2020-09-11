// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionTwin.cpp
//! @brief     Implements class InterferenceFunctionTwin.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Aggregate/InterferenceFunctionTwin.h"
#include "Core/Parametrization/RealParameter.h"
#include <cmath>

InterferenceFunctionTwin::InterferenceFunctionTwin(const kvector_t& direction, double mean_distance,
                                                   double std_dev)
    : IInterferenceFunction(0), m_direction(direction), m_distance(mean_distance),
      m_std_dev(std_dev)
{
    setName("InterferenceTwin");
    if (m_direction.mag2() <= 0.0 || m_distance < 0.0 || m_std_dev < 0.0)
        throw std::runtime_error(
            "InterferenceFunctionTwin::validateParameters: mean distance, standard deviation and "
            "length of direction vector should be positive");
    registerVector("Direction", &m_direction, "");
    registerParameter("Mean", &m_distance).setUnit("nm").setNonnegative();
    registerParameter("StdDev", &m_std_dev).setUnit("nm").setNonnegative();
}

InterferenceFunctionTwin* InterferenceFunctionTwin::clone() const
{
    auto* ret = new InterferenceFunctionTwin(m_direction, m_distance, m_std_dev);
    ret->setPositionVariance(m_position_var);
    return ret;
}

kvector_t InterferenceFunctionTwin::direction() const
{
    return m_direction;
}

double InterferenceFunctionTwin::meanDistance() const
{
    return m_distance;
}

double InterferenceFunctionTwin::stdDev() const
{
    return m_std_dev;
}

double InterferenceFunctionTwin::iff_without_dw(const kvector_t q) const
{
    double q_proj = q.dot(m_direction.unit());
    return 1.0
           + std::exp(-q_proj * q_proj * m_std_dev * m_std_dev / 2.0)
                 * std::cos(q_proj * m_distance);
}
