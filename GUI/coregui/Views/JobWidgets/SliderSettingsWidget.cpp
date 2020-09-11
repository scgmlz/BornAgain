// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/JobWidgets/SliderSettingsWidget.cpp
//! @brief     Implements class SliderSettingsWidget
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Views/JobWidgets/SliderSettingsWidget.h"
#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>

SliderSettingsWidget::SliderSettingsWidget(QWidget* parent)
    : QWidget(parent), m_currentSliderRange(100.0), m_radio1(0), m_radio2(0), m_radio3(0),
      m_lockzCheckBox(0)
{
    // tuning selectors
    QString tooltip("Allows to tune sample parameters within +/- of given range \nwith the help of "
                    "the slider.");

    QLabel* label = new QLabel("Tuning:");
    label->setToolTip(tooltip);

    m_radio1 = new QRadioButton("10%");
    m_radio1->setAutoExclusive(true);
    m_radio1->setToolTip(tooltip);
    connect(m_radio1, SIGNAL(clicked(bool)), this, SLOT(rangeChanged()));

    m_radio2 = new QRadioButton("100%");
    m_radio2->setChecked(true);
    m_radio2->setAutoExclusive(true);
    m_radio2->setToolTip(tooltip);
    connect(m_radio2, SIGNAL(clicked(bool)), this, SLOT(rangeChanged()));

    m_radio3 = new QRadioButton("1000%");
    m_radio3->setAutoExclusive(true);
    m_radio3->setToolTip(tooltip);
    connect(m_radio3, SIGNAL(clicked(bool)), this, SLOT(rangeChanged()));

    // Fix z-axis
    m_lockzCheckBox = new QCheckBox("Lock-Z");
    m_lockzCheckBox->setToolTip(
        "Preserve (min, max) range of intensity axis during parameter tuning.");
    connect(m_lockzCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onLockZChanged(int)));

    QHBoxLayout* hbox = new QHBoxLayout;

    hbox->addWidget(label);
    hbox->addWidget(m_radio1);
    hbox->addWidget(m_radio2);
    hbox->addWidget(m_radio3);
    hbox->addStretch(1);
    hbox->addWidget(m_lockzCheckBox);

    setLayout(hbox);
}

void SliderSettingsWidget::rangeChanged()
{
    if (m_radio1->isChecked()) {
        m_currentSliderRange = 10.0;
    } else if (m_radio2->isChecked()) {
        m_currentSliderRange = 100.0;
    } else if (m_radio3->isChecked()) {
        m_currentSliderRange = 1000.0;
    }
    emit sliderRangeFactorChanged(m_currentSliderRange);
}

void SliderSettingsWidget::onLockZChanged(int state)
{
    if (state == Qt::Unchecked) {
        emit lockzChanged(false);
    } else if (state == Qt::Checked) {
        emit lockzChanged(true);
    }
}
