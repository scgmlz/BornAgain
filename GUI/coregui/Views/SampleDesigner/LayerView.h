// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/LayerView.h
//! @brief     Defines class LayerView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_LAYERVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_LAYERVIEW_H

#include "GUI/coregui/Views/SampleDesigner/ILayerView.h"

//! Class that represents view of Layer
class BA_CORE_API_ LayerView : public ILayerView
{
    Q_OBJECT
public:
    LayerView(QGraphicsItem* parent = 0);

    virtual int type() const { return ViewTypes::LAYER; }

    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

    virtual void addView(IView* childView, int row = 0); // to add ParticleLayout
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_LAYERVIEW_H
