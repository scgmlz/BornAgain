// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongBox.cpp
//! @brief     Implements class FormFactorLongBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FormFactorLongBox.h"
#include "BornAgainNamespace.h"
#include "Box.h"
#include "MathFunctions.h"
#include "RealParameter.h"

FormFactorLongBox::FormFactorLongBox(double length, double width, double height)
    : m_length(length), m_width(width), m_height(height)
{
    setName(BornAgain::FFLongBoxType);
    registerParameter(BornAgain::Length, &m_length).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Width, &m_width).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    onChange();
}

complex_t FormFactorLongBox::evaluate_for_q(cvector_t q) const
{
    complex_t qxL2 = std::pow(m_length * q.x() / 2.0, 2);
    complex_t qyWdiv2 = m_width * q.y() / 2.0;
    complex_t qzHdiv2 = m_height * q.z() / 2.0;

    return m_height * m_length * m_width * exp_I(qzHdiv2)
            * MathFunctions::sinc(qyWdiv2) * MathFunctions::sinc(qzHdiv2)
            / std::sqrt(1.0 + qxL2);
}

IFormFactor* FormFactorLongBox::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                     kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorLongBox slicedff(m_length, m_width, m_height - effects.dz_bottom - effects.dz_top);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorLongBox::onChange()
{
    mP_shape.reset(new Box(m_length, m_width, m_height));
}
