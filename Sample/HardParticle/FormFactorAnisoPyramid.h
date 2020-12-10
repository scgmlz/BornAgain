//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorAnisoPyramid.h
//! @brief     Defines class FormFactorAnisoPyramid
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORANISOPYRAMID_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORANISOPYRAMID_H

#include "Sample/HardParticle/IFormFactorPolyhedron.h"

//! A frustum (truncated pyramid) with rectangular base.
//! @ingroup hardParticle

class FormFactorAnisoPyramid : public IFormFactorPolyhedron {
public:
    FormFactorAnisoPyramid(const std::vector<double> P);
    FormFactorAnisoPyramid(double length, double width, double height, double alpha);

    FormFactorAnisoPyramid* clone() const final {
        return new FormFactorAnisoPyramid(m_length, m_width, m_height, m_alpha);
    }
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getLength() const { return m_length; }
    double getWidth() const { return m_width; }
    double getHeight() const { return m_height; }
    double getAlpha() const { return m_alpha; }

protected:
    IFormFactor* sliceFormFactor(ZLimits limits, const IRotation& rot,
                                 kvector_t translation) const final;

    void onChange() final;

private:
    static const PolyhedralTopology topology;

    const double& m_length;
    const double& m_width;
    const double& m_height;
    const double& m_alpha;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORANISOPYRAMID_H
