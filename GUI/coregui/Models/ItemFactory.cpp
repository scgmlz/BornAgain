// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ItemFactory.cpp
//! @brief     Implements class ItemFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ItemFactory.h"
#include "GUIHelpers.h"
#include "ItemCatalogue.h"
#include "SessionItem.h"

namespace
{

const ItemCatalogue& catalogue()
{
    static ItemCatalogue item_catalogue;
    return item_catalogue;
}

} // namespace

SessionItem* ItemFactory::CreateItem(const QString& model_name, SessionItem* parent)
{
    if (!catalogue().contains(model_name))
        throw GUIHelpers::Error("ItemFactory::createItem() -> Error: Model name does not exist: "
                                + model_name);

    SessionItem* result = catalogue().create(model_name).release();
    if (parent)
        parent->insertItem(-1, result);

    return result;
}

SessionItem* ItemFactory::CreateEmptyItem()
{
    return new SessionItem(Constants::RootItemType);
}

QStringList ItemFactory::ValidTopItemTypes()
{
    return catalogue().validTopItemTypes();
}
