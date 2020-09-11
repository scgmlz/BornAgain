// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ModelUtils.h
//! @brief     Defines ModelUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_MODELUTILS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_MODELUTILS_H

#include "Wrap/WinDllMacros.h"
#include <QString>
#include <functional>

class QModelIndex;
class QAbstractItemModel;
class SessionModel;

namespace ModelUtils
{
//! Returns list of top iten manes.
BA_CORE_API_ QStringList topItemNames(SessionModel* model, const QString& modelType = "");

//! Iterates through all model indices and calls user function.
BA_CORE_API_ void iterate(const QModelIndex& index, const QAbstractItemModel* model,
                          const std::function<void(const QModelIndex&)>& fun);

//! Iterates through all model indices and calls user function.
//! If function returns false for given index, iteration will not go down to children.
BA_CORE_API_ void iterate_if(const QModelIndex& index, const QAbstractItemModel* model,
                             const std::function<bool(const QModelIndex&)>& fun);

} // namespace ModelUtils

#endif // BORNAGAIN_GUI_COREGUI_MODELS_MODELUTILS_H
