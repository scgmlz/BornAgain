// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/MaterialItem.cpp
//! @brief     Implements class MaterialItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/MaterialItem.h"
#include "Core/Material/MaterialFactoryFuncs.h"
#include "GUI/coregui/Models/MaterialDataItems.h"
#include "GUI/coregui/Models/SessionItemUtils.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"
#include "GUI/coregui/utils/GUIHelpers.h"

using SessionItemUtils::GetVectorItem;

namespace
{
const QString magnetization_tooltip = "Magnetization (A/m)";
}

const QString MaterialItem::P_COLOR = "Color";
const QString MaterialItem::P_MATERIAL_DATA = "Material data";
const QString MaterialItem::P_MAGNETIZATION = "Magnetization";
const QString MaterialItem::P_IDENTIFIER = "Identifier";

MaterialItem::MaterialItem() : SessionItem("Material")
{
    setItemName("Material");

    ExternalProperty color = MaterialItemUtils::colorProperty(QColor(Qt::red));
    addProperty(P_COLOR, color.variant())->setEditorType("ExtColorEditor");

    addGroupProperty(P_MATERIAL_DATA, "Material data group");
    addGroupProperty(P_MAGNETIZATION, "Vector")->setToolTip(magnetization_tooltip);
    addProperty(P_IDENTIFIER, GUIHelpers::createUuid());
    getItem(P_IDENTIFIER)->setVisible(false);
}

//! Turns material into refractive index material.

void MaterialItem::setRefractiveData(double delta, double beta)
{
    auto refractiveData = setGroupProperty(P_MATERIAL_DATA, "MaterialRefractiveData");
    refractiveData->setItemValue(MaterialRefractiveDataItem::P_DELTA, delta);
    refractiveData->setItemValue(MaterialRefractiveDataItem::P_BETA, beta);
}

//! Turns material into SLD based material.

void MaterialItem::setSLDData(double sld_real, double sld_imag)
{
    auto sldData = setGroupProperty(P_MATERIAL_DATA, "MaterialSLDData");
    sldData->setItemValue(MaterialSLDDataItem::P_SLD_REAL, sld_real);
    sldData->setItemValue(MaterialSLDDataItem::P_SLD_IMAG, sld_imag);
}

QString MaterialItem::identifier() const
{
    return getItemValue(P_IDENTIFIER).toString();
}

QColor MaterialItem::color() const
{
    ExternalProperty property = getItemValue(P_COLOR).value<ExternalProperty>();
    return property.color();
}

std::unique_ptr<Material> MaterialItem::createMaterial() const
{
    auto dataItem = getGroupItem(P_MATERIAL_DATA);
    auto magnetization = GetVectorItem(*this, P_MAGNETIZATION);
    auto name = itemName().toStdString();

    if (dataItem->modelType() == "MaterialRefractiveData") {
        double delta = dataItem->getItemValue(MaterialRefractiveDataItem::P_DELTA).toDouble();
        double beta = dataItem->getItemValue(MaterialRefractiveDataItem::P_BETA).toDouble();
        return std::make_unique<Material>(HomogeneousMaterial(name, delta, beta, magnetization));

    } else if (dataItem->modelType() == "MaterialSLDData") {
        double sld_real = dataItem->getItemValue(MaterialSLDDataItem::P_SLD_REAL).toDouble();
        double sld_imag = dataItem->getItemValue(MaterialSLDDataItem::P_SLD_IMAG).toDouble();
        return std::make_unique<Material>(MaterialBySLD(name, sld_real, sld_imag, magnetization));
    }

    throw GUIHelpers::Error("MaterialItem::createMaterial() -> Error. "
                            "Not implemented material type");
}
