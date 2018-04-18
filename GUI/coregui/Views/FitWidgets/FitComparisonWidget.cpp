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

#include "FitComparisonWidget.h"
#include "AxesItems.h"
#include "ColorMap.h"
#include "ColorMapCanvas.h"
#include "PlotStatusLabel.h"
#include "FitFlowWidget.h"
#include "IntensityDataFunctions.h"
#include "IntensityDataItem.h"
#include "JobItem.h"
#include "RealDataItem.h"
#include "SessionModel.h"
#include "FitSuiteItem.h"
#include "PropertyRepeater.h"
#include "IntensityDataPropertyWidget.h"
#include "AxesItems.h"
#include "FitComparisonController.h"
#include "JobItemUtils.h"
#include <QAction>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

namespace {
const double relative_diff_min = 1e-05;
const double relative_diff_max = 1;
}

FitComparisonWidget::FitComparisonWidget(QWidget *parent)
    : SessionItemWidget(parent)
    , m_realDataPlot(new ColorMapCanvas)
    , m_simulatedDataPlot(new ColorMapCanvas)
    , m_relativeDiffPlot(new ColorMapCanvas)
    , m_fitFlowWidget(new FitFlowWidget)
    , m_statusLabel(new PlotStatusLabel(0, this))
    , m_propertyWidget(new IntensityDataPropertyWidget)
    , m_resetViewAction(new QAction(this))
    , m_comparisonController(new FitComparisonController(this))
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

    m_resetViewAction->setText("Reset View");
    m_resetViewAction->setIcon(QIcon(":/images/toolbar16light_refresh.svg"));
    m_resetViewAction->setToolTip("Reset View");
    connect(m_resetViewAction, &QAction::triggered, this, &FitComparisonWidget::onResetViewAction);

    m_relativeDiffPlot->setItem(m_comparisonController->diffItem());
    m_propertyWidget->setVisible(false);
}

FitComparisonWidget::~FitComparisonWidget()
{
    unsubscribeFromChildren();
}


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

    if (auto simItem = simulatedDataItem()) {
        simItem->mapper()->setOnValueChange([this]() { calculateRelativeDifference(); }, this);
    }

    calculateRelativeDifference();

    m_realDataPlot->setItem(realDataItem());
    m_simulatedDataPlot->setItem(simulatedDataItem());
    m_fitFlowWidget->setItem(jobItem()->fitSuiteItem());

    m_statusLabel->reset();
    m_statusLabel->addPlot(m_realDataPlot->colorMap());
    m_statusLabel->addPlot(m_simulatedDataPlot->colorMap());
    m_statusLabel->addPlot(m_relativeDiffPlot->colorMap());

    m_comparisonController->setItems(realDataItem(), simulatedDataItem());

    if (auto diff_item = diffItem()) {
        diff_item->mapper()->setOnPropertyChange([this](const QString& name)
        {
            if (name == DataItem::P_AXES_UNITS) {
                JobItemUtils::updateDataAxes(diffItem(), jobItem()->instrumentItem());
            }
        }, this);
    }

    m_propertyWidget->setItem(simulatedDataItem());
}

void FitComparisonWidget::unsubscribeFromItem()
{
    if (!currentItem())
        return;

    unsubscribeFromChildren();

    m_comparisonController->clear();
}

void FitComparisonWidget::onResetViewAction()
{
    m_comparisonController->setActive(false);

    if (auto item = realDataItem())
        item->resetView();

    if (auto item = simulatedDataItem())
        item->resetView();

    if (diffItem()) {
        diffItem()->resetView();
        diffItem()->setLowerAndUpperZ(relative_diff_min, relative_diff_max);
    }

    m_comparisonController->setActive(true);
}

void FitComparisonWidget::calculateRelativeDifference()
{
    if (!simulatedDataItem()->getOutputData()) // job failed
        return;

    Q_ASSERT(realDataItem());
    Q_ASSERT(simulatedDataItem());
    Q_ASSERT(diffItem());

    diffItem()->setOutputData(IntensityDataFunctions::createRelativeDifferenceData(
        *simulatedDataItem()->getOutputData(), *realDataItem()->getOutputData()).release());

    diffItem()->xAxisItem()->setItemValue(BasicAxisItem::P_TITLE, simulatedDataItem()->getXaxisTitle());
    diffItem()->yAxisItem()->setItemValue(BasicAxisItem::P_TITLE, simulatedDataItem()->getYaxisTitle());
    diffItem()->setLowerAndUpperZ(relative_diff_min, relative_diff_max);
    diffItem()->setAxesRangeToData();

}

void FitComparisonWidget::unsubscribeFromChildren()
{
    if (jobItem() && simulatedDataItem())
        simulatedDataItem()->mapper()->unsubscribe(this);

    if (diffItem())
        diffItem()->mapper()->unsubscribe(this);
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
