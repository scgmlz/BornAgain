// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationView.cpp
//! @brief     Implements class SimulationView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SimulationView.h"
#include "GUI/coregui/Views/SimulationWidgets/SimulationSetupWidget.h"
#include "GUI/coregui/mainwindow/StyledToolBar.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include <QVBoxLayout>

SimulationView::SimulationView(MainWindow* mainWindow)
    : QWidget(mainWindow), m_simulationSetupWidget(new SimulationSetupWidget),
      m_toolBar(new StyledToolBar)
{
    m_toolBar->setFixedHeight(m_toolBar->minimumHeight());
    m_simulationSetupWidget->setApplicationModels(mainWindow->models());

    auto* mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_simulationSetupWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void SimulationView::onRunSimulationShortcut()
{
    m_simulationSetupWidget->onRunSimulation();
}

void SimulationView::showEvent(QShowEvent*)
{
    updateSimulationViewElements();
}

void SimulationView::updateSimulationViewElements()
{
    m_simulationSetupWidget->updateViewElements();
}
