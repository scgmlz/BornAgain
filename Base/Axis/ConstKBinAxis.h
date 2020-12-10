//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Base/Axis/ConstKBinAxis.h
//! @brief     Defines class ConstKBinAxis.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_BASE_AXIS_CONSTKBINAXIS_H
#define BORNAGAIN_BASE_AXIS_CONSTKBINAXIS_H

#include "Base/Axis/VariableBinAxis.h"

//! Axis with fixed bin size in sin(angle) space.
//! @ingroup tools

class ConstKBinAxis : public VariableBinAxis {
public:
    //! ConstKBinAxis constructor.
    //! @param name Axis name
    //! @param nbins number of bins
    //! @param start low edge of first bin
    //! @param end upper edge of last bin
    ConstKBinAxis(const std::string& name, size_t nbins, double start, double end);
    ~ConstKBinAxis() override {}

    ConstKBinAxis* clone() const override;

    ConstKBinAxis* createClippedAxis(double left, double right) const override;

protected:
    ConstKBinAxis(const std::string& name, size_t nbins);

    void print(std::ostream& ostr) const override;
    bool equals(const IAxis& other) const override;

    double m_start;
    double m_end;
};

#endif // BORNAGAIN_BASE_AXIS_CONSTKBINAXIS_H
