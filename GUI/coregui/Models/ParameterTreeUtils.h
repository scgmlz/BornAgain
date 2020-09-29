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

void createParameterTree(JobItem* jobItem);

void populateParameterContainer(SessionItem* container, const SessionItem* source);

void visitParameterContainer(SessionItem* container, std::function<void(ParameterItem*)> fun);

QStringList parameterTreeNames(const SessionItem* source);

QStringList translatedParameterTreeNames(const SessionItem* source);

QVector<QPair<QString, QString>> parameterDictionary(const SessionItem* source);

QString domainNameToParameterName(const QString& domainName, const SessionItem* source);

QString parameterNameToDomainName(const QString& parName, const SessionItem* source);

SessionItem* parameterNameToLinkedItem(const QString& parName, const SessionItem* source);

} // namespace ParameterTreeUtils

#endif // BORNAGAIN_GUI_COREGUI_MODELS_PARAMETERTREEUTILS_H
