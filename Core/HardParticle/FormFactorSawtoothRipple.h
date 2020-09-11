// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorSawtoothRipple.h
//! @brief     Defines classes FormFactorSawtoothRipple*.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORSAWTOOTHRIPPLE_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORSAWTOOTHRIPPLE_H

#include "Core/HardParticle/IProfileRipple.h"

//! The form factor for a cosine ripple, with box profile in elongation direction.
//! @ingroup legacyGrating
class BA_CORE_API_ FormFactorSawtoothRippleBox : public ISawtoothRipple
{
public:
    FormFactorSawtoothRippleBox(const std::vector<double> P);
    FormFactorSawtoothRippleBox(double length, double width, double height, double asymmetry);
    FormFactorSawtoothRippleBox* clone() const override final;
    void accept(INodeVisitor* visitor) const override final;

private:
    complex_t factor_x(complex_t qx) const override final;
};

//! The form factor for a cosine ripple, with Gaussian profile in elongation direction.
//! @ingroup legacyGrating
class BA_CORE_API_ FormFactorSawtoothRippleGauss : public ISawtoothRipple
{
public:
    FormFactorSawtoothRippleGauss(const std::vector<double> P);
    FormFactorSawtoothRippleGauss(double length, double width, double height, double asymmetry);
    FormFactorSawtoothRippleGauss* clone() const override final;
    void accept(INodeVisitor* visitor) const override final;

private:
    complex_t factor_x(complex_t qx) const override final;
};

//! The form factor for a cosine ripple, with Lorentz form factor in elongation direction.
//! @ingroup legacyGrating
class BA_CORE_API_ FormFactorSawtoothRippleLorentz : public ISawtoothRipple
{
public:
    FormFactorSawtoothRippleLorentz(const std::vector<double> P);
    FormFactorSawtoothRippleLorentz(double length, double width, double height, double asymmetry);
    FormFactorSawtoothRippleLorentz* clone() const override final;
    void accept(INodeVisitor* visitor) const override final;

private:
    complex_t factor_x(complex_t qx) const override final;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORSAWTOOTHRIPPLE_H
