// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/TransformationView.cpp
//! @brief     Implements class TransformationView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/TransformationView.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"

TransformationView::TransformationView(QGraphicsItem* parent) : ConnectableView(parent)
{
    setName("Rotation");
    setColor(DesignerHelper::getDefaultTransformationColor());
    setRectangle(DesignerHelper::getTransformationBoundingRect());
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::TRANSFORMATION)
        ->setToolTip("Connect this port to the particle to define its rotation");
    m_roundpar = 3;
}
