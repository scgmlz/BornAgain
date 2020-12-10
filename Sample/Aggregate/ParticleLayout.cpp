//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/ParticleLayout.cpp
//! @brief     Implements class ParticleLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/Aggregate/ParticleLayout.h"
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include "Sample/Aggregate/InterferenceFunctionNone.h"
#include "Sample/Particle/Particle.h"
#include "Sample/Particle/ParticleDistribution.h"

namespace {

//! Returns true if interference function is able to calculate particle density automatically,
//! which is the case for 2D functions.
bool particleDensityIsProvidedByInterference(const IInterferenceFunction& iff) {
    return iff.getName() == "Interference2DLattice" || iff.getName() == "Interference2DParaCrystal"
           || iff.getName() == "Interference2DSuperLattice"
           || iff.getName() == "InterferenceFinite2DLattice"
           || iff.getName() == "InterferenceHardDisk";
}
} // namespace

ParticleLayout::ParticleLayout()
    : m_weight(1.0), m_total_particle_density(0.01), m_interference_function(nullptr) {
    setName("ParticleLayout");
    registerParticleDensity();
    registerWeight();
}

ParticleLayout::ParticleLayout(const IAbstractParticle& particle, double abundance)
    : m_weight(1.0), m_total_particle_density(0.01), m_interference_function(nullptr) {
    setName("ParticleLayout");
    addParticle(particle, abundance);
    registerParticleDensity();
    registerWeight();
}

ParticleLayout::~ParticleLayout() = default; // needs member class definitions => don't move to .h

ParticleLayout* ParticleLayout::clone() const {
    ParticleLayout* result = new ParticleLayout();

    for (const auto* particle : m_particles)
        result->addAndRegisterAbstractParticle(particle->clone());

    if (m_interference_function)
        result->setAndRegisterInterferenceFunction(m_interference_function->clone());

    result->setTotalParticleSurfaceDensity(totalParticleSurfaceDensity());
    result->setWeight(weight());

    return result;
}

//! Adds particle to the layout with abundance, position and the rotation defined.
//! @param particle to be added
//! @param abundance Particle abundance
//! @param position Particle position
//! @param rotation Particle rotation
void ParticleLayout::addParticle(const IAbstractParticle& particle, double abundance,
                                 const kvector_t position, const IRotation& rotation) {
    IAbstractParticle* particle_clone = particle.clone();
    if (abundance >= 0.0)
        particle_clone->setAbundance(abundance);
    if (!rotation.isIdentity())
        particle_clone->rotate(rotation);
    if (position != kvector_t(0, 0, 0))
        particle_clone->translate(position);
    addAndRegisterAbstractParticle(particle_clone);
}

//! Returns information on all particles (type and abundance)
//! and generates new particles if an IAbstractParticle denotes a collection
SafePointerVector<IParticle> ParticleLayout::particles() const {
    SafePointerVector<IParticle> particle_vector;
    for (const auto* particle : m_particles) {
        if (const auto* p_part_distr = dynamic_cast<const ParticleDistribution*>(particle)) {
            SafePointerVector<IParticle> generated_particles = p_part_distr->generateParticles();
            for (const IParticle* particle : generated_particles)
                particle_vector.push_back(particle->clone());
        } else if (const auto* p_iparticle = dynamic_cast<const IParticle*>(particle)) {
            particle_vector.push_back(p_iparticle->clone());
        }
    }
    return particle_vector;
}

const IInterferenceFunction* ParticleLayout::interferenceFunction() const {
    return m_interference_function.get();
}

double ParticleLayout::getTotalAbundance() const {
    double result = 0.0;
    for (const auto* particle : m_particles)
        result += particle->abundance();
    return result;
}

//! Adds interference functions
void ParticleLayout::setInterferenceFunction(const IInterferenceFunction& interference_function) {
    setAndRegisterInterferenceFunction(interference_function.clone());
}

double ParticleLayout::totalParticleSurfaceDensity() const {
    double iff_density =
        m_interference_function ? m_interference_function->getParticleDensity() : 0.0;
    return iff_density > 0.0 ? iff_density : m_total_particle_density;
}

//! Sets total particle surface density.
//! @param particle_density: number of particles per square nanometer
void ParticleLayout::setTotalParticleSurfaceDensity(double particle_density) {
    m_total_particle_density = particle_density;
}

std::vector<const INode*> ParticleLayout::getChildren() const {
    std::vector<const INode*> result;
    for (const auto* particle : m_particles)
        result.push_back(particle);
    result << m_interference_function;
    return result;
}

//! Adds particle information with simultaneous registration in parent class.
void ParticleLayout::addAndRegisterAbstractParticle(IAbstractParticle* child) {
    m_particles.push_back(child);
    registerChild(child);
}

//! Sets interference function with simultaneous registration in parent class
void ParticleLayout::setAndRegisterInterferenceFunction(IInterferenceFunction* child) {
    m_interference_function.reset(child);
    registerChild(child);

    if (particleDensityIsProvidedByInterference(*m_interference_function))
        registerParticleDensity(false);
    else
        registerParticleDensity(true);
}

void ParticleLayout::registerParticleDensity(bool make_registered) {
    if (make_registered) {
        if (!parameter("TotalParticleDensity"))
            registerParameter("TotalParticleDensity", &m_total_particle_density);
    } else {
        removeParameter("TotalParticleDensity");
    }
}

void ParticleLayout::registerWeight() {
    registerParameter("Weight", &m_weight);
}
