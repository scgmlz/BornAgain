// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSessionController.cpp
//! @brief     Implements class FitSessionController
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/FitSessionController.h"
#include "GUI/coregui/Models/FitParameterItems.h"
#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Models/IntensityDataItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Views/FitWidgets/FitLog.h"
#include "GUI/coregui/Views/FitWidgets/FitObjectiveBuilder.h"
#include "GUI/coregui/Views/FitWidgets/FitProgressInfo.h"
#include "GUI/coregui/Views/FitWidgets/FitWorkerLauncher.h"
#include "GUI/coregui/Views/FitWidgets/GUIFitObserver.h"
#include "GUI/coregui/utils/GUIHelpers.h"

namespace
{
const bool use_fit_objective = true;
}

FitSessionController::FitSessionController(QObject* parent)
    : QObject(parent), m_jobItem(nullptr), m_runFitManager(new FitWorkerLauncher(this)),
      m_observer(new GUIFitObserver), m_fitlog(new FitLog), m_block_progress_update(false)
{
    connect(m_observer.get(), &GUIFitObserver::updateReady, this,
            &FitSessionController::onObserverUpdate);

    connect(m_runFitManager, &FitWorkerLauncher::fittingStarted, this,
            &FitSessionController::onFittingStarted);
    connect(m_runFitManager, &FitWorkerLauncher::fittingFinished, this,
            &FitSessionController::onFittingFinished);
    connect(m_runFitManager, &FitWorkerLauncher::fittingError, this,
            &FitSessionController::onFittingError);
}

FitSessionController::~FitSessionController() = default;

void FitSessionController::setItem(JobItem* item)
{
    if (m_jobItem && m_jobItem != item)
        throw GUIHelpers::Error("FitSuiteManager::setItem() -> Item was already set.");

    m_jobItem = item;
    ASSERT(m_jobItem);

    // no need to unsubscribe from jobItem on jobItem destroy. FitSessionManager deletes
    // controller right after the jobItem.

    // Propagates update interval from FitSuiteItem to fit observer.
    m_jobItem->fitSuiteItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == FitSuiteItem::P_UPDATE_INTERVAL) {
                m_observer->setInterval(m_jobItem->fitSuiteItem()
                                            ->getItemValue(FitSuiteItem::P_UPDATE_INTERVAL)
                                            .toInt());
            }
        },
        this);
}

void FitSessionController::onStartFittingRequest()
{
    if (!m_jobItem)
        return;

    try {
        m_objectiveBuilder.reset(new FitObjectiveBuilder(m_jobItem));
        m_observer->setInterval(
            m_jobItem->fitSuiteItem()->getItemValue(FitSuiteItem::P_UPDATE_INTERVAL).toInt());
        m_objectiveBuilder->attachObserver(m_observer);
        m_observer->finishedPlotting();
        m_runFitManager->runFitting(m_objectiveBuilder);

    } catch (std::exception& e) {
        m_jobItem->setStatus("Failed");
        m_fitlog->append(e.what(), FitLogFlags::ERROR);
        emit fittingError(QString::fromStdString(e.what()));
    }
}

FitLog* FitSessionController::fitLog()
{
    return m_fitlog.get();
}

void FitSessionController::onStopFittingRequest()
{
    m_runFitManager->interruptFitting();
}

void FitSessionController::onObserverUpdate()
{
    auto progressInfo = m_observer->progressInfo();
    m_jobItem->dataItem()->setRawDataVector(progressInfo.simValues());

    updateIterationCount(progressInfo);

    if (!use_fit_objective)
        updateFitParameterValues(progressInfo);

    updateLog(progressInfo);

    if (!progressInfo.logInfo().empty())
        m_fitlog->append(progressInfo.logInfo(), FitLogFlags::DEFAULT);

    m_observer->finishedPlotting();
}

void FitSessionController::onFittingStarted()
{
    m_fitlog->clearLog();

    m_jobItem->setStatus("Fitting");
    m_jobItem->setProgress(0);
    m_jobItem->setBeginTime(GUIHelpers::currentDateTime());
    m_jobItem->setEndTime(QString());
    m_jobItem->setDuration(0);

    emit fittingStarted();
}

void FitSessionController::onFittingFinished()
{
    if (m_jobItem->getStatus() != "Failed")
        m_jobItem->setStatus("Completed");
    m_jobItem->setEndTime(GUIHelpers::currentDateTime());
    m_jobItem->setProgress(100);
    m_jobItem->setDuration(m_runFitManager->getDuration());

    if (m_jobItem->isCompleted())
        m_fitlog->append("Done", FitLogFlags::SUCCESS);

    emit fittingFinished();
}

void FitSessionController::onFittingError(const QString& text)
{
    QString message;
    message.append("Current settings cause fitting failure.\n\n");
    message.append(text);
    m_fitlog->append(message.toStdString(), FitLogFlags::ERROR);

    emit fittingError(message);
}

void FitSessionController::updateIterationCount(const FitProgressInfo& info)
{
    FitSuiteItem* fitSuiteItem = m_jobItem->fitSuiteItem();
    // FIXME FitFlowWidget updates chi2 and n_iteration on P_ITERATION_COUNT change
    // The order of two lines below is important
    fitSuiteItem->setItemValue(FitSuiteItem::P_CHI2, info.chi2());
    fitSuiteItem->setItemValue(FitSuiteItem::P_ITERATION_COUNT, info.iterationCount());
}

void FitSessionController::updateFitParameterValues(const FitProgressInfo& info)
{
    QVector<double> values = GUIHelpers::fromStdVector(info.parValues());
    FitParameterContainerItem* fitParContainer = m_jobItem->fitParameterContainerItem();
    fitParContainer->setValuesInParameterContainer(values, m_jobItem->parameterContainerItem());
}

void FitSessionController::updateLog(const FitProgressInfo& info)
{
    QString message = QString("NCalls:%1 chi2:%2 \n").arg(info.iterationCount()).arg(info.chi2());
    FitParameterContainerItem* fitParContainer = m_jobItem->fitParameterContainerItem();
    int index(0);
    QVector<double> values = GUIHelpers::fromStdVector(info.parValues());
    for (auto item : fitParContainer->getItems(FitParameterContainerItem::T_FIT_PARAMETERS)) {
        if (item->getItems(FitParameterItem::T_LINK).size() == 0)
            continue;
        QString parinfo = QString("      %1 %2\n").arg(item->displayName()).arg(values[index++]);
        message.append(parinfo);
    }
    m_fitlog->append(message.toStdString(), FitLogFlags::DEFAULT);
}
