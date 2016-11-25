// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorRipple2.cpp
//! @brief     Implements class FormFactorRipple2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorRipple2.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "MathFunctions.h"
#include "RealParameter.h"

FormFactorRipple2::FormFactorRipple2(double length, double width, double height, double asymetry)
    : m_length(length), m_width(width), m_height(height), m_d(asymetry)
{
    setName(BornAgain::FFRipple2Type);
    check_initialization();
    registerParameter(BornAgain::Length, &m_length).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::AsymmetryLength, &m_d).setUnit("nm");
}

double FormFactorRipple2::getRadialExtension() const { return (m_width + m_length) / 4.0; }

//! Complex formfactor.
complex_t FormFactorRipple2::evaluate_for_q(const cvector_t q) const
{
    complex_t factor = m_length * MathFunctions::sinc(q.x() * m_length * 0.5) * m_width;
    complex_t result = 0;
    complex_t iqzH = mul_I(q.z() * m_height);
    complex_t iqyW = mul_I(q.y() * m_width);
    complex_t aaa = 2.0 * (m_d * q.y() + m_height * q.z());

    if (0.0 == q.y() && 0.0 == q.z())
        result = m_height * 0.5;
    else if (0.0 == q.y())
        result = (1.0 - std::exp(iqzH) + iqzH) / (m_height * q.z() * q.z());
    else if (1.0 == aaa / (q.y() * m_width))
        result = m_height * std::exp(iqzH) * (1.0 - std::exp(-1.0 * iqyW) - iqyW)
            / (q.y() * q.y() * m_width * m_width);
    else if (-1.0 == aaa / (q.y() * m_width))
        result = m_height * std::exp(iqzH) * (1.0 - std::exp(-1.0 * iqyW) + iqyW)
            / (q.y() * q.y() * m_width * m_width);
    else {
        complex_t iHqzdqy = complex_t(0.0, 1.0) * (q.z() * m_height + q.y() * m_d);
        complex_t Hqzdqy = q.z() * m_height + q.y() * m_d;
        result = std::cos(q.y() * m_width * 0.5)
            + 2.0 * iHqzdqy * std::sin(q.y() * m_width * 0.5) / (m_width * q.y());
        result = result * std::exp(-1.0 * iHqzdqy) - 1.0;
        result = result * 4.0 * m_height * std::exp(iqzH)
            / (4.0 * Hqzdqy * Hqzdqy - q.y() * q.y() * m_width * m_width);
    }
    return factor * result;
}

bool FormFactorRipple2::check_initialization() const
{
    bool result(true);
    std::string message;
    if (-1 * m_width > 2. * m_d) {
        result = false;
        message = std::string("Check for '-1*width <= 2.*asymmetry' failed.");
    }
    if (m_width < 2. * m_d) {
        result = false;
        message = std::string("Check for 'width >= 2.*asymmetry' failed.");
    }
    if (m_height <= 0) {
        result = false;
        message = std::string("Check for 'height > 0' failed.");
    }

    if (!result) {
        std::ostringstream ostr;
        ostr << "FormFactorRipple2() -> Error in class initialization with parameters ";
        ostr << " width:" << m_width;
        ostr << " height:" << m_height;
        ostr << " length:" << m_length;
        ostr << " asymmetry:" << m_d << "\n\n";
        ostr << message;
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    return result;
}
