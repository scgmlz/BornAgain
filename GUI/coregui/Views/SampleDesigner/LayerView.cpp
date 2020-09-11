// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/LayerView.cpp
//! @brief     Implements class LayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/LayerView.h"
#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Models/SessionItem.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/Views/SampleDesigner/MultiLayerView.h"
#include "GUI/coregui/Views/SampleDesigner/ParticleLayoutView.h"
#include "GUI/coregui/mainwindow/tooltipdatabase.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>

LayerView::LayerView(QGraphicsItem* parent) : ILayerView(parent)
{
    setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
    setName("Layer");
    setRectangle(DesignerHelper::getDefaultBoundingRect("Layer"));
    setAcceptDrops(false);
    addPort(QString(), NodeEditorPort::INPUT, NodeEditorPort::PARTICLE_LAYOUT);
}

void LayerView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget);

    painter->setPen(Qt::black);
    if (option->state & (QStyle::State_Selected | QStyle::State_HasFocus)) {
        painter->setPen(Qt::DashLine);
    }
    painter->setBrush(DesignerHelper::getLayerGradient(m_color, getRectangle()));
    painter->drawRect(getRectangle());
}

void LayerView::addView(IView* childView, int /* row */)
{
    ParticleLayoutView* layout = dynamic_cast<ParticleLayoutView*>(childView);
    ASSERT(layout);
    connectInputPort(layout, 0);
}
