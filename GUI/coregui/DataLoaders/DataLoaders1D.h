//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/DataLoaders1D.h
//! @brief     Defines class DataLoaders1D
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_GUI_COREGUI_DATALOADERS_DATALOADERS1D_H
#define BORNAGAIN_GUI_COREGUI_DATALOADERS_DATALOADERS1D_H

#include <QVector>

class AbstractDataLoader;
class AbstractDataLoader1D;

//! Collection of all available data loaders for 1D files

class DataLoaders1D {
public:
    DataLoaders1D();
    ~DataLoaders1D();

    //! The one and only instance
    static DataLoaders1D& instance();

    //! all defined loaders. A null element in the list defines a separator
    QVector<AbstractDataLoader*> loaders() const;

    //! The last 10 recently used loaders.
    QVector<AbstractDataLoader*> recentlyUsedLoaders() const;

    //! Notify loader was recently used
    void setRecentlyUsedLoader(const AbstractDataLoader* loader);

    //! Clone the loader and create a user defined loader with its current settings and the given
    //! name
    void cloneAsUserDefinedLoader(AbstractDataLoader* loader, const QString& name);

    //! Create loader from the given persistent name
    AbstractDataLoader1D* createFromPersistentName(const QString& persistentClassName);

private:
    //! create all default built in loaders
    void initBuiltInLoaders();

private:
    static DataLoaders1D* m_instance;
    QVector<AbstractDataLoader*> m_builtInLoaders;
    QVector<AbstractDataLoader*> m_recentlyUsedLoaders;
    QVector<AbstractDataLoader*> m_userDefinedLoaders;
};

#endif // BORNAGAIN_GUI_COREGUI_DATALOADERS_DATALOADERS1D_H
