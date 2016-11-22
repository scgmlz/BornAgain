// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Mask/Ellipse.cpp
//! @brief     Implements class Ellipse.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Ellipse.h"
#include "Bin.h"
#include "Exceptions.h"

//! @param xcenter x-coordinate of Ellipse's center
//! @param ycenter y-coordinate of Ellipse's center
//! @param xradius Radius along x-axis
//! @param yradius Radius along y-axis
//! @param theta Angle of Ellipse rotation in radians
Ellipse::Ellipse(double xcenter, double ycenter, double xradius, double yradius, double theta)
    : IShape2D("Ellipse")
    , m_xc(xcenter)
    , m_yc(ycenter)
    , m_xr(xradius)
    , m_yr(yradius)
    , m_theta(theta)
{
    if(xradius <= 0.0 || yradius <= 0.0)
        throw Exceptions::LogicErrorException(
            "Ellipse::Ellipse(double xcenter, double ycenter, double xradius, double yradius) "
            "-> Error. Radius can't be negative\n");
}

bool Ellipse::contains(double x, double y) const
{
    double u = std::cos(m_theta)*(x-m_xc) + std::sin(m_theta)*(y-m_yc);
    double v = -std::sin(m_theta)*(x-m_xc) + std::cos(m_theta)*(y-m_yc);
    double d = (u/m_xr)*(u/m_xr) + (v/m_yr)*(v/m_yr);
    return d<=1;
}

//! Returns true if area defined by two bins is inside or on border of ellipse;
//! more precisely, if mid point of two bins satisfy this condition.
bool Ellipse::contains(const Bin1D& binx, const Bin1D& biny) const
{
    return contains(binx.getMidPoint(), biny.getMidPoint());
}
