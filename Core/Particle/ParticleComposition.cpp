// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleComposition.cpp
//! @brief     Implements class ParticleComposition.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Particle/ParticleComposition.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Particle/FormFactorWeighted.h"
#include "Core/Particle/ParticleDistribution.h"

ParticleComposition::ParticleComposition()
{
    initialize();
}

ParticleComposition::ParticleComposition(const IParticle& particle,
                                         std::vector<kvector_t> positions)
{
    initialize();
    addParticles(particle, positions);
}

ParticleComposition::~ParticleComposition() {}

ParticleComposition* ParticleComposition::clone() const
{
    ParticleComposition* p_result = new ParticleComposition();
    p_result->setAbundance(m_abundance);
    for (size_t index = 0; index < m_particles.size(); ++index)
        p_result->addParticle(*m_particles[index]);
    if (mP_rotation)
        p_result->setRotation(*mP_rotation);
    p_result->setPosition(m_position);
    return p_result;
}

IFormFactor* ParticleComposition::createFormFactor() const
{
    if (m_particles.size() == 0)
        return {};
    std::unique_ptr<FormFactorWeighted> P_result{new FormFactorWeighted()};
    auto particles = decompose();
    for (auto p_particle : particles) {
        std::unique_ptr<IFormFactor> P_particle_ff{p_particle->createFormFactor()};
        P_result->addFormFactor(*P_particle_ff);
    }
    return P_result.release();
}

void ParticleComposition::addParticle(const IParticle& particle)
{
    IParticle* np = particle.clone();
    addParticlePointer(np);
}

void ParticleComposition::addParticle(const IParticle& particle, kvector_t position)
{
    IParticle* np = particle.clone();
    np->translate(position);
    addParticlePointer(np);
}

// Please note, that positions is not const reference here. This is intentional, to
// enable python lists to std::vector conversion
void ParticleComposition::addParticles(const IParticle& particle, std::vector<kvector_t> positions)
{
    for (size_t i = 0; i < positions.size(); ++i)
        addParticle(particle, positions[i]);
}

std::vector<const INode*> ParticleComposition::getChildren() const
{
    std::vector<const INode*> result = IParticle::getChildren();
    for (auto& P_particle : m_particles)
        result.push_back(P_particle.get());
    return result;
}

SafePointerVector<IParticle> ParticleComposition::decompose() const
{
    SafePointerVector<IParticle> result;
    auto p_rotation = rotation();
    auto translation = position();
    for (auto& P_particle : m_particles) {
        auto sublist = P_particle->decompose();
        for (auto p_subparticle : sublist) {
            if (p_rotation)
                p_subparticle->rotate(*p_rotation);
            p_subparticle->translate(translation);
            result.push_back(p_subparticle->clone());
        }
    }
    return result;
}

ParticleLimits ParticleComposition::bottomTopZ() const
{
    auto particles = decompose();
    ParticleLimits result = particles[check_index(0)]->bottomTopZ();
    for (auto& P_particle : particles) {
        ParticleLimits limits = P_particle->bottomTopZ();
        result.m_bottom = std::min(result.m_bottom, limits.m_bottom);
        result.m_top = std::max(result.m_top, limits.m_top);
    }
    return result;
}

size_t ParticleComposition::check_index(size_t index) const
{
    return index < m_particles.size()
               ? index
               : throw Exceptions::OutOfBoundsException(
                   "ParticleComposition::check_index() -> Index is out of bounds");
}

void ParticleComposition::addParticlePointer(IParticle* p_particle)
{
    p_particle->registerAbundance(false);
    registerChild(p_particle);
    m_particles.emplace_back(p_particle);
}

void ParticleComposition::initialize()
{
    setName("ParticleComposition");
    registerParticleProperties();
}
