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
#include "GUI/coregui/DataLoaders/QREDataLoader.h"
#include "GUI/coregui/DataLoaders/UserDefinedDataLoader1D.h"

namespace {

// the one and only instance of DataLoaders1D
DataLoaders1D dataLoaders1D;

} // namespace

DataLoaders1D* DataLoaders1D::m_instance = nullptr;

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
    // #baimport enable again when implementation is completed
    // m_builtInLoaders << new AutomaticDataLoader1D();
    m_builtInLoaders << new QREDataLoader();
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

    if (persistentClassName == QREDataLoader().persistentClassName())
        return new QREDataLoader();

    return nullptr;
}
