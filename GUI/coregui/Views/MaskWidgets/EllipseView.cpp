// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/EllipseView.cpp
//! @brief     Implements EllipseView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/EllipseView.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Views/MaskWidgets/SizeHandleElement.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

EllipseView::EllipseView() {}

void EllipseView::onChangedX()
{
    setBlockOnProperty(true);
    m_item->setItemValue(EllipseItem::P_XCENTER, fromSceneX(this->x()));
    setBlockOnProperty(false);
}

void EllipseView::onChangedY()
{
    setBlockOnProperty(true);
    m_item->setItemValue(EllipseItem::P_YCENTER, fromSceneY(this->y()));
    setBlockOnProperty(false);
}

void EllipseView::onPropertyChange(const QString& propertyName)
{
    if (propertyName == EllipseItem::P_XRADIUS || propertyName == EllipseItem::P_YRADIUS) {
        update_view();
    } else if (propertyName == EllipseItem::P_XCENTER) {
        setX(toSceneX(EllipseItem::P_XCENTER));
    } else if (propertyName == EllipseItem::P_YCENTER) {
        setY(toSceneY(EllipseItem::P_YCENTER));
    } else if (propertyName == EllipseItem::P_ANGLE) {
        setTransform(QTransform().rotate(-1.0 * par(EllipseItem::P_ANGLE)));
    }
}

void EllipseView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setRenderHints(QPainter::Antialiasing);
    bool mask_value = m_item->getItemValue(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
    painter->drawEllipse(m_mask_rect);
}

void EllipseView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if (m_activeHandleElement) {
        QPointF opposPos = mapFromScene(m_resize_opposite_origin);
        qreal xmin = std::min(event->pos().x(), opposPos.x());
        qreal xmax = std::max(event->pos().x(), opposPos.x());
        qreal ymin = std::min(event->pos().y(), opposPos.y());
        qreal ymax = std::max(event->pos().y(), opposPos.y());
        qreal width = xmax - xmin;
        qreal height = ymax - ymin;

        qreal xcenter = xmin + (xmax - xmin) / 2.;
        qreal ycenter = ymin + (ymax - ymin) / 2.;

        QPointF center(xcenter, ycenter);
        QPointF centerInScene = mapToScene(center);

        if (m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE) {
            m_item->setItemValue(EllipseItem::P_XCENTER, fromSceneX(centerInScene.x()));
            m_item->setItemValue(EllipseItem::P_YCENTER, fromSceneY(centerInScene.y()));

            m_item->setItemValue(EllipseItem::P_XRADIUS,
                                 (fromSceneX(centerInScene.x() + width / 2.)
                                  - fromSceneX(centerInScene.x() - width / 2.))
                                     / 2.);
            m_item->setItemValue(EllipseItem::P_YRADIUS,
                                 (fromSceneY(centerInScene.y() - height / 2.)
                                  - fromSceneY(centerInScene.y() + height / 2.))
                                     / 2.);

        } else if (m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_HEIGHT) {
            m_item->setItemValue(EllipseItem::P_YCENTER, fromSceneY(centerInScene.y()));
            m_item->setItemValue(EllipseItem::P_YRADIUS,
                                 (fromSceneY(centerInScene.y() - height / 2.)
                                  - fromSceneY(centerInScene.y() + height / 2.))
                                     / 2.);

        } else if (m_activeHandleElement->getHandleType() == SizeHandleElement::RESIZE_WIDTH) {
            m_item->setItemValue(EllipseItem::P_XCENTER, fromSceneX(centerInScene.x()));
            m_item->setItemValue(EllipseItem::P_XRADIUS,
                                 (fromSceneX(centerInScene.x() + width / 2.)
                                  - fromSceneX(centerInScene.x() - width / 2.))
                                     / 2.);
        }

    } else {
        IShape2DView::mouseMoveEvent(event);
    }
}

//! updates position of view using item properties

void EllipseView::update_position()
{
    disconnect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    disconnect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));

    setX(toSceneX(EllipseItem::P_XCENTER));
    setY(toSceneY(EllipseItem::P_YCENTER));

    connect(this, SIGNAL(xChanged()), this, SLOT(onChangedX()));
    connect(this, SIGNAL(yChanged()), this, SLOT(onChangedY()));

    if (par(EllipseItem::P_ANGLE) != 0.0)
        setTransform(QTransform().rotate(-1.0 * par(EllipseItem::P_ANGLE)));
}

QRectF EllipseView::mask_rectangle()
{
    return QRectF(-width() / 2., -height() / 2., width(), height());
}

//! returns the x-coordinate of the rectangle's left edge

qreal EllipseView::left() const
{
    return toSceneX(par(EllipseItem::P_XCENTER) - par(EllipseItem::P_XRADIUS));
}

//! returns the x-coordinate of the rectangle's right edge

qreal EllipseView::right() const
{
    return toSceneX(par(EllipseItem::P_XCENTER) + par(EllipseItem::P_XRADIUS));
}

//! Returns the y-coordinate of the rectangle's top edge.

qreal EllipseView::top() const
{
    return toSceneY(par(EllipseItem::P_YCENTER) + par(EllipseItem::P_YRADIUS));
}

//! Returns the y-coordinate of the rectangle's bottom edge.

qreal EllipseView::bottom() const
{
    return toSceneY(par(EllipseItem::P_YCENTER) - par(EllipseItem::P_YRADIUS));
}
