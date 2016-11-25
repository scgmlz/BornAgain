// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/Crystal.h
//! @brief     Defines class Crystal.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "IClusteredParticles.h"
#include "Lattice.h"
#include "Vectors3D.h"

class Particle;
class ParticleComposition;

//! A crystal structure with a ParticleComposition as a basis.
//!   Used in MesoCrystal, where it is given an outer shape.
//! @ingroup samples

class BA_CORE_API_ Crystal : public IClusteredParticles
{
public:
    Crystal(const ParticleComposition& lattice_basis, const Lattice& lattice);
    virtual ~Crystal();

    Crystal* clone() const final;
    Crystal* cloneInvertB() const final;

    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    void setAmbientMaterial(const IMaterial& material) final;
    const IMaterial* getAmbientMaterial() const final;

    virtual IFormFactor* createTotalFormFactor(
        const IFormFactor& meso_crystal_form_factor, const IRotation* p_rotation,
        const kvector_t& translation) const;

    Lattice getTransformedLattice(const IRotation* p_rotation) const;

    const ParticleComposition* getLatticeBasis() const { return mp_lattice_basis; }

    void setDWFactor(double dw_factor) { m_dw_factor = dw_factor; }

private:
    //! Private constructor
    Crystal(ParticleComposition* p_lattice_basis, const Lattice& lattice);

    Lattice m_lattice;
    ParticleComposition* mp_lattice_basis;
    double m_dw_factor;
};

#endif // CRYSTAL_H
