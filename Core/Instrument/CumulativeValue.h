// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/CumulativeValue.h
//! @brief     Defines class CumulativeValue.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CUMULATIVEVALUE_H
#define CUMULATIVEVALUE_H

#include "WinDllMacros.h"

//! The cumulative value with average and rms on-the-flight calculations.
//! @ingroup tools

class BA_CORE_API_ CumulativeValue
{
public:
    CumulativeValue() { clear(); }

    void clear();
    void setContent(double value) { m_sum = value; }
    void add(double value, double weight=1.0);

    int getNumberOfEntries() const { return m_n_entries; }
    double getContent() const { return m_sum; }
    double getAverage() const { return m_average; }
    double getRMS() const;

private:
    int m_n_entries;
    double m_sum;
    double m_average;
    double m_rms2; //sum[ (x-x_aver)^2]/nentries
    double m_sum_of_weights;
};

BA_CORE_API_ bool operator< (const CumulativeValue& lhs, const CumulativeValue& rhs);
BA_CORE_API_ bool operator> (const CumulativeValue& lhs, const CumulativeValue& rhs);

#endif // CUMULATIVEVALUE_H
