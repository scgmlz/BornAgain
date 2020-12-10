//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorBox.cpp
//! @brief     Implements class FormFactorBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/HardParticle/FormFactorBox.h"
#include "Base/Math/Functions.h"

FormFactorBox::FormFactorBox(const std::vector<double> P)
    : IFormFactorPrism({"Box",
                        "rectangular cuboid",
                        {{"Length", "nm", "side length in x direction", 0, +INF, 0},
                         {"Width", "nm", "side length in y direction", 0, +INF, 0},
                         {"Height", "nm", "side length in z direction", 0, +INF, 0}}},
                       P)
    , m_length(m_P[0])
    , m_width(m_P[1])
    , m_height(m_P[2]) {
    onChange();
}

FormFactorBox::FormFactorBox(double length, double width, double height)
    : FormFactorBox(std::vector<double>{length, width, height}) {}

complex_t FormFactorBox::evaluate_for_q(cvector_t q) const {
    complex_t qzHdiv2 = m_height / 2 * q.z();
    return m_length * m_width * m_height * Math::sinc(m_length / 2 * q.x())
           * Math::sinc(m_width / 2 * q.y()) * Math::sinc(qzHdiv2) * exp_I(qzHdiv2);
}

IFormFactor* FormFactorBox::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                            kvector_t translation) const {
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorBox slicedff(m_length, m_width, m_height - effects.dz_bottom - effects.dz_top);
    return createTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorBox::onChange() {
    double a = m_length / 2;
    double b = m_width / 2;
    std::vector<kvector_t> V{{a, b, 0.}, {-a, b, 0.}, {-a, -b, 0.}, {a, -b, 0}};
    setPrism(true, V);
}
