// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCylinder.h
//! @brief     Defines class FormFactorCylinder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORCYLINDER_H
#define FORMFACTORCYLINDER_H

#include "IFormFactorBorn.h"

//! A circular cylinder.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorCylinder : public IFormFactorBorn
{
public:
    FormFactorCylinder(double radius, double height);

    FormFactorCylinder* clone() const override final
    {
        return new FormFactorCylinder(m_radius, m_height);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getHeight() const { return m_height; }
    double getRadius() const { return m_radius; }

    double getRadialExtension() const override final { return m_radius; }

    complex_t evaluate_for_q(const cvector_t q) const override final;

private:
    double m_radius;
    double m_height;
};

#endif // FORMFACTORCYLINDER_H
