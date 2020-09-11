// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/FitWidgets/RunFitControlWidget.cpp
//! @brief     Implements class RunFitControlWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/FitWidgets/RunFitControlWidget.h"
#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Models/JobItem.h"
#include "GUI/coregui/Views/InfoWidgets/WarningSign.h"
#include "GUI/coregui/Views/SampleDesigner/DesignerHelper.h"
#include "GUI/coregui/mainwindow/mainwindow_constants.h"
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>

namespace
{
const int default_interval = 10;
const std::vector<int> slider_to_interval = {1,  2,  3,  4,   5,   10,  15,  20,
                                             25, 30, 50, 100, 200, 500, 1000};
const QString slider_tooltip = "Updates fit progress every Nth iteration";
} // namespace

RunFitControlWidget::RunFitControlWidget(QWidget* parent)
    : SessionItemWidget(parent), m_startButton(new QPushButton), m_stopButton(new QPushButton),
      m_intervalSlider(new QSlider), m_updateIntervalLabel(new QLabel),
      m_iterationsCountLabel(new QLabel), m_warningSign(new WarningSign(this))
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setFixedHeight(Constants::RUN_FIT_CONTROL_WIDGET_HEIGHT);

    m_startButton->setText("Run");
    m_startButton->setToolTip("Run fitting");
    m_startButton->setMaximumWidth(80);

    m_stopButton->setText("Stop");
    m_stopButton->setToolTip("Interrupt fitting");
    m_stopButton->setMaximumWidth(80);

    m_intervalSlider->setToolTip(slider_tooltip);
    m_intervalSlider->setOrientation(Qt::Horizontal);
    m_intervalSlider->setRange(0, static_cast<int>(slider_to_interval.size()) - 1);
    m_intervalSlider->setMaximumWidth(120);
    m_intervalSlider->setMinimumWidth(120);
    m_intervalSlider->setFocusPolicy(Qt::NoFocus);
    m_intervalSlider->setValue(5);

    QFont font("Monospace", DesignerHelper::getLabelFontSize(), QFont::Normal);
    font.setPointSize(DesignerHelper::getPortFontSize());
    m_updateIntervalLabel->setToolTip(slider_tooltip);
    m_updateIntervalLabel->setFont(font);
    m_updateIntervalLabel->setText(QString::number(sliderUpdateInterval()));

    auto layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->addWidget(m_startButton);
    layout->addSpacing(5);
    layout->addWidget(m_stopButton);
    layout->addSpacing(5);
    layout->addWidget(m_intervalSlider);
    layout->addSpacing(2);
    layout->addWidget(m_updateIntervalLabel);
    layout->addSpacing(5);
    layout->addStretch();
    layout->addWidget(m_iterationsCountLabel);
    setLayout(layout);

    connect(m_startButton, &QPushButton::clicked, [&]() { startFittingPushed(); });
    connect(m_stopButton, &QPushButton::clicked, this, [&]() { stopFittingPushed(); });
    connect(m_intervalSlider, &QSlider::valueChanged, this,
            &RunFitControlWidget::onSliderValueChanged);

    setEnabled(false);
}

RunFitControlWidget::~RunFitControlWidget()
{
    unsubscribeFromChildren();
}

void RunFitControlWidget::onFittingError(const QString& what)
{
    m_warningSign->clear();
    m_iterationsCountLabel->setText("");
    m_warningSign->setWarningMessage(what);
}

void RunFitControlWidget::onSliderValueChanged(int value)
{
    int interval = sliderValueToUpdateInterval(value);
    m_updateIntervalLabel->setText(QString::number(interval));
    if (fitSuiteItem())
        fitSuiteItem()->setItemValue(FitSuiteItem::P_UPDATE_INTERVAL, interval);
}

void RunFitControlWidget::onFitSuitePropertyChange(const QString& name)
{
    if (name == FitSuiteItem::P_ITERATION_COUNT) {
        int niter = fitSuiteItem()->getItemValue(FitSuiteItem::P_ITERATION_COUNT).toInt();
        m_iterationsCountLabel->setText(QString::number(niter));
    }
}

void RunFitControlWidget::subscribeToItem()
{
    updateControlElements();

    fitSuiteItem()->setItemValue(FitSuiteItem::P_UPDATE_INTERVAL, sliderUpdateInterval());

    fitSuiteItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) { onFitSuitePropertyChange(name); }, this);

    onFitSuitePropertyChange(FitSuiteItem::P_ITERATION_COUNT);

    jobItem()->mapper()->setOnPropertyChange(
        [this](const QString& name) {
            if (name == JobItem::P_STATUS)
                updateControlElements();
        },
        this);
}

void RunFitControlWidget::unsubscribeFromItem()
{
    setEnabled(false);
    unsubscribeFromChildren();
}

int RunFitControlWidget::sliderUpdateInterval()
{
    return sliderValueToUpdateInterval(m_intervalSlider->value());
}

//! converts slider value (1-15) to update interval to be propagated to FitSuiteWidget

int RunFitControlWidget::sliderValueToUpdateInterval(int value)
{
    size_t svalue = static_cast<size_t>(value);
    return svalue < slider_to_interval.size() ? slider_to_interval[svalue] : default_interval;
}

//! Updates button "enabled" status and warning status depending on current job conditions.

void RunFitControlWidget::updateControlElements()
{
    setEnabled(isValidJobItem());

    if (jobItem()->getStatus() == "Fitting") {
        m_startButton->setEnabled(false);
        m_stopButton->setEnabled(true);
        m_warningSign->clear();
    } else {
        m_startButton->setEnabled(true);
        m_stopButton->setEnabled(false);
    }
}

JobItem* RunFitControlWidget::jobItem()
{
    return dynamic_cast<JobItem*>(currentItem());
}

FitSuiteItem* RunFitControlWidget::fitSuiteItem()
{
    return jobItem() ? jobItem()->fitSuiteItem() : nullptr;
}

bool RunFitControlWidget::isValidJobItem()
{
    return jobItem() ? jobItem()->isValidForFitting() : false;
}

void RunFitControlWidget::unsubscribeFromChildren()
{
    if (fitSuiteItem())
        fitSuiteItem()->mapper()->unsubscribe(this);
}
