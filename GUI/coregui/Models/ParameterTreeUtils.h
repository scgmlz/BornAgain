// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ParameterTreeUtils.h
//! @brief     Defines ParameterTreeUtils namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_PARAMETERTREEUTILS_H
#define BORNAGAIN_GUI_COREGUI_MODELS_PARAMETERTREEUTILS_H

#include "Wrap/WinDllMacros.h"
#include <QPair>
#include <QString>
#include <functional>

class JobItem;
class SessionItem;
class ParameterItem;

//! The ParameterTreeBuilder namespace contains helper functions to create container
//! with ParameterItems. The ParameterItem appears in RealTimeView and provides real
//! time tuning of MultiLayerItem and InstrumentItem.

namespace ParameterTreeUtils
{

BA_CORE_API_ void createParameterTree(JobItem* jobItem);

BA_CORE_API_ void populateParameterContainer(SessionItem* container, const SessionItem* source);

BA_CORE_API_ void visitParameterContainer(SessionItem* container,
                                          std::function<void(ParameterItem*)> fun);

BA_CORE_API_ QStringList parameterTreeNames(const SessionItem* source);

BA_CORE_API_ QStringList translatedParameterTreeNames(const SessionItem* source);

BA_CORE_API_ QVector<QPair<QString, QString>> parameterDictionary(const SessionItem* source);

BA_CORE_API_ QString domainNameToParameterName(const QString& domainName,
                                               const SessionItem* source);

BA_CORE_API_ QString parameterNameToDomainName(const QString& parName, const SessionItem* source);

BA_CORE_API_ SessionItem* parameterNameToLinkedItem(const QString& parName,
                                                    const SessionItem* source);

} // namespace ParameterTreeUtils

#endif // BORNAGAIN_GUI_COREGUI_MODELS_PARAMETERTREEUTILS_H
