// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorTetrahedron.h
//! @brief     Defines class FormFactorTetrahedron
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORTETRAHEDRON_H
#define FORMFACTORTETRAHEDRON_H

#include "FormFactorPolyhedron.h"

//! A frustum with equilateral trigonal base.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorTetrahedron : public FormFactorPolyhedron
{
public:
    FormFactorTetrahedron(double base_edge, double height, double alpha);

    FormFactorTetrahedron* clone() const override final
    {
        return new FormFactorTetrahedron(m_base_edge, m_height, m_alpha);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getBaseEdge() const { return m_base_edge; }
    double getHeight() const { return m_height; }
    double getAlpha() const { return m_alpha; }

protected:
    void onChange() override final;

private:
    static const PolyhedralTopology topology;
    double m_base_edge;
    double m_height;
    double m_alpha;
};

#endif // FORMFACTORTETRAHEDRON_H
