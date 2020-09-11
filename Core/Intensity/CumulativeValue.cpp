// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/CumulativeValue.cpp
//! @brief     Implements class CumulativeValue.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Intensity/CumulativeValue.h"
#include <cmath>

double CumulativeValue::getRMS() const
{
    return std::sqrt(m_rms2);
}

void CumulativeValue::add(double value, double weight)
{
    m_n_entries++;
    m_sum += value;
    m_rms2 =
        (m_sum_of_weights / (m_sum_of_weights + weight))
        * (m_rms2
           + (weight / (m_sum_of_weights + weight)) * (value - m_average) * (value - m_average));
    m_average = m_average + (value - m_average) * weight / (m_sum_of_weights + weight);
    m_sum_of_weights += weight;
}

void CumulativeValue::clear()
{
    m_n_entries = 0;
    m_sum = 0.0;
    m_average = 0.0;
    m_rms2 = 0.0;
    m_sum_of_weights = 0.0;
}

bool operator<(const CumulativeValue& lhs, const CumulativeValue& rhs)
{
    return lhs.getContent() < rhs.getContent();
}

bool operator>(const CumulativeValue& lhs, const CumulativeValue& rhs)
{
    return rhs < lhs;
}
