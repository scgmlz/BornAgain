//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorTruncatedSpheroid.h
//! @brief     Defines class FormFactorTruncatedSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORTRUNCATEDSPHEROID_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORTRUNCATEDSPHEROID_H

#include "Sample/Scattering/IBornFF.h"

//! A truncated spheroid.
//! An ellipsoid with two equal axis, truncated by a plane perpendicular to the third axis.
//! @ingroup hardParticle

class FormFactorTruncatedSpheroid : public IBornFF {
public:
    FormFactorTruncatedSpheroid(const std::vector<double> P);
    FormFactorTruncatedSpheroid(double radius, double height, double height_flattening, double dh);

    FormFactorTruncatedSpheroid* clone() const final {
        return new FormFactorTruncatedSpheroid(m_radius, m_height, m_height_flattening, m_dh);
    }
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getRadius() const { return m_radius; }
    double getHeight() const { return m_height; }
    double getHeightFlattening() const { return m_height_flattening; }
    double getRemovedTop() const { return m_dh; }

    double radialExtension() const final { return m_radius; }

    complex_t evaluate_for_q(cvector_t q) const final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const final;

    void onChange() final;

private:
    bool check_initialization() const;
    complex_t Integrand(double Z) const;

    const double& m_radius;
    const double& m_height;
    const double& m_height_flattening;
    const double& m_dh;
    mutable cvector_t m_q;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORTRUNCATEDSPHEROID_H
