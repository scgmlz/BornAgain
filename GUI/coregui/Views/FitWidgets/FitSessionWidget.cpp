// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/FitSessionWidget.cpp
//! @brief     Implements class FitSessionWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/FitSessionWidget.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Views/FitWidgets/FitParameterWidget.h"
#include "GUI/coregui/Views/FitWidgets/FitResultsWidget.h"
#include "GUI/coregui/Views/FitWidgets/FitSessionController.h"
#include "GUI/coregui/Views/FitWidgets/MinimizerSettingsWidget.h"
#include "GUI/coregui/Views/FitWidgets/RunFitControlWidget.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include <QTabWidget>
#include <QVBoxLayout>

FitSessionWidget::FitSessionWidget(QWidget* parent)
    : QWidget(parent), m_tabWidget(new QTabWidget), m_controlWidget(new RunFitControlWidget),
      m_fitParametersWidget(new FitParameterWidget),
      m_minimizerSettingsWidget(new MinimizerSettingsWidget)
      // , m_fitResultsWidget(new FitResultsWidget)
      ,
      m_fitResultsWidget(nullptr) // temporary replacement to fix a memory leak
      ,
      m_sessionController(nullptr)
{
    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_tabWidget->addTab(m_fitParametersWidget, "Fit Parameters");
    m_tabWidget->addTab(m_minimizerSettingsWidget, "Minimizer");
    // m_tabWidget->addTab(m_fitResultsWidget, "Fit Results");

    layout->addWidget(m_tabWidget);
    layout->addWidget(m_controlWidget);

    setLayout(layout);
}

void FitSessionWidget::setItem(JobItem* jobItem)
{
    ASSERT(jobItem);
    m_fitParametersWidget->setItem(jobItem);
    m_minimizerSettingsWidget->setItem(jobItem);
    m_controlWidget->setItem(jobItem);
}

void FitSessionWidget::setModelTuningWidget(ParameterTuningWidget* tuningWidget)
{
    ASSERT(m_fitParametersWidget);
    ASSERT(tuningWidget);
    m_fitParametersWidget->setParameterTuningWidget(tuningWidget);
}

void FitSessionWidget::setSessionController(FitSessionController* sessionController)
{
    if (m_sessionController) {
        disconnect(m_sessionController, 0, this, 0);
        disconnect(m_controlWidget, 0, m_sessionController, 0);
    }

    m_sessionController = sessionController;

    if (m_sessionController) {
        connect(m_sessionController, &FitSessionController::fittingError, this,
                &FitSessionWidget::onFittingError);
        connect(m_sessionController, &QObject::destroyed,
                [this] { m_sessionController = nullptr; });
        connect(m_controlWidget, &RunFitControlWidget::startFittingPushed, m_sessionController,
                &FitSessionController::onStartFittingRequest);
        connect(m_controlWidget, &RunFitControlWidget::stopFittingPushed, m_sessionController,
                &FitSessionController::onStopFittingRequest);
    }
}

QSize FitSessionWidget::sizeHint() const
{
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, Constants::FIT_SUITE_WIDGET_HEIGHT);
}

QSize FitSessionWidget::minimumSizeHint() const
{
    return QSize(25, 25);
}

void FitSessionWidget::onFittingError(const QString& text)
{
    m_controlWidget->onFittingError(text);
}
