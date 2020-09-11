// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/ParticleLayout.h
//! @brief     Defines class ParticleLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_AGGREGATE_PARTICLELAYOUT_H
#define BORNAGAIN_CORE_AGGREGATE_PARTICLELAYOUT_H

#include "Core/Correlations/ILayout.h"
#include "Core/Scattering/Rotations.h"
#include "Core/Vector/Vectors3D.h"
#include <memory>

class IAbstractParticle;
class IInterferenceFunction;
class IParticle;

//! Decorator class that adds particles to ISample objects.
//! @ingroup samples

class BA_CORE_API_ ParticleLayout : public ILayout
{
public:
    ParticleLayout();
    ParticleLayout(const IAbstractParticle& particle, double abundance = -1.0);
    ~ParticleLayout() override;

    ParticleLayout* clone() const final override;

    void accept(INodeVisitor* visitor) const final override { visitor->visit(this); }

    void addParticle(const IAbstractParticle& particle, double abundance = -1.0,
                     const kvector_t position = {}, const IRotation& rotation = IdentityRotation());

    SafePointerVector<IParticle> particles() const final override;

    const IInterferenceFunction* interferenceFunction() const final override;

    double getTotalAbundance() const final override;

    void setInterferenceFunction(const IInterferenceFunction& interference_function);

    double totalParticleSurfaceDensity() const final override;
    void setTotalParticleSurfaceDensity(double particle_density) final override;

    std::vector<const INode*> getChildren() const final override;

private:
    void addAndRegisterAbstractParticle(IAbstractParticle* child);
    void setAndRegisterInterferenceFunction(IInterferenceFunction* child);

    void registerParticleDensity(bool make_registered = true);
    void registerWeight();

    SafePointerVector<IAbstractParticle> m_particles; //!< Vector of particle types
    std::unique_ptr<IInterferenceFunction> mP_interference_function;
    double m_total_particle_density;
};

#endif // BORNAGAIN_CORE_AGGREGATE_PARTICLELAYOUT_H
