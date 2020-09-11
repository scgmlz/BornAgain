// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/IShape2D.h
//! @brief     Defines basic class for all 2D shapes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MASK_ISHAPE2D_H
#define BORNAGAIN_CORE_MASK_ISHAPE2D_H

#include "Core/Basics/ICloneable.h"
#include <iostream>

struct Bin1D;

//! Basic class for all shapes in 2D.
//! @ingroup tools

class BA_CORE_API_ IShape2D : public ICloneable
{
public:
    IShape2D(const char* name) : m_name(name) {}
    virtual IShape2D* clone() const = 0;

    //! Returns true if point with given coordinates is inside or on border of the shape.
    virtual bool contains(double x, double y) const = 0;

    //! Returns true if area defined by two bins is inside or on border of polygon
    //! (more precisely, if mid point of two bins satisfy this condition).
    virtual bool contains(const Bin1D& binx, const Bin1D& biny) const = 0;

    friend std::ostream& operator<<(std::ostream& ostr, const IShape2D& shape)
    {
        shape.print(ostr);
        return ostr;
    }

protected:
    virtual void print(std::ostream& ostr) const { ostr << m_name; }

private:
    const char* const m_name;
};

#endif // BORNAGAIN_CORE_MASK_ISHAPE2D_H
