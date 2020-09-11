// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleDistribution.cpp
//! @brief     Implements class ParticleDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Particle/ParticleDistribution.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/ParameterSample.h"
#include "Core/Parametrization/ParameterUtils.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Particle/IParticle.h"
#include <map>

ParticleDistribution::ParticleDistribution(const IParticle& prototype,
                                           const ParameterDistribution& par_distr)
    : m_par_distribution(par_distr)
{
    setName("ParticleDistribution");
    mP_particle.reset(prototype.clone());
    registerChild(mP_particle.get());
    mP_particle->registerAbundance(false);
    if (auto dist = m_par_distribution.getDistribution())
        registerChild(dist);
    registerParameter("Abundance", &m_abundance);
}

ParticleDistribution* ParticleDistribution::clone() const
{
    ParticleDistribution* p_result = new ParticleDistribution(*mP_particle, m_par_distribution);
    p_result->setAbundance(m_abundance);
    return p_result;
}

void ParticleDistribution::translate(kvector_t translation)
{
    mP_particle->translate(translation);
}

void ParticleDistribution::rotate(const IRotation& rotation)
{
    mP_particle->rotate(rotation);
}

//! Returns particle clones with parameter values drawn from distribution.

SafePointerVector<IParticle> ParticleDistribution::generateParticles() const
{
    std::unique_ptr<ParameterPool> P_pool{mP_particle->createParameterTree()};
    std::string main_par_name = m_par_distribution.getMainParameterName();
    double main_par_value = P_pool->getUniqueMatch(main_par_name)->value();

    // Preset link ratios:
    std::map<std::string, double> linked_ratios;
    for (const std::string& name : m_par_distribution.getLinkedParameterNames())
        linked_ratios[name] =
            main_par_value == 0 ? 1.0 : P_pool->getUniqueMatch(name)->value() / main_par_value;

    // Draw distribution samples; for each sample, create one particle clone:
    std::vector<ParameterSample> main_par_samples = m_par_distribution.generateSamples();
    SafePointerVector<IParticle> result;
    for (const ParameterSample& main_sample : main_par_samples) {
        IParticle* p_particle_clone = mP_particle->clone();
        std::unique_ptr<ParameterPool> P_new_pool{p_particle_clone->createParameterTree()};
        P_new_pool->setUniqueMatchValue(main_par_name, main_sample.value);
        for (auto it = linked_ratios.begin(); it != linked_ratios.end(); ++it)
            P_new_pool->setUniqueMatchValue(it->first, main_sample.value * it->second);
        p_particle_clone->setAbundance(abundance() * main_sample.weight);
        result.push_back(p_particle_clone);
    }
    return result;
}

std::vector<const INode*> ParticleDistribution::getChildren() const
{
    std::vector<const INode*> result = std::vector<const INode*>() << mP_particle;
    if (auto dist = m_par_distribution.getDistribution())
        result.push_back(dist);
    return result;
}

std::string ParticleDistribution::mainUnits() const
{
    return ParameterUtils::poolParameterUnits(prototype(),
                                              parameterDistribution().getMainParameterName());
}
