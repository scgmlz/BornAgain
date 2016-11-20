// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/Rectangle.h
//! @brief     Defines class Rectangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "IShape2D.h"

//! The rectangle shape having its axis aligned to the (non-rotated) coordinate system.
//! @ingroup mask

class BA_CORE_API_ Rectangle : public IShape2D {
public:
    Rectangle(double xlow, double ylow, double xup, double yup);
    Rectangle* clone() const { return new Rectangle(m_xlow, m_ylow, m_xup, m_yup); }

    bool contains(double x, double y) const;
    bool contains(const Bin1D& binx, const Bin1D& biny) const;

    double getArea() const;

    double getXlow() const { return m_xlow; }
    double getYlow() const { return m_ylow; }
    double getXup()  const { return m_xup; }
    double getYup()  const { return m_yup; }

private:
    double m_xlow, m_ylow, m_xup, m_yup;
};

#endif // RECTANGLE_H
