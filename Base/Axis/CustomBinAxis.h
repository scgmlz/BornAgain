//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Axis/CustomBinAxis.h
//! @brief     Defines class CustomBinAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_BASE_AXIS_CUSTOMBINAXIS_H
#define BORNAGAIN_BASE_AXIS_CUSTOMBINAXIS_H

#include "Base/Axis/VariableBinAxis.h"

//! Axis with fixed bin size in sin(angle) space used for numerical comparison with IsGisaxs.
//! The main feature of the axis is that it produces zero bin sizes.
//! @ingroup tools

class CustomBinAxis : public VariableBinAxis {
public:
    //! CustomBinAxis constructor.
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param start center of first bin (IsGisaxs convention)
    //! @param end center of last bin (IsGisaxs convention)
    CustomBinAxis(const std::string& name, size_t nbins, double start, double end);
    virtual ~CustomBinAxis() {}

    CustomBinAxis* clone() const;

    Bin1D bin(size_t index) const;

    std::vector<double> binCenters() const;

    CustomBinAxis* createClippedAxis(double left, double right) const;

protected:
    void print(std::ostream& ostr) const;
    bool equals(const IAxis& other) const;

    double m_start;
    double m_end;
    std::vector<double> m_bin_centers;
};

#endif // BORNAGAIN_BASE_AXIS_CUSTOMBINAXIS_H
