// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPrism6.h
//! @brief     Defines class FormFactorPrism6.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPRISM6_H
#define FORMFACTORPRISM6_H
#include "FormFactorPolyhedron.h"

//! A prism based on a regular hexagonal.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorPrism6 : public FormFactorPolygonalPrism
{
public:
    FormFactorPrism6(const double base_edge, const double height);

    FormFactorPrism6* clone() const override final
    {
        return new FormFactorPrism6(m_base_edge, m_height);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getBaseEdge() const { return m_base_edge; }

protected:
    void onChange() override final;

private:
    double m_base_edge;
};

#endif // FORMFACTORPRISM6_H
