// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitActivityPanel.cpp
//! @brief     Implements class FitActivityPanel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/FitActivityPanel.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Views/FitWidgets/FitSessionManager.h"
#include "GUI/coregui/Views/FitWidgets/FitSessionWidget.h"
#include "GUI/coregui/Views/FitWidgets/RunFitControlWidget.h"
#include "GUI/coregui/Views/JobWidgets/JobMessagePanel.h"
#include "GUI/coregui/Views/JobWidgets/JobRealTimeWidget.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include <QPushButton>
#include <QVBoxLayout>

namespace
{
const bool reuse_widget = true;
}

FitActivityPanel::FitActivityPanel(JobModel* jobModel, QWidget* parent)
    : QWidget(parent), m_stackedWidget(new ItemStackPresenter<FitSessionWidget>(reuse_widget)),
      m_realTimeWidget(nullptr), m_jobMessagePanel(nullptr),
      m_fitSessionManager(new FitSessionManager(this))
{
    setWindowTitle(Constants::JobFitPanelName);
    setObjectName("FitActivityPanel");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_stackedWidget);

    setLayout(mainLayout);

    m_stackedWidget->setModel(jobModel);
}

void FitActivityPanel::setRealTimeWidget(JobRealTimeWidget* realTimeWidget)
{
    ASSERT(realTimeWidget);
    m_realTimeWidget = realTimeWidget;
}

void FitActivityPanel::setJobMessagePanel(JobMessagePanel* jobMessagePanel)
{
    m_jobMessagePanel = jobMessagePanel;
    m_fitSessionManager->setMessagePanel(m_jobMessagePanel);
}

QSize FitActivityPanel::sizeHint() const
{
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, Constants::FIT_ACTIVITY_PANEL_HEIGHT);
}

QSize FitActivityPanel::minimumSizeHint() const
{
    return QSize(80, 80);
}

void FitActivityPanel::setItem(JobItem* item)
{

    if (!isValidJobItem(item)) {
        m_jobMessagePanel->onClearLog();
        m_stackedWidget->hideWidgets();
        m_fitSessionManager->disableLogging();
        return;
    }

    m_stackedWidget->setItem(item);
    FitSessionWidget* widget = m_stackedWidget->currentWidget();
    widget->setModelTuningWidget(m_realTimeWidget->parameterTuningWidget(item));
    widget->setSessionController(m_fitSessionManager->sessionController(item));
}

bool FitActivityPanel::isValidJobItem(JobItem* item)
{
    return item ? item->isValidForFitting() : false;
}

FitSessionWidget* FitActivityPanel::currentFitSuiteWidget()
{
    return m_stackedWidget->currentWidget();
}
