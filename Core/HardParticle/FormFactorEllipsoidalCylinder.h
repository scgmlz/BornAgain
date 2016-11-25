// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorEllipsoidalCylinder.h
//! @brief     Defines class FormFactorEllipsoidalCylinder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORELLIPSOIDALCYLINDER_H
#define FORMFACTORELLIPSOIDALCYLINDER_H

#include "IFormFactorBorn.h"

//! A cylinder with elliptical base.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorEllipsoidalCylinder : public IFormFactorBorn
{
public:
    FormFactorEllipsoidalCylinder(double radius_x, double radius_y, double height);

    FormFactorEllipsoidalCylinder* clone() const override final
    {
        return new FormFactorEllipsoidalCylinder(m_radius_x, m_radius_y, m_height);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getRadiusX() const { return m_radius_x; }
    double getRadiusY() const { return m_radius_y; }
    double getHeight() const { return m_height; }

    double getRadialExtension() const override final;

    complex_t evaluate_for_q(const cvector_t q) const override final;

private:
    double m_radius_x;
    double m_radius_y;
    double m_height;
};

#endif // FORMFACTORELLIPSOIDALCYLINDER_H
