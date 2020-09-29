// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/IFormFactorPrism.cpp
//! @brief     Implements class IFormFactorPrism.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/IFormFactorPrism.h"
#include "Core/HardParticle/Prism.h"

IFormFactorPrism::IFormFactorPrism(const NodeMeta& meta, const std::vector<double>& PValues)
    : IFormFactorBorn(meta, PValues)
{
}

IFormFactorPrism::~IFormFactorPrism() = default;

void IFormFactorPrism::setPrism(bool symmetry_Ci, const std::vector<kvector_t>& vertices)
{
    pimpl = std::make_unique<Prism>(symmetry_Ci, height(), vertices);
}

double IFormFactorPrism::bottomZ(const IRotation& rotation) const
{
    return BottomZ(pimpl->vertices(), rotation);
}

double IFormFactorPrism::topZ(const IRotation& rotation) const
{
    return TopZ(pimpl->vertices(), rotation);
}

//! Returns the volume of this prism.
double IFormFactorPrism::volume() const
{
    return height() * pimpl->area();
}

double IFormFactorPrism::getHeight() const
{
    return height();
}
double IFormFactorPrism::radialExtension() const
{
    return std::sqrt(pimpl->area());
}

//! Returns the form factor F(q) of this polyhedron, respecting the offset height/2.

complex_t IFormFactorPrism::evaluate_for_q(cvector_t q) const
{
    return pimpl->evaluate_for_q(q);
}
