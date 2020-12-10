//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorFullSpheroid.h
//! @brief     Defines class FormFactorFullSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORFULLSPHEROID_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORFULLSPHEROID_H

#include "Sample/Scattering/IBornFF.h"

//! A full spheroid (an ellipsoid with two equal axes, hence with circular cross section)
//! @ingroup hardParticle

class FormFactorFullSpheroid : public IBornFF {
public:
    FormFactorFullSpheroid(const std::vector<double> P);
    FormFactorFullSpheroid(double radius, double height);

    FormFactorFullSpheroid* clone() const final {
        return new FormFactorFullSpheroid(m_radius, m_height);
    }
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getRadius() const { return m_radius; }

    double radialExtension() const final { return m_radius; }

    complex_t evaluate_for_q(cvector_t q) const final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const final;

    void onChange() final;

private:
    const double& m_radius;
    const double& m_height;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORFULLSPHEROID_H
