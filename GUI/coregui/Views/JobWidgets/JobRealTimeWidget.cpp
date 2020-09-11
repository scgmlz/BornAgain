// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/JobRealTimeWidget.cpp
//! @brief     Implements class JobRealTimeWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/JobRealTimeWidget.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Models/JobModel.h"
#include "GUI/coregui/Views/JobWidgets/ParameterTuningWidget.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include <QVBoxLayout>

namespace
{
const bool reuse_widget = true;
}

JobRealTimeWidget::JobRealTimeWidget(JobModel* jobModel, QWidget* parent)
    : QWidget(parent), m_stackedWidget(new ItemStackPresenter<ParameterTuningWidget>(reuse_widget))
{
    setWindowTitle(Constants::JobRealTimeWidgetName);
    setObjectName("JobRealTimeWidget");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    auto mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(m_stackedWidget);
    setLayout(mainLayout);

    m_stackedWidget->setModel(jobModel);
}

ParameterTuningWidget* JobRealTimeWidget::parameterTuningWidget(JobItem* jobItem)
{
    return m_stackedWidget->itemWidget(jobItem);
}

QSize JobRealTimeWidget::sizeHint() const
{
    return QSize(Constants::REALTIME_WIDGET_WIDTH_HINT, 480);
}

QSize JobRealTimeWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

void JobRealTimeWidget::setItem(JobItem* jobItem)
{
    if (!isValidJobItem(jobItem)) {
        m_stackedWidget->hideWidgets();
        return;
    }

    m_stackedWidget->setItem(jobItem);
}

//! Returns true if JobItem is valid for real time simulation.

bool JobRealTimeWidget::isValidJobItem(JobItem* item)
{
    if (item && (item->isCompleted() || item->isCanceled() || item->isFailed()))
        return true;

    return false;
}
