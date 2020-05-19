// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorRipple1.h
//! @brief     Defines classes FormFactorRipple1*.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORRIPPLE1_H
#define FORMFACTORRIPPLE1_H

#include "ProfileRipple1.h"

//! The form factor for a cosine ripple, with box profile in elongation direction.
//! @ingroup legacyGrating
class BA_CORE_API_ FormFactorRipple1Box : public ProfileRipple1
{
public:
    FormFactorRipple1Box(double length, double width, double height);
    FormFactorRipple1Box* clone() const override final;
    void accept(INodeVisitor* visitor) const override final;
private:
    complex_t factor_x(complex_t qx) const override final;
};

//! The form factor for a cosine ripple, with Gaussian profile in elongation direction.
//! @ingroup legacyGrating
class BA_CORE_API_ FormFactorRipple1Gauss : public ProfileRipple1
{
public:
    FormFactorRipple1Gauss(double length, double width, double height);
    FormFactorRipple1Gauss* clone() const override final;
    void accept(INodeVisitor* visitor) const override final;
private:
    complex_t factor_x(complex_t qx) const override final;
};

//! The form factor for a cosine ripple, with Lorentz form factor in elongation direction.
//! @ingroup legacyGrating
class BA_CORE_API_ FormFactorRipple1Lorentz : public ProfileRipple1
{
public:
    FormFactorRipple1Lorentz(double length, double width, double height);
    FormFactorRipple1Lorentz* clone() const override final;
    void accept(INodeVisitor* visitor) const override final;
private:
    complex_t factor_x(complex_t qx) const override final;
};

#endif // FORMFACTORRIPPLE1_H
