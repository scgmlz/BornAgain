//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorSawtoothRipple.h
//! @brief     Defines classes FormFactorSawtoothRipple*.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORSAWTOOTHRIPPLE_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORSAWTOOTHRIPPLE_H

#include "Sample/HardParticle/IProfileRipple.h"

//! The form factor for a cosine ripple, with box profile in elongation direction.
//! @ingroup legacyGrating
class FormFactorSawtoothRippleBox : public ISawtoothRipple {
public:
    FormFactorSawtoothRippleBox(const std::vector<double> P);
    FormFactorSawtoothRippleBox(double length, double width, double height, double asymmetry);
    FormFactorSawtoothRippleBox* clone() const final;
    void accept(INodeVisitor* visitor) const final;

private:
    complex_t factor_x(complex_t qx) const final;
};

//! The form factor for a cosine ripple, with Gaussian profile in elongation direction.
//! @ingroup legacyGrating
class FormFactorSawtoothRippleGauss : public ISawtoothRipple {
public:
    FormFactorSawtoothRippleGauss(const std::vector<double> P);
    FormFactorSawtoothRippleGauss(double length, double width, double height, double asymmetry);
    FormFactorSawtoothRippleGauss* clone() const final;
    void accept(INodeVisitor* visitor) const final;

private:
    complex_t factor_x(complex_t qx) const final;
};

//! The form factor for a cosine ripple, with Lorentz form factor in elongation direction.
//! @ingroup legacyGrating
class FormFactorSawtoothRippleLorentz : public ISawtoothRipple {
public:
    FormFactorSawtoothRippleLorentz(const std::vector<double> P);
    FormFactorSawtoothRippleLorentz(double length, double width, double height, double asymmetry);
    FormFactorSawtoothRippleLorentz* clone() const final;
    void accept(INodeVisitor* visitor) const final;

private:
    complex_t factor_x(complex_t qx) const final;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORSAWTOOTHRIPPLE_H
