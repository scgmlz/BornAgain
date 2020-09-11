// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/utils/ItemIDFactory.cpp
//! @brief     Implements class ItemIDFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/utils/ItemIDFactory.h"

ItemIDFactory& ItemIDFactory::instance()
{
    static ItemIDFactory instance;
    return instance;
}

QString ItemIDFactory::createID(SessionItem* toBeInsertedItem)
{

    QUuid id = QUuid::createUuid();
    QString id_String = id.toString();

    // prevent duplicates (very improbable that this ever happens though)
    while (instance().IDtoItemMap.contains(id_String)) {
        id = QUuid::createUuid();
        id_String = id.toString();
    }
    instance().ItemtoIDMap.insert(toBeInsertedItem, id_String);
    instance().IDtoItemMap.insert(id_String, toBeInsertedItem);

    return id_String;
}

QString ItemIDFactory::getID(SessionItem* existingItem)
{
    if (instance().ItemtoIDMap.contains(existingItem))
        return instance().ItemtoIDMap.value(existingItem);
    else
        return "";
}

SessionItem* ItemIDFactory::getItem(QString existingID)
{
    if (instance().IDtoItemMap.contains(existingID))
        return instance().IDtoItemMap.value(existingID);
    else
        return nullptr;
}

int ItemIDFactory::IDSize()
{
    static QUuid id = QUuid::createUuid();
    return id.toString().size();
}
