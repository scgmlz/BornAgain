// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/IAbstractParticle.cpp
//! @brief     Defines interface IAParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Particle/IAbstractParticle.h"

IAbstractParticle::IAbstractParticle(const NodeMeta& meta, const std::vector<double>& PValues)
    : ISample(meta, PValues)
{
}

void IAbstractParticle::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}
