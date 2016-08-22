// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SoftParticle/FormFactorSphereGaussianRadius.h
//! @brief     Defines and implements class FormFactorSphereGaussianRadius.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORSPHEREGAUSSIANRADIUS_H
#define FORMFACTORSPHEREGAUSSIANRADIUS_H

#include "FormFactorFullSphere.h"

//! A sphere with gaussian radius distribution.
//! @ingroup softParticle

class BA_CORE_API_ FormFactorSphereGaussianRadius : public IFormFactorBorn
{
public:
    FormFactorSphereGaussianRadius(double mean, double sigma);
    virtual ~FormFactorSphereGaussianRadius();

    FormFactorSphereGaussianRadius* clone() const final {
        return new FormFactorSphereGaussianRadius(m_mean, m_sigma); }

    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    double getRadialExtension() const final { return m_mean; }

    complex_t evaluate_for_q(const cvector_t q) const final;

private:
    double calculateMeanR3() const;

    double m_mean; //!< This is the mean radius
    double m_sigma;
    double m_mean_r3; //!< This is the radius that gives the mean volume
    FormFactorFullSphere* p_ff_sphere;
};

#endif // FORMFACTORSPHEREGAUSSIANRADIUS_H
