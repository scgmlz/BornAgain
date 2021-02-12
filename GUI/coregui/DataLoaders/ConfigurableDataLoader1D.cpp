//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/ConfigurableDataLoader1D.cpp
//! @brief     Implements class ConfigurableDataLoader1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/DataLoaders/ConfigurableDataLoader1D.h"
#include <QString>
#include <QVector>

#include "ui_ConfigurableDataLoaderProperties.h"

QString ConfigurableDataLoader1D::name() const
{
    return "Configurable 1D import";
}

QString ConfigurableDataLoader1D::info() const
{
    return "";
}

QString ConfigurableDataLoader1D::persistentClassName() const
{
    return "ConfigurableDataLoader1D";
}

QString ConfigurableDataLoader1D::preview(const QString& filepath, QCustomPlot* plotWidget) const
{
    return "TODO: implement ConfigurableDataLoader1D::preview";
}

void ConfigurableDataLoader1D::populatePropertiesWidget(QWidget* parent)
{
    Ui::ConfigurableDataLoaderProperties ui;
    QWidget* w = new QWidget;
    ui.setupUi(w);

    QHBoxLayout* l = new QHBoxLayout(parent);
    parent->setLayout(l);
    l->addWidget(w);

    ui.ignoreStartingEdit->setText(m_header_prefix);

    QObject::connect(ui.ignoreStartingEdit, &QLineEdit::textChanged,
                     [this](const QString& newText) {
                         m_header_prefix = newText;
                         emit propertiesChanged();
                     });
}

QByteArray ConfigurableDataLoader1D::serialize() const
{
    QByteArray a;
    QDataStream s(&a, QIODevice::WriteOnly);
    s << m_header_prefix;
    return a;
}

void ConfigurableDataLoader1D::deserialize(const QByteArray& data)
{
    QDataStream s(data);
    s >> m_header_prefix;
}
