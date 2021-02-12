//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      /GUI/coregui/DataLoaders/FormulaBasedDataLoader1D.cpp
//! @brief     Implements class FormulaBasedDataLoader1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/DataLoaders/FormulaBasedDataLoader1D.h"
#include "ui_FormulaBasedDataLoader1DProperties.h"

QString FormulaBasedDataLoader1D::name() const
{
    return "CSV file (Reflectometry - Q/R/E) formula based";
}

QString FormulaBasedDataLoader1D::persistentClassName() const
{
    return "FormulaBasedDataLoader1D";
}

QString FormulaBasedDataLoader1D::preview(const QString& filepath, QCustomPlot* plotWidget) const
{
    return "";
}

void FormulaBasedDataLoader1D::populatePropertiesWidget(QWidget* parent)
{
    if (m_propertiesWidget == nullptr) {
        m_propertiesWidget = new QWidget;
        auto ui = new Ui::FormulaBasedDataLoader1DProperties;
        ui->setupUi(m_propertiesWidget);
    }

    QHBoxLayout* l = new QHBoxLayout(parent);
    l->setContentsMargins(0, 0, 0, 0);
    parent->setLayout(l);
    l->addWidget(m_propertiesWidget);
}

void FormulaBasedDataLoader1D::initWithDefaultProperties() {}

void FormulaBasedDataLoader1D::applyProperties() {}

QByteArray FormulaBasedDataLoader1D::serialize() const
{
    return QByteArray();
}

void FormulaBasedDataLoader1D::deserialize(const QByteArray& data) {}

AbstractDataLoader* FormulaBasedDataLoader1D::clone() const
{
    auto loader = new FormulaBasedDataLoader1D();
    loader->deserialize(serialize());
    return loader;
}
