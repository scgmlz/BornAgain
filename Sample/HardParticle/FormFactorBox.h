//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorBox.h
//! @brief     Defines class FormFactorBox.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORBOX_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORBOX_H

#include "Sample/HardParticle/IFormFactorPrism.h"

//! A rectangular prism (parallelepiped).
//! @ingroup hardParticle

class FormFactorBox : public IFormFactorPrism {
public:
    FormFactorBox(const std::vector<double> P);
    FormFactorBox(double length, double width, double height);

    FormFactorBox* clone() const final { return new FormFactorBox(m_length, m_width, m_height); }

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getLength() const { return m_length; }
    double getWidth() const { return m_width; }

    double volume() const final { return m_length * m_height * m_width; }
    double radialExtension() const final { return m_length / 2.0; }
    complex_t evaluate_for_q(cvector_t q) const final;

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const final;

    void onChange() final;
    double height() const final { return m_height; }

private:
    const double& m_length;
    const double& m_width;
    const double& m_height;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORBOX_H
