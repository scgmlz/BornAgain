//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorEllipsoidalCylinder.h
//! @brief     Defines class FormFactorEllipsoidalCylinder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORELLIPSOIDALCYLINDER_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORELLIPSOIDALCYLINDER_H

#include "Sample/Scattering/IBornFF.h"

//! A cylinder with elliptical base.
//! @ingroup hardParticle

class FormFactorEllipsoidalCylinder : public IBornFF {
public:
    FormFactorEllipsoidalCylinder(const std::vector<double> P);
    FormFactorEllipsoidalCylinder(double radius_x, double radius_y, double height);

    FormFactorEllipsoidalCylinder* clone() const final {
        return new FormFactorEllipsoidalCylinder(m_radius_x, m_radius_y, m_height);
    }
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getRadiusX() const { return m_radius_x; }
    double getRadiusY() const { return m_radius_y; }
    double getHeight() const { return m_height; }

    double radialExtension() const final;

    complex_t evaluate_for_q(cvector_t q) const final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const final;

    void onChange() final;

private:
    const double& m_radius_x;
    const double& m_radius_y;
    const double& m_height;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORELLIPSOIDALCYLINDER_H
