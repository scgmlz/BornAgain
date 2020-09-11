// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/RealSpaceWidgets/RealSpacePositionBuilder.h
//! @brief     Defines class RealSpacePositionBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEPOSITIONBUILDER_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEPOSITIONBUILDER_H

#include "Core/Parametrization/INodeVisitor.h"
#include <memory>
#include <vector>

class IPositionBuilder;

class RealSpacePositionBuilder : public INodeVisitor
{
public:
    RealSpacePositionBuilder();
    ~RealSpacePositionBuilder() override;

    using INodeVisitor::visit;
    void visit(const InterferenceFunction1DLattice* p_iff) override;
    void visit(const InterferenceFunction2DLattice* p_iff) override;
    void visit(const InterferenceFunction2DParaCrystal* p_iff) override;
    void visit(const InterferenceFunctionFinite2DLattice* p_iff) override;
    void visit(const InterferenceFunctionRadialParaCrystal* p_iff) override;
    void visit(const InterferenceFunctionNone* p_iff) override;

    std::vector<std::vector<double>> generatePositions(double layer_size,
                                                       double density = 0.0) const;

private:
    std::unique_ptr<IPositionBuilder> mP_pos_builder;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_REALSPACEWIDGETS_REALSPACEPOSITIONBUILDER_H
