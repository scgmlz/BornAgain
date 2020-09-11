// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/InterferenceFunctionViews.cpp
//! @brief     Implements classes InterferenceFunctionViews
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/InterferenceFunctionViews.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"

InterferenceFunction1DLatticeView::InterferenceFunction1DLatticeView(QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName("Interference1DLattice");
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getInterferenceFunctionBoundingRect());
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunction2DLatticeView::InterferenceFunction2DLatticeView(QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName("Interference2DLattice");
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getInterferenceFunctionBoundingRect());
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunction2DParaCrystalView::InterferenceFunction2DParaCrystalView(QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName("Interference2DParaCrystal");
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getInterferenceFunctionBoundingRect());
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunctionFinite2DLatticeView::InterferenceFunctionFinite2DLatticeView(
    QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName("InterferenceFinite2DLattice");
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getInterferenceFunctionBoundingRect());
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunctionHardDiskView::InterferenceFunctionHardDiskView(QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName("InterferenceHardDisk");
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getInterferenceFunctionBoundingRect());
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}

InterferenceFunctionRadialParaCrystalView::InterferenceFunctionRadialParaCrystalView(
    QGraphicsItem* parent)
    : ConnectableView(parent)
{
    setName("InterferenceRadialParaCrystal");
    setColor(QColor(255, 236, 139));
    setRectangle(DesignerHelper::getInterferenceFunctionBoundingRect());
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::INTERFERENCE);
    m_roundpar = 3;
}
