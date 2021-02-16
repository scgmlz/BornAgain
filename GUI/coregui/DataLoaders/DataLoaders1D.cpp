//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/DataLoaders1D.cpp
//! @brief     Implements class DataLoaders1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/DataLoaders/DataLoaders1D.h"
#include "GUI/coregui/DataLoaders/AutomaticDataLoader1D.h"
#include "GUI/coregui/DataLoaders/AutomaticMultiColumnDataLoader1D.h"
#include "GUI/coregui/DataLoaders/UserDefinedDataLoader1D.h"

DataLoaders1D* DataLoaders1D::m_instance = nullptr;

DataLoaders1D dataLoadres1D;

DataLoaders1D::DataLoaders1D()
{
    m_instance = this;
}

DataLoaders1D::~DataLoaders1D()
{
    qDeleteAll(m_builtInLoaders);
    qDeleteAll(m_userDefinedLoaders);
}

DataLoaders1D& DataLoaders1D::instance()
{
    return *m_instance;
}

void DataLoaders1D::initBuiltInLoaders()
{
    m_builtInLoaders << new AutomaticDataLoader1D();
    m_builtInLoaders << new AutomaticMultiColumnDataLoader1D();
}

QVector<AbstractDataLoader*> DataLoaders1D::loaders() const
{
    if (m_builtInLoaders.isEmpty())
        const_cast<DataLoaders1D*>(this)->initBuiltInLoaders();
    return m_builtInLoaders + m_userDefinedLoaders;
}

QVector<AbstractDataLoader*> DataLoaders1D::recentlyUsedLoaders() const
{
    return m_recentlyUsedLoaders;
}

void DataLoaders1D::cloneAsUserDefinedLoader(AbstractDataLoader* loader, const QString& name)
{
    loader->applyProperties();
    auto clonedLoader = dynamic_cast<AbstractDataLoader1D*>(loader->clone());
    const auto defaultProperties = loader->serialize();

    m_userDefinedLoaders << new UserDefinedDataLoader1D(clonedLoader, name, defaultProperties);
}

AbstractDataLoader1D* DataLoaders1D::createFromPersistentName(const QString& persistentClassName)
{
    if (persistentClassName == AutomaticDataLoader1D().persistentClassName())
        return new AutomaticDataLoader1D();

    if (persistentClassName == AutomaticMultiColumnDataLoader1D().persistentClassName())
        return new AutomaticMultiColumnDataLoader1D();

    return nullptr;
}
