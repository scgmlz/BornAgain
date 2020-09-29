// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/MaterialEditor/MaterialItemUtils.h
//! @brief     Defines class MaterialItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALITEMUTILS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALITEMUTILS_H

#include "GUI/coregui/Models/MaterialItem.h"
#include "GUI/coregui/Views/MaterialEditor/ExternalProperty.h"
#include <QColor>
#include <QString>
#include <memory>

class Material;
class MaterialItemContainer;

namespace MaterialItemUtils
{

QColor suggestMaterialColor(const QString& name);
ExternalProperty defaultMaterialProperty();

std::unique_ptr<Material> createDomainMaterial(const ExternalProperty& material_property);
std::unique_ptr<Material> createDomainMaterial(const ExternalProperty& material_property,
                                               const MaterialItemContainer& container);
MaterialItem* findMaterial(const ExternalProperty& material_property);

QString materialTag(const SessionItem& item);
QStringList materialRelatedModelTypes();

//! Constructs material property corresponding to given material.
ExternalProperty materialProperty(const SessionItem& materialItem);

//! Constructs color property from given color.
ExternalProperty colorProperty(const QColor& color);

//! Calls material selector dialog.
ExternalProperty selectMaterialProperty(const ExternalProperty& previous = ExternalProperty());

//! Calls color selector dialog.
ExternalProperty selectColorProperty(const ExternalProperty& previous = ExternalProperty());

//! Gather material property items from a given item
QVector<SessionItem*> materialPropertyItems(SessionItem* item);
} // namespace MaterialItemUtils

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALITEMUTILS_H
