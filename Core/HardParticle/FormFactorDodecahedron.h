// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorDodecahedron.h
//! @brief     Defines class FormFactorDodecahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORDODECAHEDRON_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORDODECAHEDRON_H

#include "Core/HardParticle/IFormFactorPolyhedron.h"

//! A regular dodecahedron.
//! @ingroup hardParticle

class FormFactorDodecahedron : public IFormFactorPolyhedron
{
public:
    //! @brief Constructs a regular dodecahedron
    //! @param edge length
    FormFactorDodecahedron(const std::vector<double> P);
    FormFactorDodecahedron(double edge);

    FormFactorDodecahedron* clone() const override final
    {
        return new FormFactorDodecahedron(m_edge);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

    double getEdge() const { return m_edge; }

protected:
    void onChange() override final;

private:
    static const PolyhedralTopology topology;
    const double& m_edge;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORDODECAHEDRON_H
