// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/ResolutionFunction2DGaussian.cpp
//! @brief     Implements class ResolutionFunction2DGaussian.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ResolutionFunction2DGaussian.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "RealParameter.h"

ResolutionFunction2DGaussian::ResolutionFunction2DGaussian(double sigma_x, double sigma_y)
    : m_sigma_x(sigma_x), m_sigma_y(sigma_y)
{
    setName(BornAgain::ResolutionFunction2D);
    // TODO clarify dimension [if detector->getDefaultAxesUnits()==RADIANS then degrees??]
    registerParameter(BornAgain::SigmaX, &m_sigma_x).setNonnegative();
    registerParameter(BornAgain::SigmaY, &m_sigma_y).setNonnegative();
}

double ResolutionFunction2DGaussian::evaluateCDF(double x, double y) const
{
    return MathFunctions::IntegratedGaussian(x, 0.0, m_sigma_x)
        * MathFunctions::IntegratedGaussian(y, 0.0, m_sigma_y);
}
