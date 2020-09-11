// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationSetupWidget.h
//! @brief     Defines class SimulationSetupWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_SIMULATIONSETUPWIDGET_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_SIMULATIONSETUPWIDGET_H

#include "Wrap/WinDllMacros.h"
#include <QWidget>

class QPushButton;
class MultiLayerItem;
class SimulationDataSelectorWidget;
class SimulationOptionsWidget;
class ApplicationModels;

//! The SimulationSetupWidget class represents a main widget to define simulation settings
//! and run the simulation. Belongs to the SimulationView.

class BA_CORE_API_ SimulationSetupWidget : public QWidget
{
    Q_OBJECT

public:
    SimulationSetupWidget(QWidget* parent = 0);

    void setApplicationModels(ApplicationModels* model);
    void updateViewElements();

public slots:
    void onRunSimulation();
    void onExportToPythonScript();

private:
    QWidget* createButtonWidget();

    ApplicationModels* m_applicationModels;

    QPushButton* runSimulationButton;
    QPushButton* exportToPyScriptButton;

    SimulationDataSelectorWidget* m_simDataSelectorWidget;
    SimulationOptionsWidget* m_simOptionsWidget;
};

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_SIMULATIONWIDGETS_SIMULATIONSETUPWIDGET_H
