// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewActions.cpp
//! @brief     Implements class SampleViewActions
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SampleDesigner/SampleViewActions.h"
#include "GUI/coregui/Views/SampleDesigner/SampleViewDocks.h"
#include "GUI/coregui/Views/SampleView.h"
#include <QAction>
#include <QDockWidget>

SampleViewActions::SampleViewActions(SampleModel* model, SampleView* parent)
    : QObject(parent), m_model(model), m_sampleView(parent), m_selection_model(nullptr)
{
}

void SampleViewActions::setSelectionModel(QItemSelectionModel* selection_model)
{
    m_selection_model = selection_model;
}

SampleModel* SampleViewActions::sampleModel()
{
    return m_model;
}

QItemSelectionModel* SampleViewActions::selectionModel()
{
    return m_selection_model;
}

void SampleViewActions::onToggleRealSpaceView()
{
    m_sampleView->docks()->toggleDock(SampleViewDocks::REALSPACEPANEL);
}
