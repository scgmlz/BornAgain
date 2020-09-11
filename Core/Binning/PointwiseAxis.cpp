// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/PointwiseAxis.cpp
//! @brief     Implements class PointwiseAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Binning/PointwiseAxis.h"
#include <algorithm>
#include <iomanip>
#include <stdexcept>

const size_t min_axis_size = 2;

PointwiseAxis* PointwiseAxis::clone() const
{
    return new PointwiseAxis(getName(), m_coordinates);
}

Bin1D PointwiseAxis::getBin(size_t index) const
{
    checkIndex(index);
    return Bin1D(lowerBoundary(index), upperBoundary(index));
}

double PointwiseAxis::getMin() const
{
    return lowerBoundary(0);
}

double PointwiseAxis::getMax() const
{
    return upperBoundary(m_coordinates.size() - 1);
}

double PointwiseAxis::getBinCenter(size_t index) const
{
    checkIndex(index);
    return m_coordinates[index];
}

size_t PointwiseAxis::findClosestIndex(double value) const
{
    if (value <= m_coordinates.front())
        return 0;
    if (value >= m_coordinates.back())
        return m_coordinates.size() - 1;

    const auto begin = m_coordinates.begin();
    auto result = std::lower_bound(begin, m_coordinates.end(), value);
    size_t index = static_cast<size_t>(std::distance(begin, result));
    return value < lowerBoundary(index) ? index - 1 : index;
}

std::vector<double> PointwiseAxis::getBinBoundaries() const
{
    std::vector<double> result;
    const size_t v_size = m_coordinates.size();
    result.reserve(v_size + 1);
    for (size_t i = 0; i < v_size; ++i)
        result.push_back(lowerBoundary(i));
    result.push_back(upperBoundary(v_size - 1));
    return result;
}

PointwiseAxis* PointwiseAxis::createClippedAxis(double left, double right) const
{
    if (left >= right)
        throw std::runtime_error("Error in PointwiseAxis::createClippedAxis: "
                                 "'left' should be smaller than 'right'");

    using diff_t = std::vector<double>::iterator::difference_type;
    auto begin = m_coordinates.begin() + static_cast<diff_t>(findClosestIndex(left));
    auto end = m_coordinates.begin() + static_cast<diff_t>(findClosestIndex(right)) + 1;

    return new PointwiseAxis(getName(), std::vector<double>(begin, end));
}

void PointwiseAxis::print(std::ostream& ostr) const
{
    auto precision = std::setprecision(std::numeric_limits<double>::digits10 + 2);
    ostr << "PointwiseAxis(\"" << getName() << "\", "
         << ", [";
    for (size_t i = 0, fin = m_coordinates.size() - 1; i < fin; ++i)
        ostr << precision << m_coordinates[i] << ",";
    ostr << precision << m_coordinates.back() << "])";
}

bool PointwiseAxis::equals(const IAxis& other) const
{
    if (!IAxis::equals(other))
        return false;
    if (const PointwiseAxis* otherAxis = dynamic_cast<const PointwiseAxis*>(&other))
        return m_coordinates == otherAxis->getBinCenters();
    return false;
}

double PointwiseAxis::lowerBoundary(size_t index) const
{
    if (index == 0)
        return m_coordinates.front();
    return 0.5 * (m_coordinates[index] + m_coordinates[index - 1]);
}

double PointwiseAxis::upperBoundary(size_t index) const
{
    if (index + 1 == m_coordinates.size())
        return m_coordinates.back();
    return 0.5 * (m_coordinates[index] + m_coordinates[index + 1]);
}

void PointwiseAxis::checkIndex(size_t index) const
{
    if (m_coordinates.size() > index)
        return;
    std::string message = "Error in PointwiseAxis::getBinCenter: passed index ";
    message += std::to_string(index) + " exceeds the size ";
    message += std::to_string(m_coordinates.size()) + " of the axis";
    throw std::runtime_error(message);
}

void PointwiseAxis::sanityCheck() const
{
    if (m_coordinates.size() < min_axis_size)
        throw std::runtime_error(
            "Error in PointwiseAxis::PointwiseAxis: the size of passed coordinate array is "
            "less than minimum acceptable value");

    const auto begin = m_coordinates.begin();
    const auto end = m_coordinates.end();

    if (!std::is_sorted(begin, end))
        throw std::runtime_error("Error in PointwiseAxis::PointwiseAxis: passed coordinates are "
                                 "not sorted in ascending order");

    if (std::adjacent_find(begin, end) != end)
        throw std::runtime_error("Error in PointwiseAxis::PointwiseAxis: passed coordinate vector "
                                 "contains repeating values");
}
