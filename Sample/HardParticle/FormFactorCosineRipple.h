//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorCosineRipple.h
//! @brief     Defines classes FormFactorCosineRipple*.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORCOSINERIPPLE_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORCOSINERIPPLE_H

#include "Sample/HardParticle/IProfileRipple.h"

//! The form factor for a cosine ripple, with box profile in elongation direction.
//! @ingroup legacyGrating
class FormFactorCosineRippleBox : public ICosineRipple {
public:
    FormFactorCosineRippleBox(const std::vector<double> P);
    FormFactorCosineRippleBox(double length, double width, double height);
    FormFactorCosineRippleBox* clone() const final;
    void accept(INodeVisitor* visitor) const final;

private:
    complex_t factor_x(complex_t qx) const final;
};

//! The form factor for a cosine ripple, with Gaussian profile in elongation direction.
//! @ingroup legacyGrating
class FormFactorCosineRippleGauss : public ICosineRipple {
public:
    FormFactorCosineRippleGauss(const std::vector<double> P);
    FormFactorCosineRippleGauss(double length, double width, double height);
    FormFactorCosineRippleGauss* clone() const final;
    void accept(INodeVisitor* visitor) const final;

private:
    complex_t factor_x(complex_t qx) const final;
};

//! The form factor for a cosine ripple, with Lorentz form factor in elongation direction.
//! @ingroup legacyGrating
class FormFactorCosineRippleLorentz : public ICosineRipple {
public:
    FormFactorCosineRippleLorentz(const std::vector<double> P);
    FormFactorCosineRippleLorentz(double length, double width, double height);
    FormFactorCosineRippleLorentz* clone() const final;
    void accept(INodeVisitor* visitor) const final;

private:
    complex_t factor_x(complex_t qx) const final;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORCOSINERIPPLE_H
