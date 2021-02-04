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
#include <QtGui>

AutomaticMultiColumnDataLoader1DProperties::AutomaticMultiColumnDataLoader1DProperties()
{
    m_ui = new Ui::AutomaticMultiColumnDataLoader1DProperties;
    m_ui->setupUi(this);

    m_typeCombos[0] = m_ui->typeCombo1;
    m_typeCombos[1] = m_ui->typeCombo2;
    m_typeCombos[2] = m_ui->typeCombo3;
    m_typeCombos[3] = m_ui->typeCombo4;

    m_unitCombos[0] = m_ui->unitCombo1;
    m_unitCombos[1] = m_ui->unitCombo2;
    m_unitCombos[2] = m_ui->unitCombo3;
    m_unitCombos[3] = m_ui->unitCombo4;

    m_factors[0] = m_ui->factorSpinBox1;
    m_factors[1] = m_ui->factorSpinBox2;
    m_factors[2] = m_ui->factorSpinBox3;
    m_factors[3] = m_ui->factorSpinBox4;

    m_widgetsOfColumns[0] << m_ui->unitLabel1 << m_ui->unitCombo1 << m_ui->factorLabel1
                          << m_ui->factorSpinBox1;
    m_widgetsOfColumns[1] << m_ui->unitLabel2 << m_ui->unitCombo2 << m_ui->factorLabel2
                          << m_ui->factorSpinBox2;
    m_widgetsOfColumns[2] << m_ui->unitLabel3 << m_ui->unitCombo3 << m_ui->factorLabel3
                          << m_ui->factorSpinBox3;
    m_widgetsOfColumns[3] << m_ui->unitLabel4 << m_ui->unitCombo4 << m_ui->factorLabel4
                          << m_ui->factorSpinBox4;

    for (int col = 0; col < 4; col++) {

        connect(m_typeCombos[col], QOverload<int>::of(&QComboBox::currentIndexChanged),
                [=]() { onTypeComboChanged(col); });

        connect(m_unitCombos[col], QOverload<int>::of(&QComboBox::currentIndexChanged),
                [=]() { emit propertiesChanged(); });

        connect(m_factors[col], QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                [=]() { emit propertiesChanged(); });
    }
}

QString AutomaticMultiColumnDataLoader1DProperties::unit(int col) const
{
    return m_unitCombos[col]->currentText();
}

double AutomaticMultiColumnDataLoader1DProperties::factor(int col) const
{
    return m_factors[col]->value();
}

void AutomaticMultiColumnDataLoader1DProperties::setType(int col, int type)
{
    m_typeCombos[col]->setCurrentIndex(type);

    const bool isIgnored = m_typeCombos[col]->currentIndex() == 4;

    for (auto w : m_widgetsOfColumns[col])
        w->setVisible(!isIgnored);
}

void AutomaticMultiColumnDataLoader1DProperties::onTypeComboChanged(int column)
{
    const bool isIgnored = m_typeCombos[column]->currentIndex() == 4;

    for (auto w : m_widgetsOfColumns[column])
        w->setVisible(!isIgnored);

    // #TODO: update available units

    emit propertiesChanged();
}
