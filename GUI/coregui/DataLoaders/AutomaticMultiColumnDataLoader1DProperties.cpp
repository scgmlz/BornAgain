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

#include "GUI/coregui/DataLoaders/AutomaticMultiColumnDataLoader1DProperties.h"
#include "ui_AutomaticMultiColumnDataLoader1DProperties.h"
#include <QCheckBox>
#include <QtGui>

AutomaticMultiColumnDataLoader1DProperties::AutomaticMultiColumnDataLoader1DProperties()
{
    m_ui = new Ui::AutomaticMultiColumnDataLoader1DProperties;
    m_ui->setupUi(this);

    connect(m_ui->headerPrefixEdit, &QLineEdit::textChanged, [=]() { emit propertiesChanged(); });
    connect(m_ui->linesToSkipEdit, &QLineEdit::textChanged, [=]() { emit propertiesChanged(); });
    connect(m_ui->separatorCombo, &QComboBox::currentTextChanged,
            [=]() { emit propertiesChanged(); });

    for (int dataType = 0; dataType < 3; dataType++) {

        connect(enablingCheckBox(dataType), &QCheckBox::stateChanged,
                [=](int state) { onEnablingChanged(dataType); });

        connect(unitCombo(dataType), QOverload<int>::of(&QComboBox::currentIndexChanged),
                [=]() { emit propertiesChanged(); });

        connect(columnSpinBox(dataType), QOverload<int>::of(&QSpinBox::valueChanged),
                [=]() { emit propertiesChanged(); });

        connect(factorSpinBox(dataType), QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                [=]() { emit propertiesChanged(); });
    }
}

QString AutomaticMultiColumnDataLoader1DProperties::unit(int dataType) const
{
    return unitCombo(dataType)->currentText();
}

double AutomaticMultiColumnDataLoader1DProperties::factor(int dataType) const
{
    return factorSpinBox(dataType)->value();
}

void AutomaticMultiColumnDataLoader1DProperties::setDataType(int dataType, bool enabled, int column,
                                                             const QString& unit, double factor)
{
    enablingCheckBox(dataType)->setChecked(enabled);
    updateEnabling(dataType, enabled);

    columnSpinBox(dataType)->setValue(column + 1); // # view is 1-based
    unitCombo(dataType)->setCurrentText(unit);
    factorSpinBox(dataType)->setValue(factor);
}

void AutomaticMultiColumnDataLoader1DProperties::updateEnabling(int dataType, bool enabled)
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

void AutomaticMultiColumnDataLoader1DProperties::onEnablingChanged(int dataType)
{
    const bool isEnabled = enablingCheckBox(dataType)->isChecked();
    if (dataType <= 1 && !isEnabled) { // no uncheck of Q/R

        QTimer::singleShot(0, [=]() { enablingCheckBox(dataType)->setChecked(true); });
        return;
    }

    updateEnabling(dataType, isEnabled);

    emit propertiesChanged();
}

QCheckBox* AutomaticMultiColumnDataLoader1DProperties::enablingCheckBox(int dataType) const
{
    const int lineInLayout = dataType;
    return dynamic_cast<QCheckBox*>(m_ui->gridLayout->itemAtPosition(lineInLayout, 0)->widget());
}

QComboBox* AutomaticMultiColumnDataLoader1DProperties::unitCombo(int dataType) const
{
    const int lineInLayout = dataType;
    return dynamic_cast<QComboBox*>(m_ui->gridLayout->itemAtPosition(lineInLayout, 6)->widget());
}

QSpinBox* AutomaticMultiColumnDataLoader1DProperties::columnSpinBox(int dataType) const
{
    const int lineInLayout = dataType;
    return dynamic_cast<QSpinBox*>(m_ui->gridLayout->itemAtPosition(lineInLayout, 2)->widget());
}

QDoubleSpinBox* AutomaticMultiColumnDataLoader1DProperties::factorSpinBox(int dataType) const
{
    const int lineInLayout = dataType;
    return dynamic_cast<QDoubleSpinBox*>(
        m_ui->gridLayout->itemAtPosition(lineInLayout, 4)->widget());
}
