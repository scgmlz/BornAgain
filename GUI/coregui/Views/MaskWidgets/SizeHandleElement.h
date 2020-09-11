// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/SizeHandleElement.h
//! @brief     Defines SizeHandleElement class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_SIZEHANDLEELEMENT_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_SIZEHANDLEELEMENT_H

#include "GUI/coregui/Views/MaskWidgets/MaskEditorHelper.h"
#include <QCursor>
#include <QGraphicsObject>
#include <QMap>

//! Size handle on top of RectangleView represented as small circle or small rectangle.
//! Placed either in corners on in the middle of the edge.

class BA_CORE_API_ SizeHandleElement : public QGraphicsObject
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::SIZEHANDLE; }

    enum EHandleLocation {
        NONE,
        TOPLEFT,
        TOPMIDDLE,
        TOPRIGHT,
        MIDDLELEFT,
        MIDDLERIGHT,
        BOTTOMLEFT,
        BOTTOMMIDLE,
        BOTTOMRIGHT,
    };

    enum EHandleType { RESIZE, RESIZE_WIDTH, RESIZE_HEIGHT };

    SizeHandleElement(EHandleLocation pointType, QGraphicsObject* parent = 0);

    QRectF boundingRect() const;

    void updateHandleElementPosition(const QRectF& rect);

    EHandleLocation getHandleLocation() const;
    EHandleLocation getOppositeHandleLocation() const;
    EHandleType getHandleType() const;

public slots:
    virtual void update_view();

signals:
    void resize_request(bool going_to_resize);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    EHandleLocation m_handleLocation;
    EHandleType m_handleType;
    static QMap<EHandleLocation, Qt::CursorShape> m_cursors;
    static QMap<EHandleLocation, EHandleType> m_location_to_type;
    static QMap<EHandleLocation, EHandleLocation> m_opposite_handle_location;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_SIZEHANDLEELEMENT_H
