// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/VariableBinAxis.cpp
//! @brief     Implements VariableBinAxis class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Binning/VariableBinAxis.h"
#include "Core/Basics/Exceptions.h"
#include "Fit/TestEngine/Numeric.h"
#include <algorithm>
#include <iomanip>

VariableBinAxis::VariableBinAxis(const std::string& name, size_t nbins,
                                 const std::vector<double>& bin_boundaries)
    : IAxis(name), m_nbins(nbins)
{
    if (m_nbins != bin_boundaries.size() - 1)
        throw Exceptions::LogicErrorException(
            "VariableBinAxis::VariableBinAxis() -> Error! "
            "The size of bin_boundaries should be of size [nbins+1].");

    setBinBoundaries(bin_boundaries);
}

VariableBinAxis::VariableBinAxis(const std::string& name, size_t nbins)
    : IAxis(name), m_nbins(nbins)
{
}

VariableBinAxis* VariableBinAxis::clone() const
{
    VariableBinAxis* result = new VariableBinAxis(getName(), m_nbins, m_bin_boundaries);
    return result;
}

double VariableBinAxis::operator[](size_t index) const
{
    return getBin(index).getMidPoint();
}

Bin1D VariableBinAxis::getBin(size_t index) const
{
    if (index >= m_nbins)
        throw Exceptions::OutOfBoundsException("VariableBinAxis::getBin() -> Error. Wrong index.");

    Bin1D result(m_bin_boundaries[index], m_bin_boundaries[index + 1]);
    return result;
}

double VariableBinAxis::getMin() const
{
    return m_bin_boundaries.front();
}

double VariableBinAxis::getMax() const
{
    return m_bin_boundaries.back();
}

double VariableBinAxis::getBinCenter(size_t index) const
{
    return getBin(index).getMidPoint();
}

size_t VariableBinAxis::findClosestIndex(double value) const
{
    if (m_bin_boundaries.size() < 2)
        throw Exceptions::ClassInitializationException(
            "VariableBinAxis::findClosestIndex() -> Error! "
            "VariableBinAxis not  correctly initialized");
    if (value < getMin()) {
        return 0;
    } else if (value >= getMax()) {
        return m_nbins - 1;
    }

    std::vector<double>::const_iterator top_limit =
        std::lower_bound(m_bin_boundaries.begin(), m_bin_boundaries.end(), value);
    if (*top_limit != value)
        --top_limit;
    size_t nbin = top_limit - m_bin_boundaries.begin();
    return nbin;
}

std::vector<double> VariableBinAxis::getBinCenters() const
{
    std::vector<double> result;
    result.resize(size(), 0.0);
    for (size_t i = 0; i < size(); ++i) {
        result[i] = getBin(i).getMidPoint();
    }
    return result;
}

VariableBinAxis* VariableBinAxis::createClippedAxis(double left, double right) const
{

    if (left >= right)
        throw Exceptions::LogicErrorException("VariableBinAxis::createClippedAxis() -> Error. "
                                              "'left'' should be smaller than 'right'");

    if (left < getMin())
        left = getBin(0).getMidPoint();
    if (right >= getMax())
        right = getBin(size() - 1).getMidPoint();

    size_t nbin1 = findClosestIndex(left);
    size_t nbin2 = findClosestIndex(right);

    size_t new_nbins = nbin2 - nbin1 + 1;
    std::vector<double> new_boundaries;
    for (size_t i = 0; i < new_nbins + 1; ++i) {
        new_boundaries.push_back(m_bin_boundaries[nbin1 + i]);
    }

    return new VariableBinAxis(getName(), new_nbins, new_boundaries);
}

void VariableBinAxis::print(std::ostream& ostr) const
{
    ostr << "VariableBinAxis(\"" << getName() << "\", " << size() << ", [";
    for (size_t i = 0; i < m_bin_boundaries.size(); ++i) {
        ostr << std::setprecision(std::numeric_limits<double>::digits10 + 2) << m_bin_boundaries[i];
        if (i != m_bin_boundaries.size() - 1)
            ostr << ", ";
    }
    ostr << "])";
}

bool VariableBinAxis::equals(const IAxis& other) const
{
    if (!IAxis::equals(other))
        return false;
    if (const VariableBinAxis* p_other_cast = dynamic_cast<const VariableBinAxis*>(&other)) {
        if (size() != p_other_cast->size())
            return false;
        for (size_t i = 0; i < m_bin_boundaries.size(); ++i) {
            if (!Numeric::AreAlmostEqual(m_bin_boundaries[i], p_other_cast->m_bin_boundaries[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

void VariableBinAxis::setBinBoundaries(const std::vector<double>& bin_boundaries)
{
    // checking that values are sorted
    std::vector<double> vec_sorted = bin_boundaries;
    std::sort(vec_sorted.begin(), vec_sorted.end());
    for (size_t i = 0; i < bin_boundaries.size(); ++i) {
        if (vec_sorted[i] != bin_boundaries[i])
            throw Exceptions::LogicErrorException("VariableBinAxis::VariableBinAxis() -> Error. "
                                                  "Array with bin edges is not sorted.");
    }

    std::vector<double> vec = bin_boundaries;
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());

    if (vec.size() != bin_boundaries.size())
        throw Exceptions::LogicErrorException("VariableBinAxis::VariableBinAxis() -> Error. "
                                              "Array with bin edges contains repeating values.");

    m_bin_boundaries = bin_boundaries;
}
