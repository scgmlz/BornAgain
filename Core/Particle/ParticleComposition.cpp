// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleComposition.cpp
//! @brief     Implements class ParticleComposition.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParticleComposition.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "FormFactorWeighted.h"
#include "IMaterial.h"
#include "ParticleDistribution.h"

ParticleComposition::ParticleComposition()
{
    initialize();
}

ParticleComposition::ParticleComposition(const IParticle& particle)
{
    initialize();
    addParticle( particle, kvector_t(0.0, 0.0, 0.0) );
}

ParticleComposition::ParticleComposition(const IParticle &particle, kvector_t position)
{
    initialize();
    addParticle(particle, position);
}

ParticleComposition::ParticleComposition(const IParticle& particle,
        std::vector<kvector_t> positions)
{
    initialize();
    addParticles(particle, positions);
}

ParticleComposition::~ParticleComposition()
{
    for (size_t index=0; index<m_particles.size(); ++index)
        delete m_particles[index];
}

ParticleComposition* ParticleComposition::clone() const
{
    ParticleComposition* p_result = new ParticleComposition();
    p_result->setAbundance(m_abundance);
    for (size_t index=0; index<m_particles.size(); ++index)
        p_result->addParticle(*m_particles[index]);
    p_result->setAmbientMaterial(*getAmbientMaterial());
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

ParticleComposition* ParticleComposition::cloneInvertB() const
{
    ParticleComposition* p_result = new ParticleComposition();
    p_result->setAbundance(m_abundance);
    for (size_t index=0; index<m_particles.size(); ++index)
        p_result->addParticlePointer(m_particles[index]->cloneInvertB());

    if (getAmbientMaterial())
        p_result->setAmbientMaterial(*getAmbientMaterial()->cloneInverted());
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

void ParticleComposition::addParticle(const IParticle &particle)
{
    checkParticleType(particle);
    IParticle* np = particle.clone();
    registerChild(np);
    m_particles.push_back(np);
}

void ParticleComposition::addParticle(const IParticle& particle, kvector_t position)
{
    checkParticleType(particle);
    IParticle* np = particle.clone();
    np->applyTranslation(position);
    registerChild(np);
    m_particles.push_back(np);
}

// Please note, that positions is not const reference here. This is intentionally to
// python lists to std::vector
void ParticleComposition::addParticles(const IParticle& particle,
        std::vector<kvector_t > positions)
{
    for (size_t i=0; i<positions.size(); ++i)
        addParticle(particle, positions[i]);
}

void ParticleComposition::setAmbientMaterial(const IMaterial& material)
{
    for (size_t index=0; index<m_particles.size(); ++index)
        m_particles[index]->setAmbientMaterial(material);
}

const IMaterial* ParticleComposition::getAmbientMaterial() const
{
    if (m_particles.size()==0) return 0;
    return m_particles[0]->getAmbientMaterial();
}

IFormFactor*
ParticleComposition::createTransformedFormFactor(const IRotation* p_rotation,
                                                 kvector_t translation) const
{
    if (m_particles.size() == 0)
        return 0;
    const std::unique_ptr<IRotation> P_total_rotation(createComposedRotation(p_rotation));
    kvector_t total_position = getComposedTranslation(p_rotation, translation);
    FormFactorWeighted* p_result = new FormFactorWeighted();
    for (size_t index = 0; index < m_particles.size(); ++index) {
        const std::unique_ptr<IFormFactor> P_particle_ff(
            m_particles[index]->createTransformedFormFactor(P_total_rotation.get(),
                                                            total_position));
        p_result->addFormFactor(*P_particle_ff);
    }
    return p_result;
}

const IParticle* ParticleComposition::getParticle(size_t index) const
{
    return m_particles[check_index(index)];
}

kvector_t ParticleComposition::getParticlePosition(size_t index) const
{
    return m_particles[check_index(index)]->getPosition();
}

size_t ParticleComposition::check_index(size_t index) const
{
    return index < m_particles.size() ? index : throw Exceptions::OutOfBoundsException(
        "ParticleComposition::check_index() -> Index is out of bounds");
}

void ParticleComposition::checkParticleType(const IParticle &p_particle)
{
    const ParticleDistribution* p_distr = dynamic_cast<const ParticleDistribution*>(&p_particle);
    if (p_distr)
        throw Exceptions::ClassInitializationException("ParticleComposition::checkParticleType: "
                                                       "cannot add ParticleDistribution!");
}

void ParticleComposition::addParticlePointer(IParticle* p_particle)
{
    registerChild(p_particle);
    m_particles.push_back(p_particle);
}

void ParticleComposition::initialize()
{
    setName(BornAgain::ParticleCompositionType);
    registerPosition();
}
