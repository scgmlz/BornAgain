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

#include "GUI/coregui/Views/FitWidgets/GUIFitObserver.h"
#include "Core/Fitting/FitObjective.h"
#include "Fit/Kernel/MinimizerResult.h"
#include "Fit/Tools/MinimizerUtils.h"
#include "GUI/coregui/Views/FitWidgets/FitProgressInfo.h"
#include "GUI/coregui/utils/GUIHelpers.h"

GUIFitObserver::GUIFitObserver(QObject* parent)
    : QObject(parent), m_block_update_plots(false), m_update_interval(1)
{
}

GUIFitObserver::~GUIFitObserver() {}

void GUIFitObserver::update(const FitObjective* subject)
{
    if (!is_suitable_iteration(subject))
        return;

    std::unique_lock<std::mutex> lock(m_update_plot_mutex);
    if (m_block_update_plots && !is_obligatory_iteration(subject))
        return; // plotting still works, will skip iteration

    if (m_block_update_plots)
        m_on_finish_notifier.wait(lock, [this]() { return m_block_update_plots; });

    FitProgressInfo info;
    info.m_chi2 = subject->iterationInfo().chi2();
    info.m_iteration_count = static_cast<int>(subject->iterationInfo().iterationCount());
    info.m_values = subject->iterationInfo().parameters().values();

    if (subject->isCompleted())
        info.m_log_info = subject->minimizerResult().toString();

    auto data = subject->dataPair().simulationResult().data();
    info.m_sim_values = data->getRawDataVector();

    m_iteration_info = info;
    emit updateReady();
}

//! Returns true if data could be plotted, when there are resources for it.

bool GUIFitObserver::is_suitable_iteration(const FitObjective* fitSuite) const
{
    if (fitSuite->isInterrupted())
        return false;

    int n_iter = static_cast<int>(fitSuite->iterationInfo().iterationCount());
    return fitSuite->isFirstIteration() || n_iter % m_update_interval == 0
           || fitSuite->isCompleted();
}

//! Returns true if given iteration should be obligary plotted.

bool GUIFitObserver::is_obligatory_iteration(const FitObjective* fitSuite) const
{
    return fitSuite->isCompleted();
}

void GUIFitObserver::setInterval(int val)
{
    m_update_interval = val;
}

//! Informs observer that FitSuiteWidget has finished plotting and is ready for next plot

void GUIFitObserver::finishedPlotting()
{
    std::unique_lock<std::mutex> lock(m_update_plot_mutex);
    m_block_update_plots = false;
    lock.unlock();
    m_on_finish_notifier.notify_one();
}

FitProgressInfo GUIFitObserver::progressInfo()
{
    std::unique_lock<std::mutex> lock(m_update_plot_mutex);
    m_block_update_plots = true;
    return m_iteration_info;
}
