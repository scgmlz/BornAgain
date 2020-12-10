//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Axis/FixedBinAxis.cpp
//! @brief     Implement class FixedBinAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Base/Axis/FixedBinAxis.h"
#include "Base/Utils/Algorithms.h"
#include <iomanip>
#include <limits>

FixedBinAxis::FixedBinAxis(const std::string& name, size_t nbins, double start, double end)
    : IAxis(name), m_nbins(nbins), m_start(start), m_end(end) {}

FixedBinAxis* FixedBinAxis::clone() const {
    FixedBinAxis* result = new FixedBinAxis(getName(), m_nbins, m_start, m_end);
    return result;
}

double FixedBinAxis::operator[](size_t index) const {
    if (index >= m_nbins)
        throw std::runtime_error("FixedBinAxis::operator[] -> Error. Wrong index.");

    double step = (m_end - m_start) / m_nbins;
    return m_start + (index + 0.5) * step;
}

Bin1D FixedBinAxis::bin(size_t index) const {
    if (index >= m_nbins)
        throw std::runtime_error("FixedBinAxis::bin() -> Error. Wrong index.");

    double step = (m_end - m_start) / m_nbins;
    Bin1D result(m_start + step * index, m_start + step * (index + 1));
    return result;
}

size_t FixedBinAxis::findClosestIndex(double value) const {
    if (value < lowerBound()) {
        return 0;
    } else if (value >= upperBound()) {
        return m_nbins - 1;
    }

    double step = (m_end - m_start) / m_nbins;
    return int((value - m_start) / step);
}

std::vector<double> FixedBinAxis::binCenters() const {
    std::vector<double> result;
    result.resize(size(), 0.0);
    for (size_t i = 0; i < size(); ++i) {
        result[i] = bin(i).center();
    }
    return result;
}

std::vector<double> FixedBinAxis::binBoundaries() const {
    std::vector<double> result;
    result.resize(size() + 1, 0.0);
    for (size_t i = 0; i < size(); ++i) {
        result[i] = bin(i).m_lower;
    }
    result[size()] = bin(size() - 1).m_upper;
    return result;
}

FixedBinAxis* FixedBinAxis::createClippedAxis(double left, double right) const {
    if (left >= right)
        throw std::runtime_error("FixedBinAxis::createClippedAxis() -> Error. "
                                 "'left' should be smaller than 'right'");

    if (left < lowerBound())
        left = bin(0).center();
    if (right >= upperBound())
        right = bin(size() - 1).center();

    size_t nbin1 = findClosestIndex(left);
    size_t nbin2 = findClosestIndex(right);

    return new FixedBinAxis(getName(), nbin2 - nbin1 + 1, bin(nbin1).m_lower, bin(nbin2).m_upper);
}

void FixedBinAxis::print(std::ostream& ostr) const {
    ostr << "FixedBinAxis(\"" << getName() << "\", " << size() << ", "
         << std::setprecision(std::numeric_limits<double>::digits10 + 2) << lowerBound() << ", "
         << upperBound() << ")";
}

bool FixedBinAxis::equals(const IAxis& other) const {
    if (!IAxis::equals(other))
        return false;
    if (const FixedBinAxis* otherAxis = dynamic_cast<const FixedBinAxis*>(&other)) {
        if (size() != otherAxis->size())
            return false;
        if (!algo::almostEqual(m_start, otherAxis->m_start))
            return false;
        if (!algo::almostEqual(m_end, otherAxis->m_end))
            return false;
        return true;
    }
    return false;
}
