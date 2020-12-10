//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorLongBoxGauss.h
//! @brief     Defines class FormFactorLongBoxGauss.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORLONGBOXGAUSS_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORLONGBOXGAUSS_H

#include "Sample/Scattering/IBornFF.h"

//! The form factor for a long rectangular box.
//! @ingroup legacyGrating

class FormFactorLongBoxGauss : public IBornFF {
public:
    FormFactorLongBoxGauss(const std::vector<double> P);
    FormFactorLongBoxGauss(double length, double width, double height);

    FormFactorLongBoxGauss* clone() const final {
        return new FormFactorLongBoxGauss(m_length, m_width, m_height);
    }
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }
    double radialExtension() const final { return m_length / 2.0; }

    complex_t evaluate_for_q(cvector_t q) const final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const final;

    void onChange() final;

private:
    const double& m_length;
    const double& m_width;
    const double& m_height;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORLONGBOXGAUSS_H
