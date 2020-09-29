// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/IFormFactorPolyhedron.cpp
//! @brief     Implements class IFormFactorPolyhedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

//! The mathematics implemented here is described in full detail in a paper
//! by Joachim Wuttke, entitled
//! "Form factor (Fourier shape transform) of polygon and polyhedron."

#include "Core/HardParticle/IFormFactorPolyhedron.h"
#include "Core/HardParticle/Polyhedron.h"

#ifdef POLYHEDRAL_DIAGNOSTIC // TODO restore
void IFormFactorPolyhedron::setLimits(double _q, int _n)
{
    q_limit_series = _q;
    n_limit_series = _n;
}
#endif

IFormFactorPolyhedron::IFormFactorPolyhedron(const NodeMeta& meta,
                                             const std::vector<double>& PValues)
    : IFormFactorBorn(meta, PValues)
{
}

IFormFactorPolyhedron::~IFormFactorPolyhedron() = default;

//! Called by child classes to set faces and other internal variables.

void IFormFactorPolyhedron::setPolyhedron(const PolyhedralTopology& topology, double z_bottom,
                                          const std::vector<kvector_t>& vertices)
{
    pimpl = std::make_unique<Polyhedron>(topology, z_bottom, vertices);
}

double IFormFactorPolyhedron::bottomZ(const IRotation& rotation) const
{
    return BottomZ(pimpl->vertices(), rotation);
}

double IFormFactorPolyhedron::topZ(const IRotation& rotation) const
{
    return TopZ(pimpl->vertices(), rotation);
}

complex_t IFormFactorPolyhedron::evaluate_for_q(cvector_t q) const
{
    return pimpl->evaluate_for_q(q);
}

complex_t IFormFactorPolyhedron::evaluate_centered(cvector_t q) const
{
    return pimpl->evaluate_centered(q);
}

double IFormFactorPolyhedron::volume() const
{
    return pimpl->volume();
}
double IFormFactorPolyhedron::radialExtension() const
{
    return pimpl->radius();
}

//! Assertions for Platonic solid.

void IFormFactorPolyhedron::assert_platonic() const
{
    pimpl->assert_platonic();
}
