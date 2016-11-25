// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/CustomBinAxis.cpp
//! @brief     Implement class CustomBinAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CustomBinAxis.h"
#include "Exceptions.h" // TODO mv to .cpp
#include "Numeric.h"
#include <iomanip>
#include <limits>

CustomBinAxis::CustomBinAxis(const std::string& name, size_t nbins, double start, double end)
    : VariableBinAxis(name, nbins)
    , m_start(start)
    , m_end(end)
{
    if(m_start >= m_end)
        throw Exceptions::LogicErrorException("CustomBinAxis::CustomBinAxis() -> Error."
                                              " start >= end is not allowed.");

    double start_sin = std::sin(start);
    double end_sin = std::sin(end);
    double step = (end_sin - start_sin)/(m_nbins-1);  // m_nbins-1 is intentionally

    m_bin_centers.resize(m_nbins, 0.0);
    for(size_t i=0; i<m_bin_centers.size(); ++i)
        m_bin_centers[i] = std::asin(start_sin + i*step);

    std::vector<double> bin_boundaries(m_nbins + 1, 0.0);
    for(size_t i=0; i<bin_boundaries.size(); ++i)
        bin_boundaries[i] = std::asin(start_sin -step/2. + step*i);
    setBinBoundaries(bin_boundaries);
}

Bin1D CustomBinAxis::getBin(size_t index) const
{
    if(index >= m_nbins)
        throw Exceptions::OutOfBoundsException("CustomBinAxis::getBin() -> Error. Wrong index.");

    Bin1D result(m_bin_centers[index], m_bin_centers[index]);
    return result;
}

std::vector<double> CustomBinAxis::getBinCenters() const
{
    return m_bin_centers;
}

CustomBinAxis* CustomBinAxis::createClippedAxis(double /* left */, double /* right */) const
{
    throw Exceptions::NotImplementedException("VariableBinAxis::CustomBinAxis() -> Error."
                                              " Not implemented.");
}


void CustomBinAxis::print(std::ostream& ostr) const
{
    ostr << "CustomBinAxis(\"" << m_name << "\", " << size() << ", "
         << std::setprecision(std::numeric_limits<double>::digits10+2)
         << m_start << ", " << m_end << ")";
}


bool CustomBinAxis::equals(const IAxis& other) const
{
    if (!IAxis::sameName(other)) return false;
    if (const CustomBinAxis* otherAxis = dynamic_cast<const CustomBinAxis*>(&other)) {
        if (size() != otherAxis->size()) return false;
        if ( !Numeric::areAlmostEqual(m_start, otherAxis->m_start)) return false;
        if ( !Numeric::areAlmostEqual(m_end, otherAxis->m_end)) return false;
        return true;
    }
    return false;
}
