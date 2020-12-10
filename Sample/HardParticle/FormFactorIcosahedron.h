//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/HardParticle/FormFactorIcosahedron.h
//! @brief     Defines class FormFactorIcosahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORICOSAHEDRON_H
#define BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORICOSAHEDRON_H

#include "Sample/HardParticle/IFormFactorPolyhedron.h"

//! A regular icosahedron.
//! @ingroup hardParticle

class FormFactorIcosahedron : public IFormFactorPolyhedron {
public:
    FormFactorIcosahedron(const std::vector<double> P);
    FormFactorIcosahedron(double edge);

    FormFactorIcosahedron* clone() const final { return new FormFactorIcosahedron(m_edge); }
    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    double getEdge() const { return m_edge; }

protected:
    void onChange() final;

private:
    static const PolyhedralTopology topology;
    const double& m_edge;
};

#endif // BORNAGAIN_SAMPLE_HARDPARTICLE_FORMFACTORICOSAHEDRON_H
