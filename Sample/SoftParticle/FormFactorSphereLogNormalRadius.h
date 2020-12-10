//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/SoftParticle/FormFactorSphereLogNormalRadius.h
//! @brief     Defines and implements class FormFactorSphereLogNormalRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_SOFTPARTICLE_FORMFACTORSPHERELOGNORMALRADIUS_H
#define BORNAGAIN_SAMPLE_SOFTPARTICLE_FORMFACTORSPHERELOGNORMALRADIUS_H

#include "Base/Types/SafePointerVector.h"
#include "Sample/Scattering/IBornFF.h"
#include <memory>

//! A sphere with log normal radius distribution.
//! @ingroup softParticle

class FormFactorSphereLogNormalRadius : public IBornFF {
public:
    FormFactorSphereLogNormalRadius(const std::vector<double> P, size_t n_samples = 0);
    FormFactorSphereLogNormalRadius(double mean, double scale_param, size_t n_samples);

    FormFactorSphereLogNormalRadius* clone() const final;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double radialExtension() const final { return m_mean; }

    complex_t evaluate_for_q(cvector_t q) const final;

protected:
    void onChange() final;

private:
    const double& m_mean;
    const double& m_scale_param;
    size_t m_n_samples;

    std::vector<double> m_radii;
    std::vector<double> m_probabilities;
};

#endif // BORNAGAIN_SAMPLE_SOFTPARTICLE_FORMFACTORSPHERELOGNORMALRADIUS_H
