// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTriangle.cpp
//! @brief     Implements class FormFactorTriangle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorTriangle.h"
#include "BornAgainNamespace.h"
#include "RealLimits.h"
#include "RealParameter.h"

FormFactorTriangle::FormFactorTriangle(const double base_edge) : m_base_edge(base_edge)
{
    setName("Triangle");
    registerParameter(BornAgain::BaseEdge, &m_base_edge).setUnit("nm").setNonnegative();
    onChange();
}

void FormFactorTriangle::onChange()
{
    double a = m_base_edge;
    double as = a / 2;
    double ac = a / sqrt(3) / 2;
    double ah = a / sqrt(3);
    kvector_t V[3] = { { -ac, as, 0. }, { -ac, -as, 0. }, { ah, 0., 0. } };
    m_base = std::unique_ptr<PolyhedralFace>(new PolyhedralFace({ V[0], V[1], V[2] }, false));
}
