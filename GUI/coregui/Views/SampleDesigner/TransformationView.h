// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/TransformationView.h
//! @brief     Defines class TransformationView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_TRANSFORMATIONVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_TRANSFORMATIONVIEW_H

#include "GUI/coregui/Views/SampleDesigner/ConnectableView.h"

class TransformationView : public ConnectableView
{
    Q_OBJECT

public:
    TransformationView(QGraphicsItem* parent = 0);

    int type() const { return ViewTypes::TRANSFORMATION; }
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_TRANSFORMATIONVIEW_H
