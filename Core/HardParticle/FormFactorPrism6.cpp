// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPrism6.cpp
//! @brief     Implements class FormFactorPrism6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorPrism6.h"
#include "BornAgainNamespace.h"
#include "RealParameter.h"

FormFactorPrism6::FormFactorPrism6(const double base_edge, const double height)
    : FormFactorPolygonalPrism(height), m_base_edge(base_edge)
{
    setName(BornAgain::FFPrism6Type);
    registerParameter(BornAgain::BaseEdge, &m_base_edge).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    onChange();
}

void FormFactorPrism6::onChange()
{
    double a = m_base_edge;
    double as = a * sqrt(3) / 2;
    double ac = a / 2;
    std::vector<kvector_t> V{ { a, 0., 0. },  { ac, as, 0. },   { -ac, as, 0. },
                              { -a, 0., 0. }, { -ac, -as, 0. }, { ac, -as, 0. } };
    setPrism(true, V);
}
