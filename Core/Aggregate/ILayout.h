// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Aggregate/ILayout.h
//! @brief     Defines and implements interface class ILayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ILAYOUT_H
#define ILAYOUT_H

#include "ICompositeSample.h"
#include "SafePointerVector.h"

class IAbstractParticle;
class IInterferenceFunction;
class ILayout;

//! Pure virtual interface class to equip a sample layer with scattering properties.
//! Currently only inherited by ParticleLayout; in the future also by domain structure.
//! @ingroup samples_internal

// TODO: CONSIDER REFACTORING:
//   reference to particles could be removed in ILayout,
//   at the cost of a big refactoring of LayerStrategyBuilder.

class BA_CORE_API_ ILayout : public ICompositeSample
{
public:
    enum EInterferenceApproximation { DA, SSCA };

    ILayout() : me_approx(DA) {}
    virtual ~ILayout() {}

    virtual ILayout* clone() const = 0;

    //! calls the ISampleVisitor's visit method
    virtual void accept(ISampleVisitor* visitor) const = 0;

    //! Returns a clone with inverted magnetic fields
    virtual ILayout* cloneInvertB() const = 0;

    //! Returns number of particles
    virtual size_t getNumberOfParticles() const = 0;

    //! Returns information about particle with index
    virtual const IAbstractParticle* getParticle(size_t index) const = 0;

    //! Returns information on all particles (type and abundance)
    //! and generates new particles if an IAbstractParticle denotes a collection
    virtual SafePointerVector<const IParticle> getParticles() const = 0;

    /// Get abundance fraction of particle with index
    virtual double getAbundanceOfParticle(size_t index) const = 0;

    /// Get total abundance of all particles
    double getTotalAbundance() const; // implemented below

    //! Returns interference function
    virtual const IInterferenceFunction* getInterferenceFunction() const = 0;
    virtual IInterferenceFunction* cloneInterferenceFunction() const = 0;

    //! Returns surface density of all particles
    virtual double getTotalParticleSurfaceDensity() const = 0;

    //! Sets surface density of all particles
    virtual void setTotalParticleSurfaceDensity(double particle_density) = 0;

    //! Gets the used approximation for particles and interference functions
    EInterferenceApproximation getApproximation() const { return me_approx; }

    //! Sets the used approximation for particles and interference functions
    void setApproximation(EInterferenceApproximation approximation) { me_approx = approximation; }

private:
    ///< Approximation used for combining particles and interference functions
    EInterferenceApproximation me_approx;
};


inline double ILayout::getTotalAbundance() const
{
    double total_abundance = 0.0;
    for (size_t i = 0; i < getNumberOfParticles(); ++i)
        total_abundance += getAbundanceOfParticle(i);
    return total_abundance;
}

#endif // ILAYOUT_H
