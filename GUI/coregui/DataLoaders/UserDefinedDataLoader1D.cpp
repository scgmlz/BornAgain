//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/UserDefinedDataLoader1D.cpp
//! @brief     Implements class UserDefinedDataLoader1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/DataLoaders/UserDefinedDataLoader1D.h"

UserDefinedDataLoader1D::UserDefinedDataLoader1D(AbstractDataLoader1D* wrappedLoader,
                                                 const QString& name)
    : m_wrappedLoader(wrappedLoader), m_name(name)
{
}

QVector<QVector<QString>> UserDefinedDataLoader1D::parsedData() const
{
    return m_wrappedLoader->parsedData();
}

QString UserDefinedDataLoader1D::name() const
{
    return m_name;
}

QString UserDefinedDataLoader1D::info() const
{
    return m_wrappedLoader->info();
}

void UserDefinedDataLoader1D::fillPropertiesGroupBox(QGroupBox* parent)
{
    m_wrappedLoader->fillPropertiesGroupBox(parent);
}

QString UserDefinedDataLoader1D::persistentClassName() const
{
    return m_wrappedLoader->persistentClassName();
}

QByteArray UserDefinedDataLoader1D::serialize() const
{
    return m_wrappedLoader->serialize();
}

void UserDefinedDataLoader1D::deserialize(const QByteArray& data)
{
    m_wrappedLoader->deserialize(data);
}

QString UserDefinedDataLoader1D::preview(const QString& filepath, QCustomPlot* plotWidget) const
{
    return m_wrappedLoader->preview(filepath, plotWidget);
}

