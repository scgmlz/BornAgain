//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/Aggregate/ParticleLayout.h
//! @brief     Defines class ParticleLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_AGGREGATE_PARTICLELAYOUT_H
#define BORNAGAIN_SAMPLE_AGGREGATE_PARTICLELAYOUT_H

#include "Base/Types/SafePointerVector.h"
#include "Sample/Scattering/ISampleNode.h"
#include "Sample/Scattering/Rotations.h"
#include <memory>

class IAbstractParticle;
class IInterferenceFunction;
class IParticle;

//! Decorator class that adds particles to ISampleNode objects.
//! @ingroup samples

class ParticleLayout : public ISampleNode {
public:
    ParticleLayout();
    ParticleLayout(const IAbstractParticle& particle, double abundance = -1.0);
    ~ParticleLayout() override;

    ParticleLayout* clone() const override;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    void addParticle(const IAbstractParticle& particle, double abundance = -1.0,
                     const kvector_t position = {}, const IRotation& rotation = IdentityRotation());

    SafePointerVector<IParticle> particles() const;

    const IInterferenceFunction* interferenceFunction() const;

    double getTotalAbundance() const;

    void setInterferenceFunction(const IInterferenceFunction& interference_function);

    double totalParticleSurfaceDensity() const;
    void setTotalParticleSurfaceDensity(double particle_density);

    std::vector<const INode*> getChildren() const override;

    //! Returns the relative weight of this layout
    double weight() const { return m_weight; }

    //! Sets the relative weight of this layout
    void setWeight(double weight) { m_weight = weight; }

private:
    void addAndRegisterAbstractParticle(IAbstractParticle* child);
    void setAndRegisterInterferenceFunction(IInterferenceFunction* child);

    void registerParticleDensity(bool make_registered = true);
    void registerWeight();

    double m_weight;
    double m_total_particle_density;
    SafePointerVector<IAbstractParticle> m_particles; //!< Vector of particle types
    std::unique_ptr<IInterferenceFunction> m_interference_function;
};

#endif // BORNAGAIN_SAMPLE_AGGREGATE_PARTICLELAYOUT_H
