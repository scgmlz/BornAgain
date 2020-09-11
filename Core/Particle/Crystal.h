// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/Crystal.h
//! @brief     Defines class Crystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARTICLE_CRYSTAL_H
#define BORNAGAIN_CORE_PARTICLE_CRYSTAL_H

#include "Core/Lattice/Lattice.h"
#include "Core/Particle/IClusteredParticles.h"
#include "Core/Vector/Vectors3D.h"

//! A crystal structure with a ParticleComposition as a basis.
//! Used in MesoCrystal, where it is given an outer shape.
//! @ingroup samples

class BA_CORE_API_ Crystal : public IClusteredParticles
{
public:
    Crystal(const IParticle& lattice_basis, const Lattice& lattice);
    ~Crystal();

    Crystal* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    IFormFactor* createTotalFormFactor(const IFormFactor& meso_crystal_form_factor,
                                       const IRotation* p_rotation,
                                       const kvector_t& translation) const override final;

    std::vector<HomogeneousRegion> homogeneousRegions() const override final;

    Lattice transformedLattice(const IRotation* p_rotation = nullptr) const;

    void setPositionVariance(double position_variance) { m_position_variance = position_variance; }

    std::vector<const INode*> getChildren() const override final;

private:
    Crystal(IParticle* p_lattice_basis, const Lattice& lattice);

    Lattice m_lattice;
    std::unique_ptr<IParticle> mp_lattice_basis;
    double m_position_variance;
};

#endif // BORNAGAIN_CORE_PARTICLE_CRYSTAL_H
