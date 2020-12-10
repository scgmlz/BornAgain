//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/ParticleDistribution.h
//! @brief     Defines class ParticleDistribution.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_PARTICLE_PARTICLEDISTRIBUTION_H
#define BORNAGAIN_SAMPLE_PARTICLE_PARTICLEDISTRIBUTION_H

#include "Base/Types/SafePointerVector.h"
#include "Param/Distrib/ParameterDistribution.h"
#include "Sample/Particle/IAbstractParticle.h"

class IParticle;

//! A particle type that is a parametric distribution of IParticle's.
//! @ingroup samples

class ParticleDistribution : public IAbstractParticle {
public:
    ParticleDistribution(const IParticle& prototype, const ParameterDistribution& par_distr);

    ParticleDistribution* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    void translate(kvector_t translation) final;

    void rotate(const IRotation& rotation) final;

    //! Returns list of new particles generated according to a distribution.
    SafePointerVector<IParticle> generateParticles() const;

    //! Returns the prototype particle, used for generating multiple ones
    const IParticle& prototype() const { return *m_particle.get(); }

    //! Returns the distributed parameter data
    ParameterDistribution parameterDistribution() const { return m_par_distribution; }

    std::vector<const INode*> getChildren() const final;

    std::string mainUnits() const;

private:
    std::unique_ptr<IParticle> m_particle;
    ParameterDistribution m_par_distribution;
};

#endif // BORNAGAIN_SAMPLE_PARTICLE_PARTICLEDISTRIBUTION_H
