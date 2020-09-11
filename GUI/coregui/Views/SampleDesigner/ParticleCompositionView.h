// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleCompositionView.h
//! @brief     Defines class ParticleCompositionView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_PARTICLECOMPOSITIONVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_PARTICLECOMPOSITIONVIEW_H

#include "GUI/coregui/Views/SampleDesigner/ConnectableView.h"

//! Class representing view of Particle item
class BA_CORE_API_ ParticleCompositionView : public ConnectableView
{
    Q_OBJECT

public:
    ParticleCompositionView(QGraphicsItem* parent = 0);

    int type() const { return ViewTypes::PARTICLE; }

    void addView(IView* childView, int row = 0);
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_PARTICLECOMPOSITIONVIEW_H
