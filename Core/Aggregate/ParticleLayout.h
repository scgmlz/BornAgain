// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/ParticleLayout.h
//! @brief     Defines class ParticleLayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLELAYOUT_H
#define PARTICLELAYOUT_H

#include "ILayout.h"
#include "Vectors3D.h"
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
    ParticleLayout(const IAbstractParticle& particle);
    ParticleLayout(const IAbstractParticle& particle, double abundance);
    ~ParticleLayout() final;

    ParticleLayout* clone() const final;
    ParticleLayout* cloneInvertB() const final;

    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    void addParticle(const IAbstractParticle& particle);
    void addParticle(const IAbstractParticle& particle, double abundance); // TODO delete this
    void addParticle(const IParticle& particle, double abundance, const kvector_t position);
    void addParticle(
        const IParticle& particle, double abundance, const kvector_t position,
        const IRotation& rotation);

    size_t getNumberOfParticles() const final { return m_particles.size(); }

    const IAbstractParticle* getParticle(size_t index) const final;

    SafePointerVector<const IParticle> getParticles() const final;

    double getAbundanceOfParticle(size_t index) const;

    const IInterferenceFunction* getInterferenceFunction() const final
    {
        return mP_interference_function.get();
    }
    IInterferenceFunction* cloneInterferenceFunction() const final;
    void addInterferenceFunction(const IInterferenceFunction& interference_function);
    // TODO add -> set (there can be at most 1 interference function)

    double getTotalParticleSurfaceDensity() const final;
    void setTotalParticleSurfaceDensity(double particle_density) final
    {
        m_total_particle_density = particle_density;
    }

private:
    void addAndRegisterAbstractParticle(IAbstractParticle* child);

    void setAndRegisterInterferenceFunction(IInterferenceFunction* child);

    void print(std::ostream& ostr) const;

    SafePointerVector<IAbstractParticle> m_particles; //!< Vector of particle types
    std::unique_ptr<IInterferenceFunction> mP_interference_function;
    double m_total_particle_density;
};

#endif // PARTICLELAYOUT_H
