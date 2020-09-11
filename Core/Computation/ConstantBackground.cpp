// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/ConstantBackground.cpp
//! @brief     Implements class ConstantBackground.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Computation/ConstantBackground.h"

ConstantBackground::ConstantBackground(const std::vector<double> P)
    : IBackground({"ConstantBackground",
                   "class_tooltip",
                   {{"BackgroundValue", "", "para_tooltip", 0, +INF, 0}}},
                  P),
      m_background_value(m_P[0])
{
}

ConstantBackground::ConstantBackground(double background_value)
    : ConstantBackground(std::vector<double>{background_value})
{
}

ConstantBackground* ConstantBackground::clone() const
{
    return new ConstantBackground(m_background_value);
}

double ConstantBackground::addBackGround(double intensity) const
{
    return intensity + m_background_value;
}
