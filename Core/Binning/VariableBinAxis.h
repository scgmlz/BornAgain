// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/VariableBinAxis.h
//! @brief     Defines class VariableBinAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BINNING_VARIABLEBINAXIS_H
#define BORNAGAIN_CORE_BINNING_VARIABLEBINAXIS_H

#include "Core/Binning/IAxis.h"

//! Axis with variable bin size.
//! @ingroup tools

class BA_CORE_API_ VariableBinAxis : public IAxis
{
public:
    //! VariableBinAxis constructor.
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param bin_boundaries Array of size nbins+1 containing low-edges for each
    //! bin and upper edge of last bin.
    VariableBinAxis(const std::string& name, size_t nbins,
                    const std::vector<double>& bin_boundaries);
    virtual ~VariableBinAxis() {}

    VariableBinAxis* clone() const;

    size_t size() const { return m_nbins; }

    double operator[](size_t index) const;

    Bin1D getBin(size_t index) const;

    double getMin() const;
    double getMax() const;

    double getBinCenter(size_t index) const;

    size_t findClosestIndex(double value) const;

    std::vector<double> getBinCenters() const;
    std::vector<double> getBinBoundaries() const { return m_bin_boundaries; }

    virtual VariableBinAxis* createClippedAxis(double left, double right) const;

protected:
    VariableBinAxis(const std::string& name, size_t nbins = 0);
    void setBinBoundaries(const std::vector<double>& bin_boundaries);

    virtual void print(std::ostream& ostr) const;
    virtual bool equals(const IAxis& other) const;
    size_t m_nbins;

private:
    std::vector<double> m_bin_boundaries; //!< vector containing the bin limits
};

#endif // BORNAGAIN_CORE_BINNING_VARIABLEBINAXIS_H
