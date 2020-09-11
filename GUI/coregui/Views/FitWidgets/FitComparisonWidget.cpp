// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitComparisonWidget.cpp
//! @brief     Implements class FitComparisonWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/FitComparisonWidget.h"
#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/RealDataItem.h"
#include "GUI/coregui/Views/FitWidgets/FitComparisonController.h"
#include "GUI/coregui/Views/FitWidgets/FitFlowWidget.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMap.h"
#include "GUI/coregui/Views/IntensityDataWidgets/ColorMapCanvas.h"
#include "GUI/coregui/Views/IntensityDataWidgets/IntensityDataPropertyWidget.h"
#include "GUI/coregui/Views/IntensityDataWidgets/PlotStatusLabel.h"
#include <QAction>
#include <QGridLayout>
#include <QVBoxLayout>

FitComparisonWidget::FitComparisonWidget(QWidget* parent)
    : SessionItemWidget(parent), m_realDataPlot(new ColorMapCanvas),
      m_simulatedDataPlot(new ColorMapCanvas), m_relativeDiffPlot(new ColorMapCanvas),
      m_fitFlowWidget(new FitFlowWidget), m_statusLabel(new PlotStatusLabel(nullptr, this)),
      m_propertyWidget(new IntensityDataPropertyWidget), m_resetViewAction(new QAction(this)),
      m_comparisonController(new FitComparisonController2D(this))
{
    auto vlayout = new QVBoxLayout;
    vlayout->setMargin(0);
    vlayout->setSpacing(0);

    auto gridLayout = new QGridLayout;
    gridLayout->setMargin(0);
    gridLayout->setSpacing(0);

    gridLayout->addWidget(m_realDataPlot, 0, 0);
    gridLayout->addWidget(m_simulatedDataPlot, 0, 1);
    gridLayout->addWidget(m_relativeDiffPlot, 1, 0);
    gridLayout->addWidget(m_fitFlowWidget, 1, 1);

    vlayout->addLayout(gridLayout);
    vlayout->addWidget(m_statusLabel);

    auto hlayout = new QHBoxLayout;
    hlayout->setMargin(0);
    hlayout->setSpacing(0);
    hlayout->addLayout(vlayout);
    hlayout->addWidget(m_propertyWidget);
    setLayout(hlayout);

    m_resetViewAction->setText("Center view");
    m_resetViewAction->setIcon(QIcon(":/images/camera-metering-center.svg"));
    m_resetViewAction->setToolTip("Reset View");
    connect(m_resetViewAction, &QAction::triggered, this, &FitComparisonWidget::onResetViewAction);

    m_propertyWidget->setVisible(false);
}

FitComparisonWidget::~FitComparisonWidget() = default;

QList<QAction*> FitComparisonWidget::actionList()
{
    return QList<QAction*>() << m_resetViewAction << m_propertyWidget->actionList();
}

void FitComparisonWidget::subscribeToItem()
{
    if (!jobItem()->isValidForFitting())
        return;

    jobItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == JobItem::P_STATUS) {
                if (jobItem()->isCompleted())
                    onResetViewAction();
            }
        },
        this);

    m_comparisonController->setItem(jobItem());
    m_realDataPlot->setItem(realDataItem());
    m_simulatedDataPlot->setItem(simulatedDataItem());
    m_relativeDiffPlot->setItem(m_comparisonController->diffItem());
    m_fitFlowWidget->setItem(jobItem()->fitSuiteItem());

    m_statusLabel->reset();
    m_statusLabel->addPlot(m_realDataPlot->colorMap());
    m_statusLabel->addPlot(m_simulatedDataPlot->colorMap());
    m_statusLabel->addPlot(m_relativeDiffPlot->colorMap());

    m_propertyWidget->setItem(simulatedDataItem());
}

void FitComparisonWidget::unsubscribeFromItem()
{
    m_comparisonController->clear();
}

void FitComparisonWidget::onResetViewAction()
{
    if (auto item = realDataItem())
        item->resetView();

    m_comparisonController->resetDiffItem();
}

JobItem* FitComparisonWidget::jobItem()
{
    JobItem* jobItem = dynamic_cast<JobItem*>(currentItem());
    return jobItem;
}

IntensityDataItem* FitComparisonWidget::realDataItem()
{
    return jobItem()->realDataItem()->intensityDataItem();
}

IntensityDataItem* FitComparisonWidget::simulatedDataItem()
{
    return jobItem()->intensityDataItem();
}

IntensityDataItem* FitComparisonWidget::diffItem()
{
    return m_comparisonController->diffItem();
}
