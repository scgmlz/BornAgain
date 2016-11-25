// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongRipple1Gauss.cpp
//! @brief     Implements class FormFactorLongRipple1Gauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorLongRipple1Gauss.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathConstants.h"
#include "MathFunctions.h"
#include "RealLimits.h"
#include "RealParameter.h"

FormFactorLongRipple1Gauss::FormFactorLongRipple1Gauss(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    setName(BornAgain::FFLongRipple1GaussType);
    check_initialization();
    registerParameter(BornAgain::Length, &m_length).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    mP_integrator = make_integrator_complex(this, &FormFactorLongRipple1Gauss::Integrand);
}

bool FormFactorLongRipple1Gauss::check_initialization() const
{
    bool result(true);
    if (m_height <= 0.0 || m_width <= 0.0 || m_length <= 0.0) {
        std::ostringstream ostr;
        ostr << "FormFactorLongRipple1Gauss() -> Error in class initialization with parameters ";
        ostr << " height:" << m_height;
        ostr << " width:" << m_width;
        ostr << " length:" << m_length << "\n\n";
        ostr << "Check for 'height>0.0 && width>0.0 && length>0.0' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}

double FormFactorLongRipple1Gauss::getRadialExtension() const { return (m_width + m_length) / 4.0; }

//! Integrand for complex formfactor.
complex_t FormFactorLongRipple1Gauss::Integrand(double Z) const
{
    complex_t aa = std::acos(2.0 * Z / m_height - 1.0);
    return exp_I(m_q.z() * Z) * aa * MathFunctions::sinc(aa * m_q.y() * m_width / (M_TWOPI));
}

//! Complex formfactor.
complex_t FormFactorLongRipple1Gauss::evaluate_for_q(const cvector_t q) const
{
    m_q = q;
    //    complex_t factor = m_length*MathFunctions::sinc(m_q.x()*m_length*0.5)*m_width/M_PI;
    complex_t qxL2 = std::pow(m_length * q.x(), 2) / 2.0;
    complex_t factor = m_length * std::exp(-qxL2) * m_width / M_PI;

    complex_t aaa = m_q.y() * m_width / (M_TWOPI);
    complex_t aaa2 = aaa * aaa;

    // analytical expressions for some particular cases
    if (0.0 == m_q.y() && 0.0 == m_q.z())
        return factor * M_PI_2 * m_height;
    else if (0.0 == m_q.z() && 1.0 == aaa2)
        return factor * M_PI_4 * m_height;
    else if (0.0 == m_q.z())
        return factor * M_PI_2 * m_height * MathFunctions::sinc(m_q.y() * m_width * 0.5)
            / (1.0 - aaa2);

    // numerical integration otherwise
    complex_t integral = mP_integrator->integrate(0, m_height);
    return factor * integral;
}
