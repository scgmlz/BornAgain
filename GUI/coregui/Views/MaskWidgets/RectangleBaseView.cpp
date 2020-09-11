// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/RectangleBaseView.cpp
//! @brief     Implements RectangleBaseView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/RectangleBaseView.h"
#include "Core/Basics/Assert.h"

namespace
{
const double bbox_margins = 5; // additional margins around rectangle to form bounding box
}

RectangleBaseView::RectangleBaseView() : m_activeHandleElement(0)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    create_size_handle_elements();
}

//! triggered by SizeHandleElement
void RectangleBaseView::onSizeHandleElementRequest(bool going_to_resize)
{
    if (going_to_resize) {
        setFlag(QGraphicsItem::ItemIsMovable, false);
        m_activeHandleElement = qobject_cast<SizeHandleElement*>(sender());
        ASSERT(m_activeHandleElement);
        SizeHandleElement::EHandleLocation oposite_corner =
            m_activeHandleElement->getOppositeHandleLocation();
        m_resize_opposite_origin = m_resize_handles[oposite_corner]->scenePos();
    } else {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        m_activeHandleElement = 0;
    }
}

//! Track if item selected/deselected and show/hide size handles
QVariant RectangleBaseView::itemChange(QGraphicsItem::GraphicsItemChange change,
                                       const QVariant& value)
{
    if (change == QGraphicsItem::ItemSelectedChange) {
        for (auto it = m_resize_handles.begin(); it != m_resize_handles.end(); ++it) {
            it.value()->setVisible(!this->isSelected());
        }
    }
    return value;
}

void RectangleBaseView::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    onSizeHandleElementRequest(false);
    IShape2DView::mouseReleaseEvent(event);
}

void RectangleBaseView::update_view()
{
    prepareGeometryChange();
    update_bounding_rect();
    update_position();
}

//! updates view's bounding rectangle using item properties

void RectangleBaseView::update_bounding_rect()
{
    if (m_item) {
        m_mask_rect = mask_rectangle();
        m_bounding_rect = m_mask_rect.marginsAdded(
            QMarginsF(bbox_margins, bbox_margins, bbox_margins, bbox_margins));
    }
    for (QMap<SizeHandleElement::EHandleLocation, SizeHandleElement*>::iterator it =
             m_resize_handles.begin();
         it != m_resize_handles.end(); ++it) {
        it.value()->updateHandleElementPosition(m_mask_rect);
    }
}

//! returns width of the rectangle

qreal RectangleBaseView::width() const
{
    return right() - left();
}

qreal RectangleBaseView::height() const
{
    return bottom() - top();
}

void RectangleBaseView::create_size_handle_elements()
{
    QList<SizeHandleElement::EHandleLocation> points;
    points << SizeHandleElement::TOPLEFT << SizeHandleElement::TOPMIDDLE
           << SizeHandleElement::TOPRIGHT << SizeHandleElement::MIDDLERIGHT
           << SizeHandleElement::BOTTOMRIGHT << SizeHandleElement::BOTTOMMIDLE
           << SizeHandleElement::BOTTOMLEFT << SizeHandleElement::MIDDLELEFT;

    for (SizeHandleElement::EHandleLocation point_type : points) {
        SizeHandleElement* el = new SizeHandleElement(point_type, this);
        connect(el, SIGNAL(resize_request(bool)), this, SLOT(onSizeHandleElementRequest(bool)));
        el->setVisible(false);
        m_resize_handles[point_type] = el;
    }
}
