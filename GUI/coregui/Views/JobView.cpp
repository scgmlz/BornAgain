// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobView.cpp
//! @brief     Implements class JobView
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobView.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Views/JobWidgets/JobOutputDataWidget.h"
#include "GUI/coregui/Views/JobWidgets/JobProgressAssistant.h"
#include "GUI/coregui/Views/JobWidgets/JobSelectorWidget.h"
#include "GUI/coregui/Views/JobWidgets/JobViewDocks.h"
#include "GUI/coregui/Views/JobWidgets/JobViewFlags.h"
#include "GUI/coregui/Views/JobWidgets/JobViewStatusBar.h"
#include "GUI/coregui/mainwindow/mainwindow.h"
#include <QMenu>

JobView::JobView(MainWindow* mainWindow)
    : m_docks(new JobViewDocks(this)), m_statusBar(new JobViewStatusBar(mainWindow)),
      m_progressAssistant(new JobProgressAssistant(mainWindow)), m_currentItem(nullptr),
      m_mainWindow(mainWindow)
{
    setObjectName("JobView");
    m_docks->initViews(mainWindow->jobModel());

    connectSignals();
}

void JobView::onFocusRequest(JobItem* jobItem)
{
    if (jobItem->runInBackground())
        return;

    if (jobItem != m_docks->jobSelector()->currentJobItem()) {
        m_docks->jobSelector()->makeJobItemSelected(jobItem);
        setAppropriateActivityForJob(jobItem);
    }

    emit focusRequest(MainWindow::JOB);
}

//! Sets docks visibility in accordance with required activity.

void JobView::setActivity(int activity)
{
    m_docks->setActivity(activity);
    emit activityChanged(activity);
}

//! Creates global dock menu at cursor position.

void JobView::onDockMenuRequest()
{
    std::unique_ptr<QMenu> menu(createPopupMenu());
    menu->exec(QCursor::pos());
}

//! Propagates change in JobItem's selection down into main widgets.

void JobView::onSelectionChanged(JobItem* jobItem)
{
    m_docks->setItem(jobItem);
}

void JobView::showEvent(QShowEvent* event)
{
    if (isVisible())
        m_statusBar->show();

    Manhattan::FancyMainWindow::showEvent(event);
}

void JobView::hideEvent(QHideEvent* event)
{
    if (isHidden())
        m_statusBar->hide();

    Manhattan::FancyMainWindow::hideEvent(event);
}

void JobView::connectSignals()
{
    connectActivityRelated();
    connectLayoutRelated();
    connectJobRelated();
}

//! Connects signal related to activity change.

void JobView::connectActivityRelated()
{
    // Change activity requests: JobViewStatusBar -> this
    connect(m_statusBar, &JobViewStatusBar::changeActivityRequest, this, &JobView::setActivity);

    // Activity was changed: this -> JobViewStatusBar
    connect(this, &JobView::activityChanged, m_statusBar, &JobViewStatusBar::onActivityChanged);

    // Activity was changed: this -> JobOutputDataWidget
    connect(this, &JobView::activityChanged, m_docks->jobOutputDataWidget(),
            &JobOutputDataWidget::onActivityChanged);
}

//! Connects signals related to dock layout.

void JobView::connectLayoutRelated()
{
    connect(this, &JobView::resetLayout, m_docks, &JobViewDocks::onResetLayout);

    // Toggling of JobSelector request: JobViewStatusBar -> this
    connect(m_statusBar, &JobViewStatusBar::toggleJobSelectorRequest, m_docks,
            &JobViewDocks::onToggleJobSelector);

    // Dock menu request: JobViewStatusBar -> this
    connect(m_statusBar, &JobViewStatusBar::dockMenuRequest, this, &JobView::onDockMenuRequest);
}

//! Connects signals related to JobItem

void JobView::connectJobRelated()
{
    // Focus request: JobModel -> this
    connect(m_mainWindow->jobModel(), &JobModel::focusRequest, this, &JobView::onFocusRequest);

    // JobItem selection: JobSelectorWidget -> this
    connect(m_docks->jobSelector(), &JobSelectorWidget::selectionChanged, this,
            &JobView::onSelectionChanged);
}

//! Sets appropriate activity for new JobItem

void JobView::setAppropriateActivityForJob(JobItem* jobItem)
{
    if (!jobItem)
        return;

    if (jobItem->isValidForFitting())
        setActivity(JobViewFlags::FITTING_ACTIVITY);
}
