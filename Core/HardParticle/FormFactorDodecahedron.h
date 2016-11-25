// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorDodecahedron.h
//! @brief     Defines class FormFactorDodecahedron.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDODECAHEDRON_H
#define FORMFACTORDODECAHEDRON_H

#include "FormFactorPolyhedron.h"

//! A regular dodecahedron.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorDodecahedron : public FormFactorPolyhedron
{
public:
    //! @brief Constructs a regular dodecahedron
    //! @param edge length
    FormFactorDodecahedron(double edge);

    FormFactorDodecahedron* clone() const override final
    {
        return new FormFactorDodecahedron(m_edge);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getEdge() const { return m_edge; }

protected:
    void onChange() override final;

private:
    static const PolyhedralTopology topology;
    double m_edge;
};

#endif // FORMFACTORDODECAHEDRON_H
