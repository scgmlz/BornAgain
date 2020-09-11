// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationOptionsWidget.h
//! @brief     Defines class SimulationOptionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_SIMULATIONOPTIONSWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_SIMULATIONOPTIONSWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class SimulationOptionsItem;
class ComponentFlatView;

//! Holds widgets related to the setup of simulation/job options (nthreads, run policy,
//! computation method). Part of SimulationView/SimulationSetupWidet

class BA_CORE_API_ SimulationOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationOptionsWidget(QWidget* parent = nullptr);

    void setItem(SimulationOptionsItem* item);

private:
    ComponentFlatView* m_boxEditor;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_SIMULATIONOPTIONSWIDGET_H
