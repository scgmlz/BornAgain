// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/RealLimits.h
//! @brief     Defines class RealLimits.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef REALLIMITS_H
#define REALLIMITS_H

#include "WinDllMacros.h"
#include <ostream>

//! Limits for a real fit parameter.
//! @ingroup fitting

class BA_CORE_API_ RealLimits
{
 public:
    RealLimits()
        : m_has_lower_limit(false), m_has_upper_limit(false),
        m_lower_limit(0.), m_upper_limit(0.) {}

    //! if has lower limit
    bool hasLowerLimit() const { return m_has_lower_limit; }

    //! Returns lower limit
    double getLowerLimit() const { return m_lower_limit; }

    //! Sets lower limit
    void setLowerLimit(double value) { m_lower_limit = value; m_has_lower_limit = true; }

    //! remove lower limit
    void removeLowerLimit() { m_lower_limit = 0.; m_has_lower_limit = false; }

    //! if has upper limit
    bool hasUpperLimit() const { return m_has_upper_limit; }

    //! Returns upper limit
    double getUpperLimit() const { return m_upper_limit; }

    //! Sets upper limit
    void setUpperLimit(double value) { m_upper_limit = value; m_has_upper_limit = true; }

    //! remove upper limit
    void removeUpperLimit() { m_upper_limit = 0.; m_has_upper_limit = false; }

    //! if has lower and upper limit
    bool hasLowerAndUpperLimits() const { return (m_has_lower_limit && m_has_upper_limit); }

    //! Sets lower and upper limits
    void setLimits(double xmin, double xmax) { setLowerLimit(xmin); setUpperLimit(xmax); }

    //! remove limits
    void removeLimits() { removeLowerLimit(); removeUpperLimit(); }

    //! returns true if proposed value is in limits range
    bool isInRange(double value) const;

    // ---------
    // static creation methods

    //! Creates an object bounded from the left
    static RealLimits lowerLimited(double bound_value) {
        return RealLimits(true, false, bound_value, 0.); }

    //! Creates an object which can have only positive values (>0., zero is not included)
    static RealLimits positive();

    //! Creates an object which can have only positive values with 0. included
    static RealLimits nonnegative() { return lowerLimited(0.); }

    //! Creates an object bounded from the right
    static RealLimits upperLimited(double bound_value) {
        return RealLimits(false, true, 0., bound_value); }

    //! Creates an object bounded from the left and right
    static RealLimits limited(double left_bound_value, double right_bound_value) {
        return RealLimits(true, true, left_bound_value, right_bound_value); }

    //! Creates an object withoud bounds (default)
    static RealLimits limitless() { return RealLimits(); }

    //! Prints class
    friend std::ostream& operator<<(std::ostream& ostr, const RealLimits& m)
    { m.print(ostr); return ostr; }

    bool operator==(const RealLimits &other) const;
    bool operator!=(const RealLimits &other) const { return !(*this == other); }

 protected:
    RealLimits(bool has_lower_limit, bool has_upper_limit, double lower_limit, double upper_limit)
        : m_has_lower_limit(has_lower_limit)
        , m_has_upper_limit(has_upper_limit)
        , m_lower_limit(lower_limit)
        , m_upper_limit(upper_limit) {}

    bool   m_has_lower_limit; //! parameter has lower bound
    bool   m_has_upper_limit; //! parameter has upper bound
    double m_lower_limit; //! minimum allowed value
    double m_upper_limit; //! maximum allowed value

    void print(std::ostream& ostr) const;
};

#endif // REALLIMITS_H
