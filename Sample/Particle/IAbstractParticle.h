//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Particle/IAbstractParticle.h
//! @brief     Defines interface IAbstractParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_PARTICLE_IABSTRACTPARTICLE_H
#define BORNAGAIN_SAMPLE_PARTICLE_IABSTRACTPARTICLE_H

#include "Sample/Scattering/ISampleNode.h"

class IRotation;

//! Interface for a generic particle.
//!
//! Inherited by IParticle and ParticleDistribution.

//! @ingroup samples

class IAbstractParticle : public ISampleNode {
public:
    IAbstractParticle() = default;
    IAbstractParticle(const NodeMeta& meta, const std::vector<double>& PValues);
    virtual ~IAbstractParticle() = default;

    virtual IAbstractParticle* clone() const = 0;

    virtual void accept(INodeVisitor* visitor) const;

    double abundance() const { return m_abundance; }

    //! Sets particle abundance.
    //! @param abundance: proportion of this type of particles normalized to the
    //! total number of particles in the layout.
    void setAbundance(double abundance) { m_abundance = abundance; }

    //! Translates the particle with the given vector
    virtual void translate(kvector_t translation) = 0;

    //! Applies the given rotation to the particle
    virtual void rotate(const IRotation& rotation) = 0;

protected:
    double m_abundance{1.0}; // not a Parameter
};

#endif // BORNAGAIN_SAMPLE_PARTICLE_IABSTRACTPARTICLE_H
#endif // USER_API
