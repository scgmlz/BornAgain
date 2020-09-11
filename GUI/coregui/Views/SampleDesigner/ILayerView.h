// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ILayerView.h
//! @brief     Defines class ILayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_ILAYERVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_ILAYERVIEW_H

#include "GUI/coregui/Views/SampleDesigner/ConnectableView.h"

class MultiLayerView;
class MultiLayerCandidate;

//! Base class for LayerView and MultiLayerView
//! Provides functionality for moving view on top of MultiLayer.
class BA_CORE_API_ ILayerView : public ConnectableView
{
    Q_OBJECT

public:
    ILayerView(QGraphicsItem* parent = 0);

    int type() const { return ViewTypes::LAYER; }

    virtual QString getLabel() const { return ""; }

    void updateLabel();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void update_appearance();

public slots:
    void onPropertyChange(const QString& propertyName);

private:
    void updateHeight();
    void updateColor();

    MultiLayerCandidate getMultiLayerCandidate();
    QPointF m_drag_start_position;
};

//! Class to hold MultiLayer candidate for dropping LayerView.
class MultiLayerCandidate
{
public:
    MultiLayerCandidate() : multilayer(0), row(-1), distance(0) {}
    MultiLayerView* multilayer; //!< pointer to the candidate
    int row;                    //!< requested row number to drop in
    int distance;               //!< distance from given ILayerView and drop area
    bool operator<(const MultiLayerCandidate& cmp) const;
    operator bool() const { return bool(multilayer); }
    //! returns line representing interface of multilayer in scene coordinates
    QLineF getInterfaceToScene();
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_ILAYERVIEW_H
