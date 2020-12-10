//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/SoftParticle/FormFactorSphereGaussianRadius.h
//! @brief     Defines and implements class FormFactorSphereGaussianRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_SOFTPARTICLE_FORMFACTORSPHEREGAUSSIANRADIUS_H
#define BORNAGAIN_SAMPLE_SOFTPARTICLE_FORMFACTORSPHEREGAUSSIANRADIUS_H

#include "Sample/Scattering/IBornFF.h"
#include <memory>

//! A sphere with gaussian radius distribution.
//! @ingroup softParticle

class FormFactorSphereGaussianRadius : public IBornFF {
public:
    FormFactorSphereGaussianRadius(const std::vector<double> P);
    FormFactorSphereGaussianRadius(double mean, double sigma);

    FormFactorSphereGaussianRadius* clone() const final {
        return new FormFactorSphereGaussianRadius(m_mean, m_sigma);
    }

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double radialExtension() const final { return m_mean; }

    complex_t evaluate_for_q(cvector_t q) const final;

protected:
    void onChange() final;

private:
    double calculateMeanR3() const;

    const double& m_mean; //!< This is the mean radius
    const double& m_sigma;
    double m_mean_r3; //!< This is the radius that gives the mean volume
};

#endif // BORNAGAIN_SAMPLE_SOFTPARTICLE_FORMFACTORSPHEREGAUSSIANRADIUS_H
