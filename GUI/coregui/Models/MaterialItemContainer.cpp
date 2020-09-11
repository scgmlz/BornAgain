// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialItemContainer.cpp
//! @brief     Implements class MaterialItemContainer
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/MaterialItemContainer.h"
#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Models/SessionModel.h"
#include "GUI/coregui/utils/GUIHelpers.h"

const QString MaterialItemContainer::T_MATERIALS = "MaterialVector";

MaterialItemContainer::MaterialItemContainer() : SessionItem("MaterialContainer")
{
    setItemName("Materials");
    registerTag(T_MATERIALS, 0, -1, QStringList{"Material"});
}

MaterialItem* MaterialItemContainer::insertCopy(MaterialItem* material_item)
{
    MaterialItem* item_copy =
        dynamic_cast<MaterialItem*>(model()->copyItem(material_item, this, T_MATERIALS));
    item_copy->setItemValue(MaterialItem::P_IDENTIFIER, GUIHelpers::createUuid());

    return item_copy;
}

MaterialItem* MaterialItemContainer::findMaterialById(QString id)
{
    return const_cast<MaterialItem*>(
        static_cast<const MaterialItemContainer*>(this)->findMaterialById(id));
}

const MaterialItem* MaterialItemContainer::findMaterialById(QString id) const
{
    auto materials = getItems(T_MATERIALS);
    for (auto item : materials) {
        auto material = dynamic_cast<MaterialItem*>(item);
        if (material->identifier() == id)
            return material;
    }
    return nullptr;
}
