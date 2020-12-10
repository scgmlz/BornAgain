//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorHemiEllipsoid.h
//! @brief     Defines class FormFactorHemiEllipsoid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORHEMIELLIPSOID_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORHEMIELLIPSOID_H

#include "Sample/Scattering/IBornFF.h"

//! An hemi ellipsoid,
//!   obtained by truncating a full ellipsoid in the middle plane spanned by two principal axes.
//! @ingroup hardParticle

class FormFactorHemiEllipsoid : public IBornFF {
public:
    FormFactorHemiEllipsoid(const std::vector<double> P);
    FormFactorHemiEllipsoid(double radius_x, double radius_y, double height);
    virtual ~FormFactorHemiEllipsoid() {}

    FormFactorHemiEllipsoid* clone() const final {
        return new FormFactorHemiEllipsoid(m_radius_x, m_radius_y, m_height);
    }
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getRadiusX() const { return m_radius_x; }
    double getRadiusY() const { return m_radius_y; }

    double radialExtension() const final;

    complex_t evaluate_for_q(cvector_t q) const final;

protected:
    void onChange() final;

private:
    complex_t Integrand(double Z) const;

    const double& m_radius_x;
    const double& m_radius_y;
    const double& m_height;
    mutable cvector_t m_q;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORHEMIELLIPSOID_H
