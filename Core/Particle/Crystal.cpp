// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/Crystal.cpp
//! @brief     Implements class Crystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Particle/Crystal.h"
#include "Core/Particle/FormFactorCrystal.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleComposition.h"

Crystal::Crystal(const IParticle& lattice_basis, const Lattice& lattice)
    : m_lattice(lattice), m_position_variance(0.0)
{
    setName("Crystal");
    mp_lattice_basis.reset(lattice_basis.clone());
    mp_lattice_basis->registerAbundance(false);
    registerChild(mp_lattice_basis.get());
    registerChild(&m_lattice);
}

Crystal::~Crystal() {}

Crystal* Crystal::clone() const
{
    Crystal* p_new = new Crystal(*mp_lattice_basis, m_lattice);
    p_new->setPositionVariance(m_position_variance);
    return p_new;
}

IFormFactor* Crystal::createTotalFormFactor(const IFormFactor& meso_crystal_form_factor,
                                            const IRotation* p_rotation,
                                            const kvector_t& translation) const
{
    Lattice transformed_lattice = transformedLattice(p_rotation);
    std::unique_ptr<IParticle> P_basis_clone{mp_lattice_basis->clone()};
    if (p_rotation)
        P_basis_clone->rotate(*p_rotation);
    P_basis_clone->translate(translation);
    const std::unique_ptr<IFormFactor> P_basis_ff(P_basis_clone->createFormFactor());
    std::unique_ptr<FormFactorCrystal> P_ff_crystal(new FormFactorCrystal(
        transformed_lattice, *P_basis_ff, meso_crystal_form_factor, m_position_variance));
    return P_ff_crystal.release();
}

std::vector<HomogeneousRegion> Crystal::homogeneousRegions() const
{
    std::vector<HomogeneousRegion> result;
    double unit_cell_volume = m_lattice.volume();
    if (unit_cell_volume <= 0)
        return {};
    auto particles = mp_lattice_basis->decompose();
    ZLimits limits;
    for (auto p_particle : particles) {
        auto sliced_particle = p_particle->createSlicedParticle(limits);
        result.insert(result.end(), sliced_particle.m_regions.begin(),
                      sliced_particle.m_regions.end());
    }
    for (auto& region : result)
        region.m_volume /= unit_cell_volume;
    return result;
}

Lattice Crystal::transformedLattice(const IRotation* p_rotation) const
{
    if (p_rotation)
        return m_lattice.createTransformedLattice(p_rotation->getTransform3D());
    else
        return m_lattice;
}

std::vector<const INode*> Crystal::getChildren() const
{
    return std::vector<const INode*>() << mp_lattice_basis << &m_lattice;
}

Crystal::Crystal(IParticle* p_lattice_basis, const Lattice& lattice)
    : m_lattice(lattice), m_position_variance(0.0)
{
    setName("Crystal");
    mp_lattice_basis.reset(p_lattice_basis);
    registerChild(mp_lattice_basis.get());
    registerChild(&m_lattice);
}
