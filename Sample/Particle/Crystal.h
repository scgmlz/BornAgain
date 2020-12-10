//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/Crystal.h
//! @brief     Defines class Crystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_PARTICLE_CRYSTAL_H
#define BORNAGAIN_SAMPLE_PARTICLE_CRYSTAL_H

#include "Sample/Lattice/Lattice3D.h"
#include "Sample/Scattering/ISampleNode.h"

class IFormFactor;
class IRotation;
struct HomogeneousRegion;

//! A crystal structure, defined by a Bravais lattice, a basis, and a position variance.
//!
//! The basis is either a Particle or a ParticleComposition.
//!
//! Computations are delegated to class FormFactorCrystal.
//!
//! Used in MesoCrystal, where it is given an outer shape.
//!
//! @ingroup samples

class Crystal : public ISampleNode {
public:
    Crystal(const IParticle& basis, const Lattice3D& lattice, double position_variance = 0);
    ~Crystal();

    Crystal* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    IFormFactor* createTotalFormFactor(const IFormFactor& meso_crystal_form_factor,
                                       const IRotation* p_rotation,
                                       const kvector_t& translation) const;

    std::vector<HomogeneousRegion> homogeneousRegions() const;

    Lattice3D transformedLattice(const IRotation* p_rotation = nullptr) const;

    std::vector<const INode*> getChildren() const final;

private:
    Crystal(IParticle* p_basis, const Lattice3D& lattice, double position_variance = 0);

    Lattice3D m_lattice;
    std::unique_ptr<IParticle> m_basis;
    const double m_position_variance;
};

#endif // BORNAGAIN_SAMPLE_PARTICLE_CRYSTAL_H
