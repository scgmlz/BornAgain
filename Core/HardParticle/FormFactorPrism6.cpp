// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPrism6.cpp
//! @brief     Implements class FormFactorPrism6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorPrism6.h"

//! Constructor of a prism with a regular hexagonal base.
//! @param base_edge: length of the hexagonal base in nanometers
//! @param height: height in nanometers
FormFactorPrism6::FormFactorPrism6(const std::vector<double> P)
    : FormFactorPolygonalPrism({"Prism6",
                                "class_tooltip",
                                {{"BaseEdge", "nm", "para_tooltip", 0, +INF, 0},
                                 {"Height", "nm", "para_tooltip", 0, +INF, 0}}},
                               P),
      m_base_edge(m_P[0]), m_height(m_P[1])
{
    onChange();
}

FormFactorPrism6::FormFactorPrism6(double base_edge, double height)
    : FormFactorPrism6(std::vector<double>{base_edge, height})
{
}

IFormFactor* FormFactorPrism6::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                               kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorPrism6 slicedff(m_base_edge, m_height - effects.dz_bottom - effects.dz_top);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorPrism6::onChange()
{
    double a = m_base_edge;
    double as = a * sqrt(3) / 2;
    double ac = a / 2;
    std::vector<kvector_t> V{{a, 0., 0.},  {ac, as, 0.},   {-ac, as, 0.},
                             {-a, 0., 0.}, {-ac, -as, 0.}, {ac, -as, 0.}};
    setPrism(true, V);
}
