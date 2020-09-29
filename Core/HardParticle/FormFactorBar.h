// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorBar.h
//! @brief     Defines classes FormFactorBar*.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORBAR_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORBAR_H

#include "Core/HardParticle/IProfileRipple.h"

//! The form factor of an elongated bar, with Gaussian profile in elongation direction.
//! @ingroup legacyGrating
class FormFactorBarGauss : public IProfileRectangularRipple
{
public:
    FormFactorBarGauss(const std::vector<double> P);
    FormFactorBarGauss(double length, double width, double height);
    FormFactorBarGauss* clone() const final;
    void accept(INodeVisitor* visitor) const final;

private:
    complex_t factor_x(complex_t qx) const final;
};

//! The form factor of an elongated, with Lorentz form factor in elongation direction.
//! @ingroup legacyGrating
class FormFactorBarLorentz : public IProfileRectangularRipple
{
public:
    FormFactorBarLorentz(const std::vector<double> P);
    FormFactorBarLorentz(double length, double width, double height);
    FormFactorBarLorentz* clone() const final;
    void accept(INodeVisitor* visitor) const final;

private:
    complex_t factor_x(complex_t qx) const final;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORBAR_H
