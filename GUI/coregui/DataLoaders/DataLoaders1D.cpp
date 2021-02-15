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
#include "GUI/coregui/DataLoaders/ConfigurableDataLoader1D.h"
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
}

DataLoaders1D& DataLoaders1D::instance()
{
    return *m_instance;
}

void DataLoaders1D::initBuiltInLoaders()
{
    m_builtInLoaders << new AutomaticDataLoader1D();
    m_builtInLoaders << new AutomaticMultiColumnDataLoader1D();
    m_builtInLoaders << new ConfigurableDataLoader1D();
}

QVector<AbstractDataLoader*> DataLoaders1D::loaders() const
{
    return m_builtInLoaders + m_userDefinedLoaders;
}

QVector<AbstractDataLoader*> DataLoaders1D::recentlyUsedLoaders() const
{
    return m_recentlyUsedLoaders;
}

void DataLoaders1D::cloneAsUserDefinedLoader(AbstractDataLoader* loader, const QString& name)
{
    auto clonedLoader = createFromPersistentName(loader->persistentClassName());
    clonedLoader->deserialize(loader->serialize());

    m_userDefinedLoaders << new UserDefinedDataLoader1D(clonedLoader, name);
}

AbstractDataLoader1D* DataLoaders1D::createFromPersistentName(const QString& persistentClassName)
{
    if (persistentClassName == AutomaticDataLoader1D().persistentClassName())
        return new AutomaticDataLoader1D();

    if (persistentClassName == AutomaticMultiColumnDataLoader1D().persistentClassName())
        return new AutomaticMultiColumnDataLoader1D();

    if (persistentClassName == ConfigurableDataLoader1D().persistentClassName())
        return new ConfigurableDataLoader1D();

    return nullptr;
}
