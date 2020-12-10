//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/SoftParticle/FormFactorGauss.h
//! @brief     Defines class FormFactorGaussSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_SOFTPARTICLE_FORMFACTORGAUSS_H
#define BORNAGAIN_SAMPLE_SOFTPARTICLE_FORMFACTORGAUSS_H

#include "Sample/Scattering/IBornFF.h"

//! The form factor of a Gaussian sphere.
//! @ingroup softParticle

class FormFactorGaussSphere : public IBornFF {
public:
    FormFactorGaussSphere(const std::vector<double> P);
    FormFactorGaussSphere(double mean_radius);

    FormFactorGaussSphere* clone() const final { return new FormFactorGaussSphere(m_mean_radius); }
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getMeanRadius() const { return m_mean_radius; }

    double radialExtension() const final { return m_mean_radius; }

    complex_t evaluate_for_q(cvector_t q) const final;

protected:
    void onChange() final{};

private:
    const double& m_mean_radius;
    void initialize();
};

#endif // BORNAGAIN_SAMPLE_SOFTPARTICLE_FORMFACTORGAUSS_H
