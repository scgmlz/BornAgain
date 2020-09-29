// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItemUtils.h
//! @brief     Defines namespace SessionItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_SESSIONITEMUTILS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_SESSIONITEMUTILS_H

#include "Core/Vector/Vectors3D.h"
#include <QString>
#include <QVariant>

class SessionItem;
class GroupInfo;

namespace SessionItemUtils
{
//! Returns the index of the given item within its parent. Returns -1 when no parent is set.
int ParentRow(const SessionItem& item);

//! Returns a VectorType group property's value as a kvector_t.
kvector_t GetVectorItem(const SessionItem& item, const QString& name);

//! Returns a VectorType group property's value as a kvector_t.
void SetVectorItem(const SessionItem& item, const QString& name, kvector_t value);

//! Returns the row of the given item within its parent not accounting for all hidden items
//! above. Returns -1 when no parent set or item is hidden.
int ParentVisibleRow(const SessionItem& item);

//! Returns text color for given item.
QVariant TextColorRole(const SessionItem& item);

//! Returns tooltip for given item.
QVariant ToolTipRole(const SessionItem& item, int ncol = 0);

//! Returns tooltip for given item.
QVariant DecorationRole(const SessionItem& item);

//! Returns check state for given item.
QVariant CheckStateRole(const SessionItem& item);

//! Returns true if there is registered group.
bool IsValidGroup(const QString& group_type);

//! Returns GroupInfo for group property construction
GroupInfo GetGroupInfo(const QString& group_type);

//! Returns type of variant (additionally checks for user type).
int VariantType(const QVariant& variant);

//! Returns true if variants has compatible types.
bool CompatibleVariantTypes(const QVariant& oldValue, const QVariant& newValue);

//! Returns true if given variants have same type and value.
//! For custom variants (ComboProperty, ExternalProperty) will always return false (see
//! explanations in cpp file).

bool IsTheSame(const QVariant& var1, const QVariant& var2);

//! Returns true if current item is related to the position on sample editor canvas.
bool IsPositionRelated(const SessionItem& item);

bool HasOwnAbundance(const SessionItem* item);

} // namespace SessionItemUtils

#endif // BORNAGAIN_GUI_COREGUI_MODELS_SESSIONITEMUTILS_H
