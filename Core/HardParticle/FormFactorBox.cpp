// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorBox.cpp
//! @brief     Implements class FormFactorBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorBox.h"
#include "Core/Tools/MathFunctions.h"

//! Constructor of a rectangular cuboid.
//! @param length: length of the base in nanometers
//! @param width: width of the base in nanometers
//! @param height: height of the box in nanometers
FormFactorBox::FormFactorBox(const std::vector<double> P)
    : FormFactorPolygonalPrism({"Box",
                                "class_tooltip",
                                {{"Length", "nm", "para_tooltip", 0, +INF, 0},
                                 {"Width", "nm", "para_tooltip", 0, +INF, 0},
                                 {"Height", "nm", "para_tooltip", 0, +INF, 0}}},
                               P),
      m_length(m_P[0]), m_width(m_P[1]), m_height(m_P[2])
{
    onChange();
}

FormFactorBox::FormFactorBox(double length, double width, double height)
    : FormFactorBox(std::vector<double>{length, width, height})
{
}

complex_t FormFactorBox::evaluate_for_q(cvector_t q) const
{
    complex_t qzHdiv2 = m_height / 2 * q.z();
    return m_length * m_width * m_height * MathFunctions::sinc(m_length / 2 * q.x())
           * MathFunctions::sinc(m_width / 2 * q.y()) * MathFunctions::sinc(qzHdiv2)
           * exp_I(qzHdiv2);
}

IFormFactor* FormFactorBox::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                            kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorBox slicedff(m_length, m_width, m_height - effects.dz_bottom - effects.dz_top);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorBox::onChange()
{
    double a = m_length / 2;
    double b = m_width / 2;
    std::vector<kvector_t> V{{a, b, 0.}, {-a, b, 0.}, {-a, -b, 0.}, {a, -b, 0}};
    setPrism(true, V);
}
