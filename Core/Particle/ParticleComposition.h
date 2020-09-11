// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleComposition.h
//! @brief     Defines class ParticleComposition.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARTICLE_PARTICLECOMPOSITION_H
#define BORNAGAIN_CORE_PARTICLE_PARTICLECOMPOSITION_H

#include "Core/Particle/IParticle.h"
#include <memory>

//! A composition of particles at fixed positions
//! @ingroup samples

class BA_CORE_API_ ParticleComposition : public IParticle
{
public:
    ParticleComposition();
    ParticleComposition(const IParticle& particle, std::vector<kvector_t> positions);

    ~ParticleComposition();
    ParticleComposition* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    IFormFactor* createFormFactor() const override final;

    void addParticle(const IParticle& particle);
    void addParticle(const IParticle& particle, kvector_t position);
    void addParticles(const IParticle& particle, std::vector<kvector_t> positions);

    //! Returns number of different particles
    size_t nbrParticles() const { return m_particles.size(); }

    std::vector<const INode*> getChildren() const override final;

    SafePointerVector<IParticle> decompose() const override final;

    ParticleLimits bottomTopZ() const override final;

private:
    size_t check_index(size_t index) const;

    //! For internal use
    void addParticlePointer(IParticle* p_particle);

    std::vector<std::unique_ptr<IParticle>> m_particles;
    void initialize();
};

#endif // BORNAGAIN_CORE_PARTICLE_PARTICLECOMPOSITION_H
