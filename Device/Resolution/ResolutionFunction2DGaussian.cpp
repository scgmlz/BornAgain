//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Device/Resolution/ResolutionFunction2DGaussian.cpp
//! @brief     Implements class ResolutionFunction2DGaussian.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Device/Resolution/ResolutionFunction2DGaussian.h"
#include "Base/Math/Functions.h"
#include "Param/Base/RealParameter.h"

ResolutionFunction2DGaussian::ResolutionFunction2DGaussian(double sigma_x, double sigma_y)
    : m_sigma_x(sigma_x), m_sigma_y(sigma_y) {
    setName("ResolutionFunction2D");
    registerParameter("SigmaX", &m_sigma_x).setNonnegative();
    registerParameter("SigmaY", &m_sigma_y).setNonnegative();
}

double ResolutionFunction2DGaussian::evaluateCDF(double x, double y) const {
    return Math::IntegratedGaussian(x, 0.0, m_sigma_x)
           * Math::IntegratedGaussian(y, 0.0, m_sigma_y);
}
