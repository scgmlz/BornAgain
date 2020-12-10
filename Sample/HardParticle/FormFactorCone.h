//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorCone.h
//! @brief     Defines class FormFactorCone
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORCONE_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORCONE_H

#include "Sample/Scattering/IBornFF.h"

//! A conical frustum (cone truncated parallel to the base) with circular base.
//! @ingroup hardParticle

class FormFactorCone : public IBornFF {
public:
    FormFactorCone(const std::vector<double> P);
    FormFactorCone(double radius, double height, double alpha);

    FormFactorCone* clone() const final { return new FormFactorCone(m_radius, m_height, m_alpha); }
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getAlpha() const { return m_alpha; }
    double getRadius() const { return m_radius; }

    double radialExtension() const final { return m_radius; }

    complex_t evaluate_for_q(cvector_t q) const final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const final;

    void onChange() final;

private:
    complex_t Integrand(double Z) const;

    const double& m_radius;
    const double& m_height;
    const double& m_alpha;
    double m_cot_alpha;
    mutable cvector_t m_q;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORCONE_H
