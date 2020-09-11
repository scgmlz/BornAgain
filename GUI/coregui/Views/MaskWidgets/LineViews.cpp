// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/LineViews.cpp
//! @brief     Implements classes VerticalLineView and HorizontalLineView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/LineViews.h"
#include "GUI/coregui/Models/MaskItems.h"
#include "GUI/coregui/Views/MaskWidgets/ColorMapSceneAdaptor.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditorHelper.h"
#include <QCursor>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace
{
const double mask_width = 8.0;
const double mask_visible_width = 3.0;
} // namespace

VerticalLineView::VerticalLineView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setCursor(Qt::SizeHorCursor);
}

void VerticalLineView::onChangedX()
{
    setBlockOnProperty(true);
    m_item->setItemValue(VerticalLineItem::P_POSX, fromSceneX(this->x()));
    setBlockOnProperty(false);
}

void VerticalLineView::onPropertyChange(const QString& propertyName)
{
    if (propertyName == VerticalLineItem::P_POSX)
        setX(toSceneX(VerticalLineItem::P_POSX));
}

void VerticalLineView::update_view()
{
    QRectF plot_scene_rectangle = m_adaptor->viewportRectangle();

    setX(toSceneX(VerticalLineItem::P_POSX));
    setY(plot_scene_rectangle.top());

    m_bounding_rect = QRectF(-mask_width / 2., 0.0, mask_width, plot_scene_rectangle.height());
    update();
}

void VerticalLineView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    bool mask_value = m_item->getItemValue(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
    painter->drawRect(
        QRectF(-mask_visible_width / 2., 0.0, mask_visible_width, m_bounding_rect.height()));

    if (isSelected()) {
        QPen pen;
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(
            QRectF(-mask_visible_width / 2., 0.0, mask_visible_width, m_bounding_rect.height()));
    }
}

//! Allows item movement along x, prevent movement along y
QVariant VerticalLineView::itemChange(QGraphicsItem::GraphicsItemChange change,
                                      const QVariant& value)
{
    if (isSelected() && change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        newPos.setY(y());
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}

// --------------------------------------------------------------------------------------------- //

HorizontalLineView::HorizontalLineView()
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setCursor(Qt::SizeVerCursor);
}

void HorizontalLineView::onChangedY()
{
    setBlockOnProperty(true);
    m_item->setItemValue(HorizontalLineItem::P_POSY, fromSceneY(this->y()));
    setBlockOnProperty(false);
}

void HorizontalLineView::onPropertyChange(const QString& propertyName)
{
    if (propertyName == HorizontalLineItem::P_POSY)
        setY(toSceneY(HorizontalLineItem::P_POSY));
}

void HorizontalLineView::update_view()
{
    QRectF plot_scene_rectangle = m_adaptor->viewportRectangle();

    setX(plot_scene_rectangle.left());
    setY(toSceneY(HorizontalLineItem::P_POSY));

    m_bounding_rect = QRectF(0.0, -mask_width / 2., plot_scene_rectangle.width(), mask_width);
    update();
}

void HorizontalLineView::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    bool mask_value = m_item->getItemValue(MaskItem::P_MASK_VALUE).toBool();
    painter->setBrush(MaskEditorHelper::getMaskBrush(mask_value));
    painter->setPen(MaskEditorHelper::getMaskPen(mask_value));
    painter->drawRect(
        QRectF(0.0, -mask_visible_width / 2., m_bounding_rect.width(), mask_visible_width));

    if (isSelected()) {
        QPen pen;
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(
            QRectF(0.0, -mask_visible_width / 2., m_bounding_rect.width(), mask_visible_width));
    }
}

//! Allows item movement along y, prevent movement along x
QVariant HorizontalLineView::itemChange(QGraphicsItem::GraphicsItemChange change,
                                        const QVariant& value)
{
    if (isSelected() && change == ItemPositionChange && scene()) {
        QPointF newPos = value.toPointF();
        newPos.setX(x());
        return newPos;
    }
    return QGraphicsItem::itemChange(change, value);
}
