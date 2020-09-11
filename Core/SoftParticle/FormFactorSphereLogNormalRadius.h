// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereLogNormalRadius.h
//! @brief     Defines and implements class FormFactorSphereLogNormalRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORSPHERELOGNORMALRADIUS_H
#define BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORSPHERELOGNORMALRADIUS_H

#include "Core/Scattering/IFormFactorBorn.h"
#include "Core/Tools/SafePointerVector.h"
#include <memory>

//! A sphere with log normal radius distribution.
//! @ingroup softParticle

class BA_CORE_API_ FormFactorSphereLogNormalRadius : public IFormFactorBorn
{
public:
    FormFactorSphereLogNormalRadius(const std::vector<double> P, size_t n_samples = 0);
    FormFactorSphereLogNormalRadius(double mean, double scale_param, size_t n_samples);

    FormFactorSphereLogNormalRadius* clone() const override final;

    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double radialExtension() const override final { return m_mean; }

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    void onChange() override final;

private:
    const double& m_mean;
    const double& m_scale_param;
    size_t m_n_samples;

    std::vector<double> m_radii;
    std::vector<double> m_probabilities;
};

#endif // BORNAGAIN_CORE_SOFTPARTICLE_FORMFACTORSPHERELOGNORMALRADIUS_H
