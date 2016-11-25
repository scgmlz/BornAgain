// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongBoxLorentz.cpp
//! @brief     Implements class FormFactorLongBoxLorentz.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorLongBoxLorentz.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "RealParameter.h"

FormFactorLongBoxLorentz::FormFactorLongBoxLorentz(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    setName(BornAgain::FFLongBoxLorentzType);
    registerParameter(BornAgain::Length, &m_length).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
}

complex_t FormFactorLongBoxLorentz::evaluate_for_q(const cvector_t q) const
{
    complex_t qxL2 = 2.5 * std::pow(m_length * q.x(), 2);
    complex_t qyWdiv2 = m_width * q.y() / 2.0;
    complex_t qzHdiv2 = m_height * q.z() / 2.0;

    return m_height * m_length * m_width * std::exp(complex_t(0., 1.) * qzHdiv2) / (1.0 + qxL2)
        * MathFunctions::sinc(qyWdiv2) * MathFunctions::sinc(qzHdiv2);
}
