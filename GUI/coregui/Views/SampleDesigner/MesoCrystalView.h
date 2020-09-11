// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/MesoCrystalView.h
//! @brief     Defines class MesoCrystalView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_MESOCRYSTALVIEW_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_MESOCRYSTALVIEW_H

#include "GUI/coregui/Views/SampleDesigner/ConnectableView.h"

//! Class representing view of a meso crystal item
class BA_CORE_API_ MesoCrystalView : public ConnectableView
{
    Q_OBJECT

public:
    MesoCrystalView(QGraphicsItem* parent = 0);

    int type() const { return ViewTypes::PARTICLE; }

    void addView(IView* childView, int row = 0);
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SAMPLEDESIGNER_MESOCRYSTALVIEW_H
