// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereLogNormalRadius.h
//! @brief     Defines and implements class FormFactorSphereLogNormalRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORSPHERELOGNORMALRADIUS_H
#define FORMFACTORSPHERELOGNORMALRADIUS_H

#include "Distributions.h"
#include "FormFactorFullSphere.h"
#include "SafePointerVector.h"
#include <memory>

//! A sphere with log normal radius distribution.
//! @ingroup softParticle

class BA_CORE_API_ FormFactorSphereLogNormalRadius : public IFormFactorBorn
{
public:
    FormFactorSphereLogNormalRadius(double mean, double scale_param, size_t n_samples);

    FormFactorSphereLogNormalRadius* clone() const override final
    {
        return new FormFactorSphereLogNormalRadius(m_mean, m_scale_param, m_n_samples);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getRadialExtension() const override final { return m_mean; }

    complex_t evaluate_for_q(const cvector_t q) const override final;

private:
    double m_mean;
    double m_scale_param;
    size_t m_n_samples;

    std::unique_ptr<DistributionLogNormal> mP_distribution;

    SafePointerVector<IFormFactorBorn> m_form_factors;
    std::vector<double> m_probabilities;
};

#endif // FORMFACTORSPHERELOGNORMALRADIUS_H
