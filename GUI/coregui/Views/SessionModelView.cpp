// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SessionModelView.cpp
//! @brief     Implements class SessionModelView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/SessionModelView.h"
#include "GUI/coregui/Models/InstrumentModel.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Models/SampleModel.h"
#include "GUI/coregui/Models/SessionModelDelegate.h"
#include "GUI/coregui/Views/CommonWidgets/ModelTreeView.h"
#include "GUI/coregui/Views/TestView.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>

namespace
{
const bool show_test_view = false;
}

SessionModelView::SessionModelView(MainWindow* mainWindow)
    : QWidget(mainWindow), m_mainWindow(mainWindow), m_toolBar(new QToolBar),
      m_tabs(new QTabWidget), m_expandCollapseButton(new QToolButton),
      m_delegate(new SessionModelDelegate(this))
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    m_expandCollapseButton->setText("Expand / collapse tree");
    m_expandCollapseButton->setIcon(QIcon(":/images/toolbar_expand_collapse_tree.svg"));
    m_expandCollapseButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_expandCollapseButton->setToolTip("Click to  switch between expanded/collapsed tree view");
    m_toolBar->addWidget(m_expandCollapseButton);
    connect(m_expandCollapseButton, SIGNAL(clicked()), this, SLOT(onExpandCollapseTree()));

    layout->addWidget(m_toolBar);
    layout->addWidget(m_tabs);
    setLayout(layout);

    init_tabs();

    if (show_test_view)
        init_test_view();
}

void SessionModelView::onExpandCollapseTree()
{
    m_content.at(m_tabs->currentIndex())->toggleExpanded();
}

//! Creates content for tab widget.

void SessionModelView::init_tabs()
{
    ASSERT(m_content.empty());

    for (auto model : modelsForTabs()) {
        auto treeView = new ModelTreeView(this, model);
        treeView->setItemDelegate(m_delegate);
        m_tabs->addTab(treeView, treeView->objectName());
        m_content.push_back(treeView);
    }
}

//! Returns list of models to show in tabs.

QList<SessionModel*> SessionModelView::modelsForTabs()
{
    QList<SessionModel*> result = QList<SessionModel*>()
                                  << m_mainWindow->instrumentModel() << m_mainWindow->sampleModel()
                                  << m_mainWindow->realDataModel() << m_mainWindow->materialModel()
                                  << m_mainWindow->jobModel();
    return result;
}

void SessionModelView::init_test_view()
{
    auto view = new TestView(m_mainWindow);
    int index = m_tabs->addTab(view, "Test View");
    m_tabs->setCurrentIndex(index);
}
