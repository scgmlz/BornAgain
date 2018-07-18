// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialItemUtils.cpp
//! @brief     Implements class MaterialItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MaterialItemUtils.h"
#include "MaterialDataItems.h"
#include "ComboProperty.h"
#include "DesignerHelper.h"
#include "GUIHelpers.h"
#include "Material.h"
#include "MaterialModel.h"
#include "ParticleItem.h"
#include "LayerItem.h"
#include "MaterialEditorDialog.h"
#include "AppSvc.h"
#include "MaterialItem.h"
#include <QColorDialog>


QColor MaterialItemUtils::suggestMaterialColor(const QString &name)
{
    if(name.contains("Air") ) {
        return QColor(179, 242, 255);
    }
    else if(name.contains("Substrate") ) {
        return QColor(205,102,0);
    }
    else if ( name.contains("Default") ) {
        return QColor(Qt::green);
    }
    else if ( name.contains("Particle") ) {
        return QColor(146, 198, 255);
    }
    else {
        return DesignerHelper::getRandomColor();
    }
}


ExternalProperty MaterialItemUtils::defaultMaterialProperty()
{
    if (!AppSvc::materialModel())
        return ExternalProperty();

    auto materials = AppSvc::materialModel()->topItems();
    return materials.isEmpty() ? ExternalProperty() :
                                 MaterialItemUtils::materialProperty(*materials.front());
}


std::unique_ptr<Material>
MaterialItemUtils::createDomainMaterial(const ExternalProperty &material_property)
{
    if (!AppSvc::materialModel())
        throw GUIHelpers::Error("MaterialItemUtils::createDomainMaterial() -> Error. "
                                "Attempt to access non-existing material model");

    MaterialItem *materialItem
        = AppSvc::materialModel()->materialFromIdentifier(material_property.identifier());

    if(!materialItem)
        throw GUIHelpers::Error("MaterialUtils::createDomainMaterial() -> Error. Can't create "
                                "material with name '"+material_property.text()+"'.");

    return materialItem->createMaterial();
}

//! Returns material tag for given item. Returns empty string, if item doesn't have materials.

QString MaterialItemUtils::materialTag(const SessionItem &item)
{
    QString result;
    if (item.modelType() == Constants::ParticleType) {
        result = ParticleItem::P_MATERIAL;
    } else if (item.modelType() == Constants::LayerType) {
        result = LayerItem::P_MATERIAL;
    }
    return result;
}

//! Returns list of model types which contains registered MaterialProperty.

QStringList MaterialItemUtils::materialRelatedModelTypes()
{
    return {Constants::ParticleType, Constants::LayerType};
}

//! Constructs material property for given material.

ExternalProperty MaterialItemUtils::materialProperty(const SessionItem& materialItem)
{
    ExternalProperty result;

    ExternalProperty colorProperty = materialItem.getItemValue(MaterialItem::P_COLOR).value<ExternalProperty>();
    result.setIdentifier(materialItem.getItemValue(MaterialItem::P_IDENTIFIER).toString());
    result.setColor(colorProperty.color());
    result.setText(materialItem.itemName());

    return result;
}

ExternalProperty MaterialItemUtils::colorProperty(const QColor& color)
{
    ExternalProperty result;
    result.setColor(color);
    result.setText(QString("[%1, %2, %3] (%4)")
                   .arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha()));
    return result;
}

ExternalProperty MaterialItemUtils::selectMaterialProperty(const ExternalProperty& previous)
{
    MaterialEditorDialog dialog(AppSvc::materialModel());
    dialog.setMaterialProperty(previous);
    if(dialog.exec() == QDialog::Accepted) {
        return dialog.selectedMaterialProperty();
    }

    return ExternalProperty();
}


ExternalProperty MaterialItemUtils::selectColorProperty(const ExternalProperty& previous)
{
    ExternalProperty result;

    bool ok = false;
    QRgb oldRgba = previous.color().rgba();
    QRgb newRgba = QColorDialog::getRgba(oldRgba, &ok, nullptr);
    if (ok && newRgba != oldRgba)
        result = MaterialItemUtils::colorProperty(QColor::fromRgba(newRgba));

    return result;
}
