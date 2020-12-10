//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorPrism3.cpp
//! @brief     Implements class FormFactorPrism3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/HardParticle/FormFactorPrism3.h"
#include <iostream>

FormFactorPrism3::FormFactorPrism3(const std::vector<double> P)
    : IFormFactorPrism({"Prism3",
                        "prism with regular trigonal base",
                        {{"BaseEdge", "nm", "edge length of trigonal base", 0, +INF, 0},
                         {"Height", "nm", "height", 0, +INF, 0}}},
                       P)
    , m_base_edge(m_P[0])
    , m_height(m_P[1]) {
    onChange();
}

FormFactorPrism3::FormFactorPrism3(double base_edge, double height)
    : FormFactorPrism3(std::vector<double>{base_edge, height}) {}

IFormFactor* FormFactorPrism3::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                               kvector_t translation) const {
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorPrism3 slicedff(m_base_edge, m_height - effects.dz_bottom - effects.dz_top);
    return createTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorPrism3::onChange() {
    double a = m_base_edge;
    double as = a / 2;
    double ac = a / sqrt(3) / 2;
    double ah = a / sqrt(3);
    std::vector<kvector_t> V{{-ac, as, 0.}, {-ac, -as, 0.}, {ah, 0., 0.}};
    setPrism(false, V);
}
