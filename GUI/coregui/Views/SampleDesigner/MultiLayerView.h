// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/MultiLayerView.h
//! @brief     Defines class MultiLayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_MULTILAYERVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_MULTILAYERVIEW_H

#include "GUI/coregui/Views/SampleDesigner/ILayerView.h"

class DesignerMimeData;
class QGraphicsSceneDragDropEvent;

//! Class representing view of MultiLayer.
//! Handles drop of other MultiLayer and Layer views on top of it
class BA_CORE_API_ MultiLayerView : public ILayerView
{
    Q_OBJECT

public:
    MultiLayerView(QGraphicsItem* parent = 0);

    int type() const override { return ViewTypes::MULTILAYER; }

    QRectF boundingRect() const override;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void addView(IView* childView, int row = 0) override;

    virtual void addNewLayer(ILayerView* layer, int row);
    virtual void removeLayer(ILayerView* layer);

    int getDropArea(QPointF pos);
    QRectF getDropAreaRectangle(int row);
    QLineF getInterfaceLine(int row);

public slots:
    void updateGeometry();
    void updateHeight();
    void updateWidth();
    void onLayerAboutToBeDeleted();

protected:
    void dropEvent(QGraphicsSceneDragDropEvent* event) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent* event) override;
    const DesignerMimeData* checkDragEvent(QGraphicsSceneDragDropEvent* event);
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

private:
    QList<ILayerView*> m_layers;
    QList<QRectF> m_drop_areas;
    QList<QLineF> m_interfaces;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_MULTILAYERVIEW_H
