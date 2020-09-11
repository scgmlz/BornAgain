// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaskWidgets/PolygonView.h
//! @brief     Defines PolygonView class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_POLYGONVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_POLYGONVIEW_H

#include "GUI/coregui/Views/MaskWidgets/IShape2DView.h"
#include <QPolygonF>

//! This is a View of polygon mask (represented by PolygonItem) on GraphicsScene.

class BA_CORE_API_ PolygonView : public IShape2DView
{
    Q_OBJECT

public:
    int type() const { return MaskEditorHelper::POLYGON; }

    PolygonView();

    void addView(IShape2DView* childView, int row);
    bool isClosedPolygon();
    QPointF lastAddedPoint() const;

public slots:
    bool closePolygonIfNecessary();
    void onClosePolygonRequest(bool value);

protected slots:
    void update_view();

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

private:
    void update_polygon();
    void update_points();
    void setChildrenVisible(bool value);
    bool makePolygonClosed();

    QPolygonF m_polygon;
    bool m_block_on_point_update;
    bool m_close_polygon_request;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MASKWIDGETS_POLYGONVIEW_H
