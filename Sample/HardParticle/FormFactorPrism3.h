//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorPrism3.h
//! @brief     Defines class FormFactorPrism3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORPRISM3_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORPRISM3_H

#include "Sample/HardParticle/IFormFactorPrism.h"

//! A prism based on an equilateral triangle.
//! @ingroup hardParticle

class FormFactorPrism3 : public IFormFactorPrism {
public:
    FormFactorPrism3(const std::vector<double> P);
    FormFactorPrism3(double base_edge, double height);

    FormFactorPrism3* clone() const final { return new FormFactorPrism3(m_base_edge, m_height); }
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getBaseEdge() const { return m_base_edge; }

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const final;

    void onChange() final;
    double height() const final { return m_height; }

private:
    const double& m_base_edge;
    const double& m_height;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORPRISM3_H
