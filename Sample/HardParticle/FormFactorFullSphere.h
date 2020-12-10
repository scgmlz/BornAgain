//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorFullSphere.h
//! @brief     Defines class FormFactorFullSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORFULLSPHERE_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORFULLSPHERE_H

#include "Sample/Scattering/IBornFF.h"

//! A full sphere.
//! @ingroup hardParticle

class FormFactorFullSphere : public IBornFF {
public:
    FormFactorFullSphere(const std::vector<double> P, bool position_at_center = false);
    FormFactorFullSphere(double radius, bool position_at_center = false);

    FormFactorFullSphere* clone() const final {
        return new FormFactorFullSphere(m_radius, m_position_at_center);
    }
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getRadius() const { return m_radius; }

    double radialExtension() const final { return m_radius; }

    double bottomZ(const IRotation& rotation) const final;

    double topZ(const IRotation& rotation) const final;

    complex_t evaluate_for_q(cvector_t q) const final;

protected:
    bool canSliceAnalytically(const IRotation&) const final { return true; }

    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const final;

    void onChange() final;

private:
    const double& m_radius;
    bool m_position_at_center;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORFULLSPHERE_H
