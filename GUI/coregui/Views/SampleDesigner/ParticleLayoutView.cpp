// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleLayoutView.cpp
//! @brief     Implements class ParticleLayoutView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ParticleLayoutView.h"
#include "DesignerHelper.h"
#include "GUIHelpers.h"
#include "ParticleView.h"
#include "SessionItem.h"

ParticleLayoutView::ParticleLayoutView(QGraphicsItem *parent)
    : ConnectableView(parent)
{
    setName(Constants::ParticleLayoutType);
    setColor(QColor(135, 206, 50));
    setRectangle( DesignerHelper::getDefaultBoundingRect(Constants::ParticleLayoutType));
    addPort("out", NodeEditorPort::OUTPUT, NodeEditorPort::PARTICLE_LAYOUT)
        ->setToolTip(QStringLiteral("Connect this port with the layer "
                                    "to populate it with particles"));
    addPort("particle", NodeEditorPort::INPUT, NodeEditorPort::FORM_FACTOR)
        ->setToolTip(QStringLiteral("Connect one or several particles to this port"));
    addPort("interference", NodeEditorPort::INPUT, NodeEditorPort::INTERFERENCE)
        ->setToolTip(QStringLiteral("Connect interference to this port "
                                    "to have coherent scattering"));
    m_roundpar = 3;
}

void ParticleLayoutView::addView(IView *childView, int /* row */)
{
    if(childView->type() == DesignerHelper::PARTICLE) {
        connectInputPort(dynamic_cast<ConnectableView *>(childView), 0);
    }
    else if(childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_RADIAL_PARA
         || childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_2D_PARA
         || childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_1D_LATTICE
         || childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_2D_LATTICE
         || childView->type() == DesignerHelper::INTERFERENCE_FUNCTION_FINITE_2D_LATTICE) {
        connectInputPort(dynamic_cast<ConnectableView *>(childView), 1);
    }
    else {
        throw GUIHelpers::Error("ParticleLayoutView::addView() -> Error. Unknown view");
    }
}
