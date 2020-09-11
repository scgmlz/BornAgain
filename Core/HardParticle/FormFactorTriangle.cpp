// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTriangle.cpp
//! @brief     Implements class FormFactorTriangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorTriangle.h"
#include "Fit/Tools/RealLimits.h"

FormFactorTriangle::FormFactorTriangle(const std::vector<double> P)
    : FormFactorPolygonalSurface(
        {"Triangle", "class_tooltip", {{"BaseEdge", "nm", "para_tooltip", 0, +INF, 0}}}, P),
      m_base_edge(m_P[0])
{
    onChange();
}

FormFactorTriangle::FormFactorTriangle(double base_edge)
    : FormFactorTriangle(std::vector<double>{base_edge})
{
}

void FormFactorTriangle::onChange()
{
    double a = m_base_edge;
    double as = a / 2;
    double ac = a / sqrt(3) / 2;
    double ah = a / sqrt(3);
    kvector_t V[3] = {{-ac, as, 0.}, {-ac, -as, 0.}, {ah, 0., 0.}};
    m_base = std::unique_ptr<PolyhedralFace>(new PolyhedralFace({V[0], V[1], V[2]}, false));
}
