//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Mask/Rectangle.cpp
//! @brief     Implements class Rectangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Mask/Rectangle.h"
#include "Base/Axis/Bin.h"

//! @param xlow x-coordinate of lower left corner
//! @param ylow y-coordinate of lower left corner
//! @param xup x-coordinate of upper right corner
//! @param yup y-coordinate of upper right corner
Rectangle::Rectangle(double xlow, double ylow, double xup, double yup) : IShape2D("Rectangle") {
    if (xup <= xlow) {
        std::ostringstream message;
        message << "Rectangle(double xlow, double ylow, double xup, double yup) -> Error. ";
        message << " xup <= xlow" << std::endl;
        throw std::runtime_error(message.str());
    }
    if (yup <= ylow) {
        std::ostringstream message;
        message << "Rectangle(double xlow, double ylow, double xup, double yup) -> Error. ";
        message << " yup <= ylow" << std::endl;
        throw std::runtime_error(message.str());
    }
    m_xlow = xlow;
    m_ylow = ylow;
    m_xup = xup;
    m_yup = yup;
}

bool Rectangle::contains(double x, double y) const {
    return x <= m_xup && x >= m_xlow && y <= m_yup && y >= m_ylow;
}

bool Rectangle::contains(const Bin1D& binx, const Bin1D& biny) const {
    return contains(binx.center(), biny.center());
}

double Rectangle::getArea() const {
    return (m_xup - m_xlow) * (m_yup - m_ylow);
}
