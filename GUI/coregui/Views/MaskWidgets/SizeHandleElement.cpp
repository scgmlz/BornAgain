// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/SizeHandleElement.cpp
//! @brief     Implements SizeHandleElement class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/MaskWidgets/SizeHandleElement.h"
#include "GUI/coregui/Views/MaskWidgets/ISceneAdaptor.h"
#include "GUI/coregui/Views/MaskWidgets/MaskEditorHelper.h"
#include <QGraphicsSceneHoverEvent>
#include <QPainter>

namespace
{
QMap<SizeHandleElement::EHandleLocation, Qt::CursorShape> create_cursors_map()
{
    QMap<SizeHandleElement::EHandleLocation, Qt::CursorShape> result;
    result[SizeHandleElement::NONE] = Qt::ArrowCursor;
    result[SizeHandleElement::TOPLEFT] = Qt::SizeFDiagCursor;
    result[SizeHandleElement::TOPMIDDLE] = Qt::SizeVerCursor;
    result[SizeHandleElement::TOPRIGHT] = Qt::SizeBDiagCursor;
    result[SizeHandleElement::MIDDLERIGHT] = Qt::SizeHorCursor;
    result[SizeHandleElement::BOTTOMRIGHT] = Qt::SizeFDiagCursor;
    result[SizeHandleElement::BOTTOMMIDLE] = Qt::SizeVerCursor;
    result[SizeHandleElement::BOTTOMLEFT] = Qt::SizeBDiagCursor;
    result[SizeHandleElement::MIDDLELEFT] = Qt::SizeHorCursor;
    return result;
}

QMap<SizeHandleElement::EHandleLocation, SizeHandleElement::EHandleType>
create_location_to_type_map()
{
    QMap<SizeHandleElement::EHandleLocation, SizeHandleElement::EHandleType> result;
    result[SizeHandleElement::NONE] = SizeHandleElement::RESIZE;
    result[SizeHandleElement::TOPLEFT] = SizeHandleElement::RESIZE;
    result[SizeHandleElement::TOPMIDDLE] = SizeHandleElement::RESIZE_HEIGHT;
    result[SizeHandleElement::TOPRIGHT] = SizeHandleElement::RESIZE;
    result[SizeHandleElement::MIDDLERIGHT] = SizeHandleElement::RESIZE_WIDTH;
    result[SizeHandleElement::BOTTOMRIGHT] = SizeHandleElement::RESIZE;
    result[SizeHandleElement::BOTTOMMIDLE] = SizeHandleElement::RESIZE_HEIGHT;
    result[SizeHandleElement::BOTTOMLEFT] = SizeHandleElement::RESIZE;
    result[SizeHandleElement::MIDDLELEFT] = SizeHandleElement::RESIZE_WIDTH;
    return result;
}

QMap<SizeHandleElement::EHandleLocation, SizeHandleElement::EHandleLocation>
getMapOfOppositeCorners()
{
    QMap<SizeHandleElement::EHandleLocation, SizeHandleElement::EHandleLocation> result;
    result[SizeHandleElement::TOPLEFT] = SizeHandleElement::BOTTOMRIGHT;
    result[SizeHandleElement::TOPMIDDLE] = SizeHandleElement::BOTTOMMIDLE;
    result[SizeHandleElement::TOPRIGHT] = SizeHandleElement::BOTTOMLEFT;
    result[SizeHandleElement::MIDDLERIGHT] = SizeHandleElement::MIDDLELEFT;
    result[SizeHandleElement::BOTTOMRIGHT] = SizeHandleElement::TOPLEFT;
    result[SizeHandleElement::BOTTOMMIDLE] = SizeHandleElement::TOPMIDDLE;
    result[SizeHandleElement::BOTTOMLEFT] = SizeHandleElement::TOPRIGHT;
    result[SizeHandleElement::MIDDLELEFT] = SizeHandleElement::MIDDLERIGHT;
    return result;
}

} // namespace

QMap<SizeHandleElement::EHandleLocation, SizeHandleElement::EHandleType>
    SizeHandleElement::m_location_to_type = create_location_to_type_map();

QMap<SizeHandleElement::EHandleLocation, Qt::CursorShape> SizeHandleElement::m_cursors =
    create_cursors_map();

QMap<SizeHandleElement::EHandleLocation, SizeHandleElement::EHandleLocation>
    SizeHandleElement::m_opposite_handle_location = getMapOfOppositeCorners();

// ----------------------------------------------------------------------------

SizeHandleElement::SizeHandleElement(EHandleLocation pointType, QGraphicsObject* parent)
    : QGraphicsObject(parent), m_handleLocation(pointType),
      m_handleType(m_location_to_type[pointType])
{
    setCursor(m_cursors[m_handleLocation]);
    setParentItem(parent);
}

QRectF SizeHandleElement::boundingRect() const
{
    return QRectF(-4, -4, 8, 8);
}

void SizeHandleElement::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setRenderHints(QPainter::Antialiasing);

    painter->setBrush(MaskEditorHelper::getSelectionMarkerBrush());
    painter->setPen(MaskEditorHelper::getSelectionMarkerPen());
    if (getHandleType() == RESIZE) {
        painter->drawRect(boundingRect());
    } else {
        painter->drawEllipse(boundingRect());
    }
}

void SizeHandleElement::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit resize_request(true);
    QGraphicsObject::mousePressEvent(event);
}

void SizeHandleElement::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    emit resize_request(false);
    QGraphicsObject::mouseReleaseEvent(event);
}

//! set position from location type using coordinates of external rectangle
void SizeHandleElement::updateHandleElementPosition(const QRectF& rect)
{
    if (m_handleLocation == TOPLEFT) {
        setPos(rect.topLeft());
    }

    else if (m_handleLocation == TOPMIDDLE) {
        setPos(QPointF(rect.x() + rect.width() / 2., rect.y()));
    }

    else if (m_handleLocation == TOPRIGHT) {
        setPos(rect.topRight());
    }

    else if (m_handleLocation == MIDDLERIGHT) {
        setPos(QPointF(rect.x() + rect.width(), rect.y() + rect.height() / 2.));
    }

    else if (m_handleLocation == BOTTOMRIGHT) {
        setPos(rect.bottomRight());
    }

    else if (m_handleLocation == BOTTOMMIDLE) {
        setPos(QPointF(rect.x() + rect.width() / 2., rect.y() + rect.height()));
    }

    else if (m_handleLocation == BOTTOMLEFT) {
        setPos(rect.bottomLeft());
    }

    else if (m_handleLocation == MIDDLELEFT) {
        setPos(QPointF(rect.x(), rect.y() + rect.height() / 2.));
    }
}

SizeHandleElement::EHandleLocation SizeHandleElement::getHandleLocation() const
{
    return m_handleLocation;
}

SizeHandleElement::EHandleLocation SizeHandleElement::getOppositeHandleLocation() const
{
    return m_opposite_handle_location[m_handleLocation];
}

SizeHandleElement::EHandleType SizeHandleElement::getHandleType() const
{
    return m_handleType;
}

void SizeHandleElement::update_view()
{
    update();
}
