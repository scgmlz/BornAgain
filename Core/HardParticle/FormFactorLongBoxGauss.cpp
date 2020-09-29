// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorLongBoxGauss.cpp
//! @brief     Implements class FormFactorLongBoxGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorLongBoxGauss.h"
#include "Core/Shapes/Box.h"
#include "Core/Tools/MathFunctions.h"

FormFactorLongBoxGauss::FormFactorLongBoxGauss(const std::vector<double> P)
    : IFormFactorBorn({"FormFactorLongBoxGauss",
                       "class_tooltip",
                       {{"Length", "nm", "para_tooltip", 0, +INF, 0},
                        {"Width", "nm", "para_tooltip", 0, +INF, 0},
                        {"Height", "nm", "para_tooltip", 0, +INF, 0}}},
                      P),
      m_length(m_P[0]), m_width(m_P[1]), m_height(m_P[2])
{
    onChange();
}

FormFactorLongBoxGauss::FormFactorLongBoxGauss(double length, double width, double height)
    : FormFactorLongBoxGauss(std::vector<double>{length, width, height})
{
}

complex_t FormFactorLongBoxGauss::evaluate_for_q(cvector_t q) const
{
    complex_t qxL2 = std::pow(m_length * q.x(), 2) / 2.0;
    complex_t qyWdiv2 = m_width * q.y() / 2.0;
    complex_t qzHdiv2 = m_height * q.z() / 2.0;

    return m_height * m_length * m_width * exp_I(qzHdiv2) * std::exp(-qxL2)
           * MathFunctions::sinc(qyWdiv2) * MathFunctions::sinc(qzHdiv2);
}

IFormFactor* FormFactorLongBoxGauss::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                     kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorLongBoxGauss slicedff(m_length, m_width,
                                    m_height - effects.dz_bottom - effects.dz_top);
    return createTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorLongBoxGauss::onChange()
{
    mP_shape.reset(new Box(m_length, m_width, m_height));
}
