// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationOptionsWidget.cpp
//! @brief     Implements class SimulationOptionsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SimulationWidgets/SimulationOptionsWidget.h"
#include "GUI/coregui/Models/SimulationOptionsItem.h"
#include "GUI/coregui/Views/PropertyEditor/ComponentFlatView.h"
#include <QGroupBox>
#include <QVBoxLayout>

SimulationOptionsWidget::SimulationOptionsWidget(QWidget* parent)
    : QWidget(parent), m_boxEditor(new ComponentFlatView)
{
    auto groupBox = new QGroupBox("Simulation Parameters");

    auto groupLayout = new QVBoxLayout;
    groupBox->setLayout(groupLayout);

    groupLayout->addWidget(m_boxEditor);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(groupBox);
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void SimulationOptionsWidget::setItem(SimulationOptionsItem* item)
{
    m_boxEditor->clearEditor();
    m_boxEditor->setItem(item);
}
