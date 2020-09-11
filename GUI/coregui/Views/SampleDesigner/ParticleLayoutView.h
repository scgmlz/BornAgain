// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/ParticleLayoutView.h
//! @brief     Defines class ParticleLayoutView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_PARTICLELAYOUTVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_PARTICLELAYOUTVIEW_H

#include "GUI/coregui/Views/SampleDesigner/ConnectableView.h"

class BA_CORE_API_ ParticleLayoutView : public ConnectableView
{
public:
    ParticleLayoutView(QGraphicsItem* parent = 0);

    int type() const { return ViewTypes::PARTICLE_LAYOUT; }

    void addView(IView* childView, int row = 0); // to add Particle
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_PARTICLELAYOUTVIEW_H
