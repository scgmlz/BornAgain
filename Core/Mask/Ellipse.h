// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/Ellipse.h
//! @brief     Defines class Rectangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "IShape2D.h"

//! Ellipse shape.
//! @ingroup tools

class  BA_CORE_API_ Ellipse : public IShape2D {
public:
    Ellipse(double xcenter, double ycenter, double xradius, double yradius, double theta = 0.0);
    Ellipse* clone() const { return new Ellipse(m_xc, m_yc, m_xr, m_yr, m_theta); }

    bool contains(double x, double y) const;
    bool contains(const Bin1D& binx, const Bin1D& biny) const;

    double getCenterX() const { return m_xc; }
    double getCenterY() const { return m_yc; }
    double getRadiusX() const { return m_xr; }
    double getRadiusY() const { return m_yr; }
    double getTheta()   const { return m_theta; }

private:
    double m_xc, m_yc, m_xr, m_yr, m_theta;
};

#endif // ELLIPSE_H
