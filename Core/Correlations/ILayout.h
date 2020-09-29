// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Correlations/ILayout.h
//! @brief     Defines and implements interface class ILayout.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_CORRELATIONS_ILAYOUT_H
#define BORNAGAIN_CORE_CORRELATIONS_ILAYOUT_H

#include "Core/Scattering/ISample.h"
#include "Core/Tools/SafePointerVector.h"

class IAbstractParticle;
class IInterferenceFunction;

//! Pure virtual interface class to equip a sample layer with scattering properties.
//! Currently only inherited by ParticleLayout; in the future also by domain structure.
//!
//! @ingroup samples_internal

// NOTE: When domain structures are implemented, this interface would probably undergo
// major changes, because a domain layout would not contain particles
class ILayout : public ISample
{
public:
    ILayout();
    virtual ~ILayout();

    virtual ILayout* clone() const = 0;
    virtual void accept(INodeVisitor* visitor) const = 0;

    //! Returns information on all particles (type and abundance)
    //! and generates new particles if an IAbstractParticle denotes a collection
    virtual SafePointerVector<IParticle> particles() const = 0;

    //! Returns the interference function
    virtual const IInterferenceFunction* interferenceFunction() const = 0;

    /// Get total abundance of all particles
    virtual double getTotalAbundance() const = 0;

    //! Returns surface density of all particles
    virtual double totalParticleSurfaceDensity() const = 0;

    //! Sets surface density of all particles
    virtual void setTotalParticleSurfaceDensity(double particle_density) = 0;

    //! Returns the relative weight of this layout
    double weight() const { return m_weight; }

    //! Sets the relative weight of this layout
    void setWeight(double weight) { m_weight = weight; }

protected:
    double m_weight;
};

#endif // BORNAGAIN_CORE_CORRELATIONS_ILAYOUT_H
