// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/PropertyEditor/ComponentUtils.h
//! @brief     Defines ComponentUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTUTILS_H
#define BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTUTILS_H

#include "Wrap/WinDllMacros.h"
#include <QList>
#include <QStringList>

class SessionItem;

//! Contains collection of utility functions to support editing of SessionItem's components.

namespace ComponentUtils
{

//! Returns list of strings representing modelTypes suitable for editing in component editors.
BA_CORE_API_ QStringList propertyRelatedTypes();

//! Returns list of SessionItem's children suitable for editing in property editors.
BA_CORE_API_ QList<const SessionItem*> componentItems(const SessionItem& item);

} // namespace ComponentUtils

#endif // BORNAGAIN_GUI_COREGUI_VIEWS_PROPERTYEDITOR_COMPONENTUTILS_H
