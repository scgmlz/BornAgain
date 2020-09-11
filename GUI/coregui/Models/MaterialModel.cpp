// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialModel.cpp
//! @brief     Implements class MaterialModel
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/MaterialModel.h"
#include "GUI/coregui/Models/MaterialDataItems.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "GUI/coregui/mainwindow/AppSvc.h"
#include "GUI/coregui/utils/GUIHelpers.h"

MaterialModel::MaterialModel(QObject* parent) : SessionModel(SessionXML::MaterialModelTag, parent)
{
    setObjectName(SessionXML::MaterialModelTag);
    if (AppSvc::materialModel() == nullptr)
        AppSvc::subscribe(this);
}

MaterialModel::~MaterialModel()
{
    if (AppSvc::materialModel() == this)
        AppSvc::unsubscribe(this);
}

MaterialModel* MaterialModel::createCopy(SessionItem* parent)
{
    MaterialModel* result = new MaterialModel();
    result->initFrom(this, parent);
    return result;
}

MaterialItem* MaterialModel::addRefractiveMaterial(const QString& name, double delta, double beta)
{
    auto materialItem = createMaterial(name);
    materialItem->setRefractiveData(delta, beta);
    return materialItem;
}

MaterialItem* MaterialModel::addSLDMaterial(const QString& name, double sld, double abs_term)
{
    auto materialItem = createMaterial(name);
    materialItem->setSLDData(sld, abs_term);
    return materialItem;
}

MaterialItem* MaterialModel::materialFromIndex(const QModelIndex& index)
{
    return dynamic_cast<MaterialItem*>(itemForIndex(index));
}

MaterialItem* MaterialModel::materialFromName(const QString& name)
{
    for (auto materialItem : topItems<MaterialItem>())
        if (materialItem->itemName() == name)
            return materialItem;

    return nullptr;
}

MaterialItem* MaterialModel::materialFromIdentifier(const QString& identifier)
{
    for (auto materialItem : topItems<MaterialItem>())
        if (materialItem->identifier() == identifier)
            return materialItem;

    return nullptr;
}

//! Returns clone of material with given index. Clone will get unique identifier.

MaterialItem* MaterialModel::cloneMaterial(const QModelIndex& index)
{
    const auto origMaterial = materialFromIndex(index);
    if (!origMaterial)
        return nullptr;

    auto clonedMaterial = copyItem(origMaterial, 0);
    clonedMaterial->setItemValue(MaterialItem::P_IDENTIFIER, GUIHelpers::createUuid());
    clonedMaterial->setItemName(origMaterial->itemName() + " (clone)");
    return dynamic_cast<MaterialItem*>(clonedMaterial);
}

//! Creates material with name and color. Material data remains uninitialized.

MaterialItem* MaterialModel::createMaterial(const QString& name)
{
    auto result = dynamic_cast<MaterialItem*>(insertNewItem("Material"));
    result->setItemName(name);

    QColor color = MaterialItemUtils::suggestMaterialColor(name);
    result->setItemValue(MaterialItem::P_COLOR, MaterialItemUtils::colorProperty(color).variant());

    return result;
}
