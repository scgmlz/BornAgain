// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/PropertyEditorFactory.h
//! @brief     Defines PropertyEditorFactory namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_PROPERTYEDITORFACTORY_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_PROPERTYEDITORFACTORY_H

#include "Wrap/WinDllMacros.h"
#include <QString>

class QModelIndex;
class QWidget;
class SessionItem;
class QVariant;

//! Creates editors for SessionItem's values.

namespace PropertyEditorFactory
{

//! Returns true if the index data has known (custom) convertion to string.
BA_CORE_API_ bool hasStringRepresentation(const QModelIndex& index);

//! Provides string representation of index data.
BA_CORE_API_ QString toString(const QModelIndex& index);

//! Creates an editor suitable for editing of item.value()
BA_CORE_API_ QWidget* CreateEditor(const SessionItem& item, QWidget* parent = nullptr);

} // namespace PropertyEditorFactory

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_PROPERTYEDITORFACTORY_H
