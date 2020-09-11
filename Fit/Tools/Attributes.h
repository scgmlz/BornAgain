// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Tools/Attributes.h
//! @brief     Defines and implements class Attributes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_FIT_TOOLS_ATTRIBUTES_H
#define BORNAGAIN_FIT_TOOLS_ATTRIBUTES_H

#include "Wrap/WinDllMacros.h"
#include <ostream>

//! Attributes for a fit parameter. Currently, the only attribute is fixed/free.
//! @ingroup fitting

class BA_CORE_API_ Attributes
{
public:
    Attributes() : m_is_fixed(false) {}
    //! Creates a fixed value object
    static Attributes fixed() { return Attributes(true); }
    static Attributes free() { return Attributes(false); }

    void setFixed(bool is_fixed) { m_is_fixed = is_fixed; }
    bool isFixed() const { return m_is_fixed; }
    bool isFree() const { return !isFixed(); }

    friend std::ostream& operator<<(std::ostream& ostr, const Attributes& m)
    {
        m.print(ostr);
        return ostr;
    }

    bool operator==(const Attributes& other) const { return isFixed() == other.isFixed(); }
    bool operator!=(const Attributes& other) const { return !(*this == other); }

protected:
    Attributes(bool is_fixed) : m_is_fixed(is_fixed) {}

    bool m_is_fixed; //! parameter is fixed

    void print(std::ostream& ostr) const;
};

//! Prints class
inline void Attributes::print(std::ostream& ostr) const
{
    if (isFixed())
        ostr << "fixed";
    else
        ostr << "free";
}

#endif // BORNAGAIN_FIT_TOOLS_ATTRIBUTES_H
