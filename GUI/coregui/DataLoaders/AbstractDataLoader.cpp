//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      GUI/coregui/DataLoaders/AbstractDataLoader.cpp
//! @brief     Implements class AbstractDataLoader
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2021
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "GUI/coregui/DataLoaders/AbstractDataLoader.h"
#include <QString>

QString AbstractDataLoader::info() const
{
    return QString();
}

void AbstractDataLoader::fillPropertiesGroupBox(QGroupBox* parent) {}

QByteArray AbstractDataLoader::serialize() const
{
    return QByteArray();
}

void AbstractDataLoader::deserialize(QByteArray& data) {}
