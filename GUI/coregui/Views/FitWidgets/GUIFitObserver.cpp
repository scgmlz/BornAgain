// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/GUIFitObserver.cpp
//! @brief     Implements class GUIFitObserver
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUIFitObserver.h"
#include "FitParameterSet.h"
#include "FitProgressInfo.h"
#include "FitSuite.h"
#include "GUIHelpers.h"
#include "MinimizerUtils.h"

GUIFitObserver::GUIFitObserver(QObject* parent)
    : QObject(parent)
    , IFitObserver(1)
    , m_block_update_plots(false)
    , m_update_interval(1)
{
}

GUIFitObserver::~GUIFitObserver()
{
}

void GUIFitObserver::update(FitSuite* subject)
{
    if (!is_suitable_iteration(subject))
        return;

    std::unique_lock<std::mutex> lock(m_update_plot_mutex);
    if (m_block_update_plots && !is_obligatory_iteration(subject))
        return; // plotting still works, will skip iteration

    if (m_block_update_plots)
        m_on_finish_notifier.wait(lock, [this]() { return m_block_update_plots; });

    if (subject->isFirstIteration())
        emit logInfoUpdate(QString::fromStdString(subject->setupToString()));

    FitProgressInfo info;
    info.m_chi2 = subject->getChi2();
    info.m_iteration_count = (int)subject->numberOfIterations();
    info.m_values = GUIHelpers::fromStdVector(subject->fitParameters()->values());

    emit progressInfoUpdate(info);

    if (subject->isLastIteration())
        emit logInfoUpdate(reportToString(subject));

    m_simData.reset(subject->simulationResult().data());
    emit plotsUpdate();

}

//! Returns true if data could be plotted, when there are resources for it.

bool GUIFitObserver::is_suitable_iteration(FitSuite* fitSuite)
{
    if (fitSuite->isInterrupted())
        return false;

    int n_iter = static_cast<int>(fitSuite->numberOfIterations());
    return n_iter == fitSuite->isFirstIteration() ||
           n_iter % m_update_interval == 0 ||
           fitSuite->isLastIteration();
}

//! Returns true if given iteration should be obligary plotted.

bool GUIFitObserver::is_obligatory_iteration(FitSuite* fitSuite)
{
    return fitSuite->isLastIteration();
}

void GUIFitObserver::setInterval(int val)
{
    m_update_interval = val;
}

//! Return string representing results of the minimization.

QString GUIFitObserver::reportToString(FitSuite* fitSuite)
{
    QString result = QString::fromStdString(MinimizerUtils::sectionString("Fit parameter setup"));
    result += QString::fromStdString(fitSuite->setupToString());
    result += QString::fromStdString(fitSuite->reportResults());
    return result;
}

//! Informs observer that FitSuiteWidget has finished plotting and is ready for next plot

void GUIFitObserver::finishedPlotting()
{
    std::unique_lock<std::mutex> lock(m_update_plot_mutex);
    m_block_update_plots = false;
    lock.unlock();
    m_on_finish_notifier.notify_one();
}

//! Returns data to the user and blocks possible data update.

const OutputData<double>* GUIFitObserver::simulationData()
{
    std::unique_lock<std::mutex> lock(m_update_plot_mutex);
    m_block_update_plots = true;
    return m_simData.get();
}
