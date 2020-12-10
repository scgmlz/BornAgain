//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Mask/Rectangle.h
//! @brief     Defines class Rectangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_MASK_RECTANGLE_H
#define BORNAGAIN_DEVICE_MASK_RECTANGLE_H

#include "Device/Mask/IShape2D.h"

//! A rectangle, for use in detector masks.
//!
//! Edges are along the coordinate axes.
//! @ingroup mask

class Rectangle : public IShape2D {
public:
    Rectangle(double xlow, double ylow, double xup, double yup);
    Rectangle* clone() const { return new Rectangle(m_xlow, m_ylow, m_xup, m_yup); }

    bool contains(double x, double y) const;
    bool contains(const Bin1D& binx, const Bin1D& biny) const;

    double getArea() const;

    double getXlow() const { return m_xlow; }
    double getYlow() const { return m_ylow; }
    double getXup() const { return m_xup; }
    double getYup() const { return m_yup; }

private:
    double m_xlow, m_ylow, m_xup, m_yup;
};

#endif // BORNAGAIN_DEVICE_MASK_RECTANGLE_H
