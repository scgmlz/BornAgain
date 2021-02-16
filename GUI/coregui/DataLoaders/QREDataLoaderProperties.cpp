//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/AutomaticMultiColumnDataLoader1DProperties.cpp
//! @brief     Implements class AutomaticMultiColumnDataLoader1DProperties
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/DataLoaders/QREDataLoaderProperties.h"
#include "ui_QREDataLoaderProperties.h"
#include <QCheckBox>
#include <QtGui>

QREDataLoaderProperties::QREDataLoaderProperties() : m_allowFactors(false)
{
    m_ui = new Ui::QREDataLoaderProperties;
    m_ui->setupUi(this);

    allowFactors(false);

    connect(m_ui->headerPrefixEdit, &QLineEdit::textChanged, [=]() { emit propertiesChanged(); });
    connect(m_ui->linesToSkipEdit, &QLineEdit::textChanged, [=]() { emit propertiesChanged(); });
    connect(m_ui->separatorCombo, &QComboBox::currentTextChanged,
            [=]() { emit propertiesChanged(); });

    connect(m_ui->enableErrorCheckBox, &QCheckBox::stateChanged, this,
            &QREDataLoaderProperties::onErrorEnablingChanged);

    connect(m_ui->qUnitCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=]() { emit propertiesChanged(); });

    for (int dataType = 0; dataType < 3; dataType++) {

        connect(columnSpinBox(dataType), QOverload<int>::of(&QSpinBox::valueChanged),
                [=]() { emit propertiesChanged(); });

        connect(factorSpinBox(dataType), QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                [=]() { emit propertiesChanged(); });
    }
}

void QREDataLoaderProperties::allowFactors(bool b)
{
    m_allowFactors = b;
    for (int dataType = 0; dataType < 3; dataType++) {
        factorLabel(dataType)->setVisible(b);
        factorSpinBox(dataType)->setVisible(b);
    }

    updateErrorEnabling(m_ui->enableErrorCheckBox->isChecked());
}

double QREDataLoaderProperties::factor(int dataType) const
{
    auto spinBox = factorSpinBox(dataType);
    return spinBox->isVisible() ? spinBox->value() : 1.0;
}

void QREDataLoaderProperties::updateEnabling(int dataType, bool enabled)
{
    const int lineInLayout = dataType;
    for (int col = 1; col < m_ui->gridLayout->columnCount(); col++) {
        auto layoutItem = m_ui->gridLayout->itemAtPosition(lineInLayout, col);
        if (layoutItem) {
            QWidget* w = layoutItem->widget();
            if (w) {
                const bool belongsToUnusedCombo =
                    (dataType != 0) && (col >= 5); // no unit except for Q
                w->setVisible(enabled && !belongsToUnusedCombo);
            }
        }
    }
}

void QREDataLoaderProperties::updateErrorEnabling(bool enabled)
{
    const int lineInLayout = 2;

    for (int col = 1; col < m_ui->gridLayout->columnCount(); col++) {
        auto layoutItem = m_ui->gridLayout->itemAtPosition(lineInLayout, col);
        if (layoutItem) {
            QWidget* w = layoutItem->widget();
            if (w) {
                const bool belongsToFactor = col == factorColumn || col == factorLabelColumn;
                w->setVisible(enabled && (!belongsToFactor || m_allowFactors));
            }
        }
    }
}

void QREDataLoaderProperties::onErrorEnablingChanged()
{
    const bool isEnabled = m_ui->enableErrorCheckBox->isChecked();

    updateErrorEnabling(isEnabled);

    emit propertiesChanged();
}

QSpinBox* QREDataLoaderProperties::columnSpinBox(int dataType) const
{
    const int lineInLayout = dataType;
    return dynamic_cast<QSpinBox*>(m_ui->gridLayout->itemAtPosition(lineInLayout, 2)->widget());
}

QDoubleSpinBox* QREDataLoaderProperties::factorSpinBox(int dataType) const
{
    const int lineInLayout = dataType;
    return dynamic_cast<QDoubleSpinBox*>(
        m_ui->gridLayout->itemAtPosition(lineInLayout, factorColumn)->widget());
}

QLabel* QREDataLoaderProperties::factorLabel(int dataType) const
{
    const int lineInLayout = dataType;
    return dynamic_cast<QLabel*>(
        m_ui->gridLayout->itemAtPosition(lineInLayout, factorLabelColumn)->widget());
}
