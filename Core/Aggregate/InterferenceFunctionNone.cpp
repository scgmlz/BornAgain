// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/InterferenceFunctionNone.cpp
//! @brief     Implements class InterferenceFunctionNone.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Aggregate/InterferenceFunctionNone.h"

InterferenceFunctionNone::InterferenceFunctionNone() : IInterferenceFunction(0)
{
    setName("InterferenceNone");
}

InterferenceFunctionNone* InterferenceFunctionNone::clone() const
{
    auto* ret = new InterferenceFunctionNone();
    ret->setPositionVariance(m_position_var);
    return ret;
}

double InterferenceFunctionNone::iff_without_dw(const kvector_t) const
{
    return 1.0;
}
