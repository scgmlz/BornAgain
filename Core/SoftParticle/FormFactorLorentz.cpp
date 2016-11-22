// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorLorentz.cpp
//! @brief     Implements class FormFactorLorentz.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorLorentz.h"
#include "BornAgainNamespace.h"
#include "RealLimits.h"
#include "MathConstants.h"
#include "RealParameter.h"

FormFactorLorentz::FormFactorLorentz(double width, double height)
{
    m_width = width;
    m_height = height;
    initialize();
}

FormFactorLorentz::FormFactorLorentz(double length)
    : m_width { length }
    , m_height { length }
{
    initialize();
}


double FormFactorLorentz::getRadialExtension() const
{
    return m_width / 2.0;
}

complex_t FormFactorLorentz::evaluate_for_q(const cvector_t q) const
{
    static const double sigma2 = 4.0*std::pow(M_PI, 2.0/3.0);
    double R = m_width;
    double H = m_height;

    complex_t xnorm = R*R*q.x()*q.x()/sigma2;
    complex_t ynorm = R*R*q.y()*q.y()/sigma2;
    complex_t znorm = H*H*q.z()*q.z()/sigma2;

    complex_t result = H*R*R/(1.0 + xnorm + ynorm + znorm);

    return result;
}

void FormFactorLorentz::initialize()
{
    setName(BornAgain::FFLorentzType);
    registerParameter(BornAgain::Width, &m_width).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
}
