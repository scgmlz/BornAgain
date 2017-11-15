// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ModelUtils.h
//! @brief     Defines ModelUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef MODELUTILS_H
#define MODELUTILS_H

#include "WinDllMacros.h"
#include <functional>

class QModelIndex;
class QAbstractItemModel;

namespace ModelUtils
{

//! Iterates through all model indices and calls user function.
BA_CORE_API_ void iterate(const QModelIndex& index, const QAbstractItemModel* model,
                          const std::function<void(const QModelIndex&)>& fun);

//! Iterates through all model indices and calls user function.
//! If function returns false for given index, iteration will not go down to children.
BA_CORE_API_ void iterate_if(const QModelIndex& index, const QAbstractItemModel* model,
                          const std::function<bool(const QModelIndex&)>& fun);

}

#endif  //  MODELUTILS_H
