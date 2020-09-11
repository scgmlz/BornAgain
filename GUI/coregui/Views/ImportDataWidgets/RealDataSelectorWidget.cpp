// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/RealDataSelectorWidget.cpp
//! @brief     Implements class RealDataSelectorWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/ImportDataWidgets/RealDataSelectorWidget.h"
#include "GUI/coregui/Models/RealDataModel.h"
#include "GUI/coregui/Views/CommonWidgets/ItemSelectorWidget.h"
#include "GUI/coregui/Views/ImportDataWidgets/RealDataPropertiesWidget.h"
#include "GUI/coregui/Views/ImportDataWidgets/RealDataSelectorActions.h"
#include "GUI/coregui/Views/ImportDataWidgets/RealDataSelectorHBar.h"
#include "GUI/coregui/Views/ImportDataWidgets/RealDataSelectorToolBar.h"
#include "minisplitter.h"
#include <QItemSelectionModel>
#include <QVBoxLayout>

RealDataSelectorWidget::RealDataSelectorWidget(QWidget* parent)
    : QWidget(parent), m_selectorActions(new RealDataSelectorActions(this)),
      m_toolBar(new RealDataSelectorToolBar(m_selectorActions, this)),
      m_hamBar(new RealDataSelectorHBar(m_selectorActions, this)),
      m_splitter(new Manhattan::MiniSplitter), m_selectorWidget(new ItemSelectorWidget),
      m_propertiesWidget(new RealDataPropertiesWidget)
{
    setMinimumSize(128, 600);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    setWindowTitle("RealDataSelectorWidget");

    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_selectorWidget);
    m_splitter->addWidget(m_propertiesWidget);
    m_splitter->setChildrenCollapsible(true);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_toolBar);
    mainLayout->addWidget(m_hamBar);
    mainLayout->addWidget(m_splitter);
    setLayout(mainLayout);

    connect(m_selectorWidget, &ItemSelectorWidget::contextMenuRequest, m_selectorActions,
            &RealDataSelectorActions::onContextMenuRequest);

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
