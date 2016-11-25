// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorPrism3.h
//! @brief     Defines class FormFactorPrism3.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORPRISM3_H
#define FORMFACTORPRISM3_H
#include "FormFactorPolyhedron.h"

//! A prism based on an equilateral triangle.
//! @ingroup hardParticle

class BA_CORE_API_ FormFactorPrism3 : public FormFactorPolygonalPrism
{
public:
    FormFactorPrism3(const double base_edge, const double height);

    FormFactorPrism3* clone() const override final
    {
        return new FormFactorPrism3(m_base_edge, m_height);
    }
    void accept(ISampleVisitor* visitor) const override final { visitor->visit(this); }

    double getBaseEdge() const { return m_base_edge; }

protected:
    void onChange() override final;

private:
    double m_base_edge;
};

#endif // FORMFACTORPRISM3_H
