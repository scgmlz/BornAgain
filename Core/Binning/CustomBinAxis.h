// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/CustomBinAxis.h
//! @brief     Defines class CustomBinAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CUSTOMBINAXIS_H
#define CUSTOMBINAXIS_H

#include "VariableBinAxis.h"

//! Axis with fixed bin size in sin(angle) space used for numerical comparison with IsGisaxs.
//! The main feature of the axis is that it produces zero bin sizes.
//! @ingroup tools

class BA_CORE_API_ CustomBinAxis : public VariableBinAxis
{
public:
    //! CustomBinAxis constructor.
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param start center of first bin (IsGisaxs convention)
    //! @param end center of last bin (IsGisaxs convention)
    CustomBinAxis(const std::string& name, size_t nbins, double start, double end);
    virtual ~CustomBinAxis() {}

    CustomBinAxis* clone() const;

    Bin1D getBin(size_t index) const;

    std::vector<double > getBinCenters() const;

    CustomBinAxis* createClippedAxis(double left, double right) const;

protected:
    void print(std::ostream& ostr) const;
    bool equals(const IAxis& other) const;

    double m_start;
    double m_end;
    std::vector<double> m_bin_centers;
};

#endif // CUSTOMBINAXIS_H
