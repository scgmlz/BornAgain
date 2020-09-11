// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorIcosahedron.h
//! @brief     Defines class FormFactorIcosahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORICOSAHEDRON_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORICOSAHEDRON_H

#include "Core/HardParticle/FormFactorPolyhedron.h"

//! A regular icosahedron.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorIcosahedron : public FormFactorPolyhedron
{
public:
    FormFactorIcosahedron(const std::vector<double> P);
    FormFactorIcosahedron(double edge);

    FormFactorIcosahedron* clone() const override final
    {
        return new FormFactorIcosahedron(m_edge);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getEdge() const { return m_edge; }

protected:
    void onChange() override final;

private:
    static const PolyhedralTopology topology;
    const double& m_edge;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORICOSAHEDRON_H
