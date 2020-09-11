// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/ParticleLayout.cpp
//! @brief     Implements class ParticleLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Aggregate/ParticleLayout.h"
#include "Core/Aggregate/IInterferenceFunction.h"
#include "Core/Aggregate/InterferenceFunctionNone.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/Particle.h"
#include "Core/Particle/ParticleDistribution.h"

namespace
{

//! Returns true if interference function is able to calculate particle density automatically,
//! which is the case for 2D functions.
bool particleDensityIsProvidedByInterference(const IInterferenceFunction& iff)
{
    if (iff.getName() == "Interference2DLattice" || iff.getName() == "Interference2DParaCrystal"
        || iff.getName() == "Interference2DSuperLattice"
        || iff.getName() == "InterferenceFinite2DLattice"
        || iff.getName() == "InterferenceHardDisk")
        return true;
    return false;
}
} // namespace

ParticleLayout::ParticleLayout() : mP_interference_function{nullptr}, m_total_particle_density{0.01}
{
    setName("ParticleLayout");
    registerParticleDensity();
    registerWeight();
}

ParticleLayout::ParticleLayout(const IAbstractParticle& particle, double abundance)
    : mP_interference_function{nullptr}, m_total_particle_density{0.01}
{
    setName("ParticleLayout");
    addParticle(particle, abundance);
    registerParticleDensity();
    registerWeight();
}

ParticleLayout::~ParticleLayout() {} // needs member class definitions => don't move to .h

ParticleLayout* ParticleLayout::clone() const
{
    ParticleLayout* p_result = new ParticleLayout();

    for (auto p_particle : m_particles)
        p_result->addAndRegisterAbstractParticle(p_particle->clone());

    if (mP_interference_function)
        p_result->setAndRegisterInterferenceFunction(mP_interference_function->clone());

    p_result->setTotalParticleSurfaceDensity(totalParticleSurfaceDensity());
    p_result->setWeight(weight());

    return p_result;
}

//! Adds particle to the layout with abundance, position and the rotation defined.
//! @param particle to be added
//! @param abundance Particle abundance
//! @param position Particle position
//! @param rotation Particle rotation
void ParticleLayout::addParticle(const IAbstractParticle& particle, double abundance,
                                 const kvector_t position, const IRotation& rotation)
{
    std::unique_ptr<IAbstractParticle> P_particle_clone{particle.clone()};
    if (abundance >= 0.0)
        P_particle_clone->setAbundance(abundance);
    if (!rotation.isIdentity())
        P_particle_clone->rotate(rotation);
    if (position != kvector_t(0, 0, 0))
        P_particle_clone->translate(position);
    addAndRegisterAbstractParticle(P_particle_clone.release());
}

//! Returns information on all particles (type and abundance)
//! and generates new particles if an IAbstractParticle denotes a collection
SafePointerVector<IParticle> ParticleLayout::particles() const
{
    SafePointerVector<IParticle> particle_vector;
    for (auto particle : m_particles) {
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

const IInterferenceFunction* ParticleLayout::interferenceFunction() const
{
    return mP_interference_function.get();
}

double ParticleLayout::getTotalAbundance() const
{
    double result = 0.0;
    for (auto p_particle : m_particles) {
        result += p_particle->abundance();
    }
    return result;
}

//! Adds interference functions
void ParticleLayout::setInterferenceFunction(const IInterferenceFunction& interference_function)
{
    setAndRegisterInterferenceFunction(interference_function.clone());
}

double ParticleLayout::totalParticleSurfaceDensity() const
{
    double iff_density =
        mP_interference_function ? mP_interference_function->getParticleDensity() : 0.0;
    return iff_density > 0.0 ? iff_density : m_total_particle_density;
}

//! Sets total particle surface density.
//! @param particle_density: number of particles per square nanometer
void ParticleLayout::setTotalParticleSurfaceDensity(double particle_density)
{
    m_total_particle_density = particle_density;
}

std::vector<const INode*> ParticleLayout::getChildren() const
{
    std::vector<const INode*> result;
    for (auto particle : m_particles)
        result.push_back(particle);
    result << mP_interference_function;
    return result;
}

//! Adds particle information with simultaneous registration in parent class.
void ParticleLayout::addAndRegisterAbstractParticle(IAbstractParticle* child)
{
    m_particles.push_back(child);
    registerChild(child);
}

//! Sets interference function with simultaneous registration in parent class
void ParticleLayout::setAndRegisterInterferenceFunction(IInterferenceFunction* child)
{
    mP_interference_function.reset(child);
    registerChild(child);

    if (particleDensityIsProvidedByInterference(*mP_interference_function))
        registerParticleDensity(false);
    else
        registerParticleDensity(true);
}

void ParticleLayout::registerParticleDensity(bool make_registered)
{
    if (make_registered) {
        if (!parameter("TotalParticleDensity"))
            registerParameter("TotalParticleDensity", &m_total_particle_density);
    } else {
        removeParameter("TotalParticleDensity");
    }
}

void ParticleLayout::registerWeight()
{
    registerParameter("Weight", &m_weight);
}
