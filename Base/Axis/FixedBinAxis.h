//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Axis/FixedBinAxis.h
//! @brief     Defines class FixedBinAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_BASE_AXIS_FIXEDBINAXIS_H
#define BORNAGAIN_BASE_AXIS_FIXEDBINAXIS_H

#include "Base/Axis/IAxis.h"

//! Axis with fixed bin size.
//! @ingroup tools

class FixedBinAxis : public IAxis {
public:
    //! FixedBinAxis constructor.
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param start low edge of first bin
    //! @param end upper edge of last bin
    FixedBinAxis(const std::string& name, size_t nbins, double start, double end);
    virtual ~FixedBinAxis() {}

    FixedBinAxis* clone() const;

    size_t size() const { return m_nbins; }

    double operator[](size_t index) const;

    Bin1D bin(size_t index) const;

    double lowerBound() const { return m_start; }
    double upperBound() const { return m_end; }

    double binCenter(size_t index) const { return (*this)[index]; }

    size_t findClosestIndex(double value) const;

    std::vector<double> binCenters() const;

    std::vector<double> binBoundaries() const;

    FixedBinAxis* createClippedAxis(double left, double right) const;

protected:
    void print(std::ostream& ostr) const;
    virtual bool equals(const IAxis& other) const;

private:
    size_t m_nbins;
    double m_start;
    double m_end;
};

#endif // BORNAGAIN_BASE_AXIS_FIXEDBINAXIS_H
