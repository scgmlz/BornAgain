// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Binning/ConstKBinAxis.h
//! @brief     Defines class ConstKBinAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_BINNING_CONSTKBINAXIS_H
#define BORNAGAIN_CORE_BINNING_CONSTKBINAXIS_H

#include "Core/Binning/VariableBinAxis.h"

//! Axis with fixed bin size in sin(angle) space.
//! @ingroup tools

class BA_CORE_API_ ConstKBinAxis : public VariableBinAxis
{
public:
    //! ConstKBinAxis constructor.
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param start low edge of first bin
    //! @param end upper edge of last bin
    ConstKBinAxis(const std::string& name, size_t nbins, double start, double end);
    ~ConstKBinAxis() final {}

    ConstKBinAxis* clone() const final;

    ConstKBinAxis* createClippedAxis(double left, double right) const final;

protected:
    ConstKBinAxis(const std::string& name, size_t nbins);

    void print(std::ostream& ostr) const final;
    bool equals(const IAxis& other) const final;

    double m_start;
    double m_end;
};

#endif // BORNAGAIN_CORE_BINNING_CONSTKBINAXIS_H
