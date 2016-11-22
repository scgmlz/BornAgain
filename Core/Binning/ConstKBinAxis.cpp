// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/ConstKBinAxis.cpp
//! @brief     Implement class ConstKBinAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ConstKBinAxis.h"
#include "Exceptions.h" // TODO mv to .cpp
#include "Numeric.h"
#include <iomanip>

ConstKBinAxis::ConstKBinAxis(const std::string& name, size_t nbins)
    : VariableBinAxis(name, nbins)
    , m_start(0)
    , m_end(0)
{}

ConstKBinAxis::ConstKBinAxis(const std::string& name, size_t nbins, double start, double end)
    : VariableBinAxis(name, nbins)
    , m_start(start)
    , m_end(end)
{
    if(m_start >= m_end)
        throw Exceptions::LogicErrorException(
            "ConstKBinAxis::ConstKBinAxis() -> Error. start >= end is not allowed.");

    double start_sin = std::sin(m_start);
    double end_sin = std::sin(m_end);
    double step = (end_sin-start_sin)/(m_nbins);

    std::vector<double> bin_boundaries(m_nbins + 1, 0.0);
    for(size_t i=0; i<bin_boundaries.size(); ++i)
        bin_boundaries[i] = std::asin(start_sin + step*i);
    setBinBoundaries(bin_boundaries);
}

ConstKBinAxis* ConstKBinAxis::createClippedAxis(double left, double right) const
{
    if(left >= right)
        throw Exceptions::LogicErrorException(
            "ConstKBinAxis::createClippedAxis() -> Error. 'left'' should be smaller than 'right'");

    if(left < getMin())
        left = getBin(0).getMidPoint();
    if(right >= getMax())
        right = getBin(size()-1).getMidPoint();

    size_t nbin1 = findClosestIndex(left);
    size_t nbin2 = findClosestIndex(right);

    size_t new_nbins = nbin2-nbin1+1;
    std::vector<double> new_boundaries;
    std::vector<double> old_boundaries = getBinBoundaries();
    for(size_t i=0; i<new_nbins+1; ++i)
        new_boundaries.push_back(old_boundaries[nbin1 + i]);

    ConstKBinAxis* result = new ConstKBinAxis(getName(), new_nbins);
    result->m_start = new_boundaries.front();
    result->m_end = new_boundaries.back();
    result->setBinBoundaries(new_boundaries);
    return result;
}

bool ConstKBinAxis::equals(const IAxis& other) const
{
    const ConstKBinAxis* otherAxis = dynamic_cast<const ConstKBinAxis*>(&other);
    return
        IAxis::sameName(other) &&
        otherAxis &&
        size() == otherAxis->size() &&
        Numeric::areAlmostEqual(m_start, otherAxis->m_start) &&
        Numeric::areAlmostEqual(m_end, otherAxis->m_end);
}

void ConstKBinAxis::print(std::ostream& ostr) const
{
    ostr << "ConstKBinAxis(\"" << m_name << "\", " << size() << ", "
         << std::setprecision(std::numeric_limits<double>::digits10+2)
         << m_start << ", " << m_end << ")";
}
