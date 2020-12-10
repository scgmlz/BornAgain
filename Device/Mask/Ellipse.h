//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Mask/Ellipse.h
//! @brief     Defines class Rectangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_DEVICE_MASK_ELLIPSE_H
#define BORNAGAIN_DEVICE_MASK_ELLIPSE_H

#include "Device/Mask/IShape2D.h"

//! An ellipse, for use in detector masks.
//! @ingroup tools

class Ellipse : public IShape2D {
public:
    Ellipse(double xcenter, double ycenter, double xradius, double yradius, double theta = 0.0);
    Ellipse* clone() const { return new Ellipse(m_xc, m_yc, m_xr, m_yr, m_theta); }

    bool contains(double x, double y) const;
    bool contains(const Bin1D& binx, const Bin1D& biny) const;

    double getCenterX() const { return m_xc; }
    double getCenterY() const { return m_yc; }
    double getRadiusX() const { return m_xr; }
    double getRadiusY() const { return m_yr; }
    double getTheta() const { return m_theta; }

private:
    double m_xc, m_yc, m_xr, m_yr, m_theta;
};

#endif // BORNAGAIN_DEVICE_MASK_ELLIPSE_H
