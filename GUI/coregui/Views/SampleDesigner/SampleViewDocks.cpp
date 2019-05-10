// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewDocks.h
//! @brief     Defines class SampleViewDocks
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SampleViewDocks.h"
#include "ApplicationModels.h"
#include "FilterPropertyProxy.h"
#include "ScriptPanel.h"
#include "SampleDesigner.h"
#include "SamplePropertyWidget.h"
#include "SampleTreeWidget.h"
#include "SampleView.h"
#include "SampleWidgetBox.h"
#include "RealSpacePanel.h"
#include <QDockWidget>
#include <QTreeView>
#include <QAction>

SampleViewDocks::SampleViewDocks(SampleView* parent)
    : DocksController(parent), m_sampleDesigner(new SampleDesigner(parent)),
      m_widgetBox(new SampleWidgetBox(sampleDesigner(), parent)),
      m_treeWidget(new SampleTreeWidget(parent, parent->models()->sampleModel())),
      m_propertyWidget(
          new SamplePropertyWidget(m_treeWidget->treeView()->selectionModel(), parent))
    , m_scriptPanel(new ScriptPanel(parent))
    , m_realSpacePanel(new RealSpacePanel(parent->models()->sampleModel(),
                                         m_treeWidget->treeView()->selectionModel(), parent))
{
    addWidget(WIDGET_BOX, m_widgetBox, Qt::LeftDockWidgetArea);
    addWidget(SAMPLE_TREE, m_treeWidget, Qt::RightDockWidgetArea);
    addWidget(PROPERTY_EDITOR, m_propertyWidget, Qt::RightDockWidgetArea);
    addWidget(INFO, m_scriptPanel, Qt::BottomDockWidgetArea);
    addWidget(REALSPACEPANEL, m_realSpacePanel, Qt::BottomDockWidgetArea);

    connect(m_scriptPanel, &ScriptPanel::widgetHeightRequest, this,
            &DocksController::setDockHeightForWidget);
    connect(m_scriptPanel, &ScriptPanel::widgetCloseRequest, this,
            &SampleViewDocks::onWidgetCloseRequest);

    m_scriptPanel->setSampleModel(parent->models()->sampleModel());
    m_scriptPanel->setInstrumentModel(parent->models()->instrumentModel());

    m_sampleDesigner->setModels(parent->models());
    m_sampleDesigner->setSelectionModel(
        m_treeWidget->treeView()->selectionModel(),
        dynamic_cast<FilterPropertyProxy*>(
            const_cast<QAbstractItemModel*>(m_treeWidget->treeView()->model())));

    parent->setCentralWidget(m_sampleDesigner->getCentralWidget());
    onResetLayout();
}

SampleWidgetBox* SampleViewDocks::widgetBox()
{
    return m_widgetBox;
}

SampleTreeWidget* SampleViewDocks::treeWidget()
{
    return m_treeWidget;
}

SamplePropertyWidget* SampleViewDocks::propertyWidget()
{
    return m_propertyWidget;
}

void SampleViewDocks::onResetLayout()
{
    DocksController::onResetLayout();
    mainWindow()->tabifyDockWidget(findDock(REALSPACEPANEL), findDock(INFO));
    findDock(REALSPACEPANEL)->raise(); // makes first tab active

    findDock(REALSPACEPANEL)->hide();
    findDock(INFO)->hide();
}

void SampleViewDocks::toggleDock(int id)
{
    auto dock = findDock(id);
    dock->setHidden(!dock->isHidden());
}

SampleDesigner* SampleViewDocks::sampleDesigner()
{
    return m_sampleDesigner;
}
