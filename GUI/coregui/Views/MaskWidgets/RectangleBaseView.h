// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/RectangleBaseView.h
//! @brief     Defines RectangleBaseView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_RECTANGLEBASEVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_RECTANGLEBASEVIEW_H

#include "GUI/coregui/Views/MaskWidgets/IShape2DView.h"
#include "GUI/coregui/Views/MaskWidgets/SizeHandleElement.h"
#include <QMap>

//! Base view for all rectangular-like masks.

class BA_CORE_API_ RectangleBaseView : public IShape2DView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::RECTANGLEBASE; }

    RectangleBaseView();

private slots:
    void onSizeHandleElementRequest(bool going_to_resize);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void update_view();

    virtual void update_bounding_rect();
    virtual void update_position() = 0;
    virtual QRectF mask_rectangle() = 0;
    virtual qreal left() const = 0;
    virtual qreal right() const = 0;
    virtual qreal top() const = 0;
    virtual qreal bottom() const = 0;

    qreal width() const;
    qreal height() const;

    void create_size_handle_elements();
    QRectF m_mask_rect; //!< mask rectangle in scene coordinates
    QMap<SizeHandleElement::EHandleLocation, SizeHandleElement*> m_resize_handles;
    //!< coordinates of corner opposite to the grip corner at the moment it first clicked
    //!< in scene coordinates
    QPointF m_resize_opposite_origin;
    SizeHandleElement* m_activeHandleElement;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_RECTANGLEBASEVIEW_H
