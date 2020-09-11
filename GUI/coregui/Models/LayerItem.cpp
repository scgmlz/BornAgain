// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/LayerItem.cpp
//! @brief     Implements class LayerItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/LayerItem.h"
#include "GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h"

namespace
{
const QString layer_nslices_tooltip = "Number of horizontal slices.\n"
                                      "Used for Average Layer Material calculations \n"
                                      "when corresponding Simulation option set.";
}

const QString LayerItem::P_THICKNESS = QString::fromStdString("Thickness");
const QString LayerItem::P_ROUGHNESS = "Top roughness";
const QString LayerItem::P_MATERIAL = "Material";
const QString LayerItem::P_NSLICES = "Number of slices";
const QString LayerItem::T_LAYOUTS = "Layout tag";

LayerItem::LayerItem() : SessionGraphicsItem("Layer")
{
    setToolTip("A layer with thickness and material");
    addProperty(P_THICKNESS, 0.0)
        ->setLimits(RealLimits::lowerLimited(0.0))
        .setToolTip("Thickness of a layer in nanometers");

    addProperty(P_MATERIAL, MaterialItemUtils::defaultMaterialProperty().variant())
        ->setToolTip("Material the layer is made of")
        .setEditorType("ExtMaterialEditor");

    addProperty(P_NSLICES, 1)
        ->setLimits(RealLimits::lowerLimited(0.0))
        .setToolTip(layer_nslices_tooltip);

    addGroupProperty(P_ROUGHNESS, "Roughness")->setToolTip("Roughness of top interface");

    registerTag(T_LAYOUTS, 0, -1, QStringList() << "ParticleLayout");
    setDefaultTag(T_LAYOUTS);

    mapper()->setOnParentChange([this](SessionItem* new_parent) { updateAppearance(new_parent); });
}

QVector<SessionItem*> LayerItem::materialPropertyItems()
{
    QVector<SessionItem*> result;
    if (auto property = getItem(LayerItem::P_MATERIAL))
        result.push_back(property);
    for (auto layout : getItems(LayerItem::T_LAYOUTS))
        result.append(MaterialItemUtils::materialPropertyItems(layout));
    return result;
}

void LayerItem::updateAppearance(SessionItem* new_parent)
{
    if (!new_parent) {
        if (parent() && parent()->modelType() == "MultiLayer") {
            // we are about to be removed from MultiLayer
            getItem(LayerItem::P_ROUGHNESS)->setEnabled(true);
            getItem(LayerItem::P_THICKNESS)->setEnabled(true);
        }
    }
}
