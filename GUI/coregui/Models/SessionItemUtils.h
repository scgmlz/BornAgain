// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/SessionItemUtils.h
//! @brief     Defines namespace SessionItemUtils
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke, Dmitry Yurov
//
// ************************************************************************** //

#ifndef SESSIONITEMUTILS_H
#define SESSIONITEMUTILS_H

#include "Vectors3D.h"
#include "WinDllMacros.h"
#include <QString>

class SessionItem;

namespace SessionItemUtils
{
//! Returns the index of the given item within its parent. Returns -1 when no parent is set.
BA_CORE_API_ int ParentRow(const SessionItem& item);

//! Returns a VectorType group property's value as a kvector_t.
BA_CORE_API_ kvector_t GetVectorItem(const SessionItem& item, const QString& name);

//! Returns a VectorType group property's value as a kvector_t.
BA_CORE_API_ void SetVectorItem(const SessionItem& item, const QString& name, kvector_t value);

//! Returns the row of the given item within its parent not accounting for all hidden items
//! above. Returns -1 when no parent set or item is hidden.

BA_CORE_API_ int ParentVisibleRow(const SessionItem& item);

}  // namespace SessionItemUtils

#endif // SESSIONITEMUTILS_H
