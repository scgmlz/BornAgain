// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorBox.cpp
//! @brief     Implements class FormFactorBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorBox.h"
#include "BornAgainNamespace.h"
#include "MathFunctions.h"
#include "RealParameter.h"

//! @param length of rectangular base
//! @param width  of rectangular base
//! @param height of prism
FormFactorBox::FormFactorBox(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    setName(BornAgain::FFBoxType);
    registerParameter(BornAgain::Length, &m_length).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
}

complex_t FormFactorBox::evaluate_for_q(const cvector_t q) const
{
    complex_t qzHdiv2 = m_height / 2 * q.z();
    return m_height * m_length * m_width * MathFunctions::sinc(m_length / 2 * q.x())
        * MathFunctions::sinc(m_width / 2 * q.y()) * MathFunctions::sinc(qzHdiv2) * exp_I(qzHdiv2);
}
