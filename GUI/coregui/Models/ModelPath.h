// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ModelPath.h
//! @brief     Defines ModelPath namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_MODELPATH_H
#define BORNAGAIN_GUI_COREGUI_MODELS_MODELPATH_H

#include "GUI/coregui/Models/ParameterTranslators.h"
#include "Wrap/WinDllMacros.h"
#include <memory>
#include <vector>

class SessionItem;
class QModelIndex;
class SessionModel;

namespace ModelPath
{
BA_CORE_API_ QString getPathFromIndex(const QModelIndex& index);

BA_CORE_API_ QModelIndex getIndexFromPath(const SessionModel* model, const QString& path);

BA_CORE_API_ SessionItem* getItemFromPath(const QString& relPath, const SessionItem* parent);

BA_CORE_API_ bool isValidItem(SessionModel* model, SessionItem* item, const QModelIndex& parent);

BA_CORE_API_ const SessionItem* ancestor(const SessionItem* item, const QString& requiredModelType);

BA_CORE_API_ QString itemPathTranslation(const SessionItem& item, const SessionItem* topItem = 0);
} // namespace ModelPath

#endif // BORNAGAIN_GUI_COREGUI_MODELS_MODELPATH_H
