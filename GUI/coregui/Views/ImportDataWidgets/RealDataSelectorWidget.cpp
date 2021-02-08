//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorWidget.cpp
//! @brief     Implements class RealDataSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/Views/ImportDataWidgets/RealDataSelectorWidget.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Views/CommonWidgets/ItemSelectorWidget.h"
#include "GUI/coregui/Views/ImportDataWidgets/RealDataPropertiesWidget.h"
#include "GUI/coregui/Views/ImportDataWidgets/RealDataSelectorActions.h"
#include "GUI/coregui/mainwindow/StyledToolBar.h"
#include <QItemSelectionModel>
#include <QLineEdit>
#include <QListView>
#include <QMenu>
#include <QSplitter>
#include <QVBoxLayout>

RealDataSelectorWidget::RealDataSelectorWidget(QWidget* parent)
    : QWidget(parent)
    , m_selectorActions(new RealDataSelectorActions(this))
    , m_selectorWidget(new ItemSelectorWidget)
    , m_propertiesWidget(new RealDataPropertiesWidget)
    , m_renameDataAction(new QAction(this))
{
    setMinimumSize(128, 600);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    setWindowTitle("RealDataSelectorWidget");

    m_renameDataAction->setText("Rename this data");
    m_renameDataAction->setIcon(QIcon()); // #TODO: Icon needed?
    m_renameDataAction->setIconText("Rename");
    m_renameDataAction->setToolTip("Rename data");
    connect(m_renameDataAction, &QAction::triggered, this,
            &RealDataSelectorWidget::onRenameDataRequest);

    QToolBar* toolBar = new StyledToolBar(this);
    toolBar->setMinimumSize(toolBar->minimumHeight(), toolBar->minimumHeight());
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolBar->addAction(m_selectorActions->m_import2dDataAction);
    toolBar->addAction(m_selectorActions->m_import1dDataAction);
    toolBar->addAction(m_selectorActions->m_removeDataAction);
    toolBar->addAction(m_selectorActions->m_rotateDataAction);

    auto splitter = new QSplitter;
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(m_selectorWidget);
    splitter->addWidget(m_propertiesWidget);
    splitter->setChildrenCollapsible(true);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(toolBar);
    mainLayout->addWidget(splitter);
    setLayout(mainLayout);

    connect(m_selectorWidget, &ItemSelectorWidget::contextMenuRequest, this,
            &RealDataSelectorWidget::onContextMenuRequest);

    connect(m_selectorWidget, &ItemSelectorWidget::selectionChanged, this,
            &RealDataSelectorWidget::onSelectionChanged);
}

QSize RealDataSelectorWidget::sizeHint() const
{
    return QSize(200, 400);
}

QSize RealDataSelectorWidget::minimumSizeHint() const
{
    return QSize(128, 200);
}

void RealDataSelectorWidget::setModels(InstrumentModel* instrumentModel,
                                       RealDataModel* realDataModel)
{
    m_selectorWidget->setModel(realDataModel);
    m_propertiesWidget->setModels(instrumentModel, realDataModel);

    m_selectorActions->setRealDataModel(realDataModel);
    m_selectorActions->setSelectionModel(m_selectorWidget->selectionModel());
}

void RealDataSelectorWidget::onSelectionChanged(SessionItem* item)
{
    m_propertiesWidget->setItem(item);
    emit selectionChanged(item);
}

void RealDataSelectorWidget::onContextMenuRequest(const QPoint& point,
                                                  const QModelIndex& indexAtPoint)
{

    const auto setAllActionsEnabled = [this](bool value) {
        m_selectorActions->m_import2dDataAction->setEnabled(value);
        m_selectorActions->m_import1dDataAction->setEnabled(value);
        m_selectorActions->m_rotateDataAction->setEnabled(value);
        m_selectorActions->m_removeDataAction->setEnabled(value);
        m_renameDataAction->setEnabled(value);
    };

    QMenu menu;
    menu.setToolTipsVisible(true);

    setAllActionsEnabled(indexAtPoint.isValid());

    m_selectorActions->m_import2dDataAction->setEnabled(true);
    m_selectorActions->m_import1dDataAction->setEnabled(true);

    menu.addAction(m_renameDataAction);
    menu.addAction(m_selectorActions->m_removeDataAction);
    menu.addAction(m_selectorActions->m_rotateDataAction);
    menu.addSeparator();
    menu.addAction(m_selectorActions->m_import2dDataAction);
    menu.addAction(m_selectorActions->m_import1dDataAction);
    menu.exec(point);
}

void RealDataSelectorWidget::onRenameDataRequest()
{
    QModelIndex currentIndex = m_selectorWidget->selectionModel()->currentIndex();
    if (!currentIndex.isValid())
        return;

    m_selectorWidget->listView()->edit(currentIndex);
}
