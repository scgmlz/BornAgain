// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/LineViews.h
//! @brief     Defines classes VerticalLineView and HorizontalLineView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_LINEVIEWS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_LINEVIEWS_H

#include "GUI/coregui/Views/MaskWidgets/IShape2DView.h"

//! This is a view of VerticalLineItem mask

class BA_CORE_API_ VerticalLineView : public IShape2DView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::VERTICALLINE; }

    VerticalLineView();

protected slots:
    virtual void update_view();
    virtual void onChangedX();
    virtual void onPropertyChange(const QString& propertyName);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);
};

//! This is a view of HorizontalLineItem mask

class BA_CORE_API_ HorizontalLineView : public IShape2DView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::HORIZONTALLINE; }

    HorizontalLineView();

protected slots:
    virtual void update_view();
    virtual void onChangedY();
    virtual void onPropertyChange(const QString& propertyName);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_LINEVIEWS_H
