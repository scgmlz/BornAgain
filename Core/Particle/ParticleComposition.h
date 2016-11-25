// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleComposition.h
//! @brief     Defines class ParticleComposition.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLECOMPOSITION_H
#define PARTICLECOMPOSITION_H

#include "IParticle.h"

class IMaterial;

//! A composition of particles at fixed positions
//! @ingroup samples

class BA_CORE_API_ ParticleComposition : public IParticle
{
public:
    ParticleComposition();
    explicit ParticleComposition(const IParticle& particle);
    ParticleComposition(const IParticle& particle, kvector_t position);
    ParticleComposition(const IParticle& particle, std::vector<kvector_t> positions);

    virtual ~ParticleComposition();
    virtual ParticleComposition* clone() const;

    //! Returns a clone with inverted magnetic fields
    virtual ParticleComposition* cloneInvertB() const;

    virtual void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

    void addParticle(const IParticle& particle);
    void addParticle(const IParticle& particle, kvector_t position);
    void addParticles(const IParticle& particle, std::vector<kvector_t> positions);

    virtual void setAmbientMaterial(const IMaterial& material);
    virtual const IMaterial* getAmbientMaterial() const;

    //! Create a form factor for this particle with an extra scattering factor
    virtual IFormFactor*
    createTransformedFormFactor(const IRotation* p_rotation, kvector_t translation) const;

    //! Returns number of different particles
    size_t getNbrParticles() const { return m_particles.size(); }

    //! Returns particle with given index
    const IParticle* getParticle(size_t index) const;

    kvector_t getParticlePosition(size_t index) const;

private:
    size_t check_index(size_t index) const;

    //! Returns true if particle's type is suitable for adding
    void checkParticleType(const IParticle& p_particle);

    //! For internal use in cloneInvertB():
    void addParticlePointer(IParticle* p_particle);

    std::vector<IParticle*> m_particles;
    void initialize();
};

#endif // PARTICLECOMPOSITION_H
