// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/ParticleDistribution.h
//! @brief     Defines class ParticleDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARTICLE_PARTICLEDISTRIBUTION_H
#define BORNAGAIN_CORE_PARTICLE_PARTICLEDISTRIBUTION_H

#include "Core/Parametrization/ParameterDistribution.h"
#include "Core/Particle/IAbstractParticle.h"
#include "Core/Tools/SafePointerVector.h"

class IParticle;

//! A particle type that is a parametric distribution of IParticle's.
//! @ingroup samples

class BA_CORE_API_ ParticleDistribution : public IAbstractParticle
{
public:
    ParticleDistribution(const IParticle& prototype, const ParameterDistribution& par_distr);

    ParticleDistribution* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    void translate(kvector_t translation) override final;

    void rotate(const IRotation& rotation) override final;

    //! Returns list of new particles generated according to a distribution.
    SafePointerVector<IParticle> generateParticles() const;

    //! Returns the prototype particle, used for generating multiple ones
    const IParticle& prototype() const { return *mP_particle.get(); }

    //! Returns the distributed parameter data
    ParameterDistribution parameterDistribution() const { return m_par_distribution; }

    std::vector<const INode*> getChildren() const override final;

    std::string mainUnits() const;

private:
    std::unique_ptr<IParticle> mP_particle;
    ParameterDistribution m_par_distribution;
};

#endif // BORNAGAIN_CORE_PARTICLE_PARTICLEDISTRIBUTION_H
