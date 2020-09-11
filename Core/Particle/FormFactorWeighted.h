// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/FormFactorWeighted.h
//! @brief     Defines class FormFactorWeighted.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_PARTICLE_FORMFACTORWEIGHTED_H
#define BORNAGAIN_CORE_PARTICLE_FORMFACTORWEIGHTED_H

#include "Core/Scattering/IFormFactor.h"

//! Coherent sum of different scalar IFormFactor's with different weights.
//!
//! Used by ParticleComposition.
//! If same particles are at different positions, then consider
//! FormFactorDecoratorMultiPositionFactor (restore from commit 0500a26de76).

//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorWeighted : public IFormFactor
{
public:
    FormFactorWeighted();
    ~FormFactorWeighted() override final;

    FormFactorWeighted* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double radialExtension() const override final;

    double bottomZ(const IRotation& rotation) const override final;

    double topZ(const IRotation& rotation) const override final;

    void addFormFactor(const IFormFactor& form_factor, double weight = 1.0);

    void setAmbientMaterial(Material material) override final;

    complex_t evaluate(const WavevectorInfo& wavevectors) const override final;

#ifndef SWIG
    //! Calculates and returns a polarized form factor calculation in DWBA
    Eigen::Matrix2cd evaluatePol(const WavevectorInfo& wavevectors) const override final;
#endif

protected:
    std::vector<IFormFactor*> m_form_factors;
    std::vector<double> m_weights;
};

#endif // BORNAGAIN_CORE_PARTICLE_FORMFACTORWEIGHTED_H
