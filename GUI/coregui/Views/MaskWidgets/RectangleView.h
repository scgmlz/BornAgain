// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/RectangleView.h
//! @brief     Defines RectangleView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_RECTANGLEVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_RECTANGLEVIEW_H

#include "GUI/coregui/Views/MaskWidgets/RectangleBaseView.h"

//! This is a View of rectangular mask (represented by RectangleItem) on GraphicsScene.
//! Given view follows standard QGraphicsScene notations: (x,y) is top left corner.

class BA_CORE_API_ RectangleView : public RectangleBaseView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::RECTANGLE; }

    RectangleView();

protected slots:
    virtual void onChangedX();
    virtual void onChangedY();
    virtual void onPropertyChange(const QString& propertyName);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

protected:
    void update_position();
    QRectF mask_rectangle();
    qreal left() const;
    qreal right() const;
    qreal top() const;
    qreal bottom() const;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_RECTANGLEVIEW_H
