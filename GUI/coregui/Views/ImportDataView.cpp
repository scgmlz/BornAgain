// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataView.cpp
//! @brief     Implements class ImportDataView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/ImportDataView.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Views/CommonWidgets/ItemSelectorWidget.h"
#include "GUI/coregui/Views/ImportDataWidgets/RealDataSelectorWidget.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include "minisplitter.h"
#include <QVBoxLayout>

namespace
{
const bool reuse_widget = true;
}

ImportDataView::ImportDataView(MainWindow* mainWindow)
    : QWidget(mainWindow), m_splitter(new Manhattan::MiniSplitter),
      m_selectorWidget(new RealDataSelectorWidget),
      m_stackedWidget(new ItemStackPresenter<RealDataPresenter>(reuse_widget)),
      m_realDataModel(mainWindow->realDataModel())
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    m_stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_selectorWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    m_stackedWidget->setSizeHint(QSize(1024, 1024));

    m_splitter->addWidget(m_selectorWidget);
    m_splitter->addWidget(m_stackedWidget);
    m_splitter->setCollapsible(0, false);
    m_splitter->setCollapsible(1, false);

    m_splitter->setSizes(QList<int>() << Constants::ITEM_SELECTOR_WIDGET_WIDTH
                                      << Constants::ITEM_SELECTOR_WIDGET_WIDTH * 7);

    mainLayout->addWidget(m_splitter);

    setLayout(mainLayout);

    setupConnections();

    m_selectorWidget->setModels(mainWindow->instrumentModel(), mainWindow->realDataModel());
    m_stackedWidget->setModel(mainWindow->realDataModel());
}

void ImportDataView::onSelectionChanged(SessionItem* item)
{
    m_stackedWidget->setItem(item);
}

void ImportDataView::setupConnections()
{
    connect(m_selectorWidget, &RealDataSelectorWidget::selectionChanged, this,
            &ImportDataView::onSelectionChanged);
}
