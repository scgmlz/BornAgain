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

#include "GUI/coregui/Models/ItemFactory.h"
#include "GUI/coregui/Models/ItemCatalog.h"
#include "GUI/coregui/Models/SessionItem.h"

namespace
{

//! Returns the single instance of ItemCatalog.
const ItemCatalog& catalog()
{
    static ItemCatalog item_catalog;
    return item_catalog;
}

} // namespace

SessionItem* ItemFactory::CreateItem(const QString& model_name, SessionItem* parent)
{
    SessionItem* result = catalog().createItemPtr(model_name).release();
    if (parent)
        parent->insertItem(-1, result);

    return result;
}

SessionItem* ItemFactory::CreateEmptyItem()
{
    return new SessionItem("ROOT_ITEM");
}

QStringList ItemFactory::ValidTopItemTypes()
{
    return catalog().validTopItemTypes();
}
