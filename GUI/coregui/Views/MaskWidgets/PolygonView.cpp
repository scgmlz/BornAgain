// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/PolygonView.cpp
//! @brief     Implements PolygonView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/PolygonView.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Views/MaskWidgets/PolygonPointView.h"
#include <QCursor>
#include <QPainter>

namespace
{
const double bbox_margins = 5; // additional margins around points to form bounding box
}

PolygonView::PolygonView() : m_block_on_point_update(false), m_close_polygon_request(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void PolygonView::addView(IShape2DView* childView, int row)
{
    Q_UNUSED(row);

    if (childItems().contains(childView))
        return;

    PolygonPointView* pointView = dynamic_cast<PolygonPointView*>(childView);
    ASSERT(pointView);
    pointView->setParentItem(this);

    // polygon consisting from more than 2 points can be closed via hover event by clicking
    // on first polygon point
    if (!isClosedPolygon() && childItems().size() > 2)
        childItems()[0]->setAcceptHoverEvents(true);

    pointView->setVisible(true);
    update_polygon();

    connect(pointView, SIGNAL(propertyChanged()), this, SLOT(update_view()));
    connect(pointView, SIGNAL(closePolygonRequest(bool)), this, SLOT(onClosePolygonRequest(bool)));
}

//! returns last added poligon point in scene coordinates
QPointF PolygonView::lastAddedPoint() const
{
    return childItems().size() ? childItems().back()->scenePos() : QPointF();
}

//! Returns true if there was a request to close polygon (emitted by its start point),
//! and then closes a polygon. Returns true if polygon was closed.
bool PolygonView::closePolygonIfNecessary()
{
    if (m_close_polygon_request) {
        for (QGraphicsItem* childItem : childItems()) {
            childItem->setFlag(QGraphicsItem::ItemIsMovable);
            childItem->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
            childItem->setAcceptHoverEvents(false);
            childItem->setCursor(Qt::SizeAllCursor);
        }
        m_item->setItemValue(PolygonItem::P_ISCLOSED, true);
        update();
    }
    return isClosedPolygon();
}

void PolygonView::onClosePolygonRequest(bool value)
{
    m_close_polygon_request = value;
}

bool PolygonView::isClosedPolygon()
{
    return m_item->getItemValue(PolygonItem::P_ISCLOSED).toBool();
}

void PolygonView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    ASSERT(m_item);
    painter->setRenderHints(QPainter::Antialiasing);

    bool mask_value = m_item->getItemValue(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));

    // painter->drawRect(m_bounding_rect);

    painter->drawPolyline(m_polygon.toPolygon());

    if (isClosedPolygon())
        painter->drawPolygon(m_polygon.toPolygon());
}

QVariant PolygonView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        setChildrenVisible(this->isSelected());

    return value;
}

void PolygonView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    IShape2DView::mouseMoveEvent(event);
    update_points();
}

void PolygonView::update_view()
{
    update_polygon();
    update();
}

//! Runs through all PolygonPointItem and calculate bounding rectangle.
//! Determines position of the rectangle in scene.
//! Calculates position of PolygonPointView in local polygon coordinates
void PolygonView::update_polygon()
{
    if (m_block_on_point_update)
        return;

    m_block_on_point_update = true;

    if (m_item->numberOfChildren()) {

        m_polygon.clear();

        for (SessionItem* item : m_item->getChildrenOfType("PolygonPoint")) {
            qreal px = toSceneX(item->getItemValue(PolygonPointItem::P_POSX).toReal());
            qreal py = toSceneY(item->getItemValue(PolygonPointItem::P_POSY).toReal());
            m_polygon << QPointF(px, py);
        }
        QRectF scene_rect = m_polygon.boundingRect().marginsAdded(
            QMarginsF(bbox_margins, bbox_margins, bbox_margins, bbox_margins));

        m_bounding_rect = QRectF(0.0, 0.0, scene_rect.width(), scene_rect.height());

        setPos(scene_rect.x(), scene_rect.y());
        update(); // to propagate changes to scene

        m_polygon = mapFromScene(m_polygon);

        //        for (int i = 0; i < childItems().size(); ++i) {
        //            QGraphicsItem* childView = childItems()[i];
        //            childView->setPos(m_polygon[i]);
        //        }
        int index(0);
        for (auto childView : childItems())
            childView->setPos(m_polygon[index++]);

        setPos(scene_rect.x(), scene_rect.y());
    }
    m_block_on_point_update = false;
}

//! When polygon moves as a whole thing across the scene, given method updates coordinates
//! of PolygonPointItem's
void PolygonView::update_points()
{
    if (m_block_on_point_update)
        return;

    for (QGraphicsItem* childItem : childItems()) {
        PolygonPointView* view = dynamic_cast<PolygonPointView*>(childItem);
        QPointF pos = view->scenePos();
        disconnect(view, SIGNAL(propertyChanged()), this, SLOT(update_view()));
        view->updateParameterizedItem(pos);
        connect(view, SIGNAL(propertyChanged()), this, SLOT(update_view()));
    }
}

void PolygonView::setChildrenVisible(bool value)
{
    for (QGraphicsItem* childItem : childItems())
        childItem->setVisible(value);
}
