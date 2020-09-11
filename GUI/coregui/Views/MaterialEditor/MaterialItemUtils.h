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

BA_CORE_API_ QColor suggestMaterialColor(const QString& name);
BA_CORE_API_ ExternalProperty defaultMaterialProperty();

BA_CORE_API_ std::unique_ptr<Material>
createDomainMaterial(const ExternalProperty& material_property);
BA_CORE_API_ std::unique_ptr<Material>
createDomainMaterial(const ExternalProperty& material_property,
                     const MaterialItemContainer& container);
BA_CORE_API_ MaterialItem* findMaterial(const ExternalProperty& material_property);

BA_CORE_API_ QString materialTag(const SessionItem& item);
BA_CORE_API_ QStringList materialRelatedModelTypes();

//! Constructs material property corresponding to given material.
BA_CORE_API_ ExternalProperty materialProperty(const SessionItem& materialItem);

//! Constructs color property from given color.
BA_CORE_API_ ExternalProperty colorProperty(const QColor& color);

//! Calls material selector dialog.
BA_CORE_API_ ExternalProperty
selectMaterialProperty(const ExternalProperty& previous = ExternalProperty());

//! Calls color selector dialog.
BA_CORE_API_ ExternalProperty
selectColorProperty(const ExternalProperty& previous = ExternalProperty());

//! Gather material property items from a given item
BA_CORE_API_ QVector<SessionItem*> materialPropertyItems(SessionItem* item);
} // namespace MaterialItemUtils

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_MATERIALEDITOR_MATERIALITEMUTILS_H
