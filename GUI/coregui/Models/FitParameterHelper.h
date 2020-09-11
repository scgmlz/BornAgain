// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitParameterHelper.h
//! @brief     Defines class FitParameterHelper
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_FITPARAMETERHELPER_H
#define BORNAGAIN_GUI_COREGUI_MODELS_FITPARAMETERHELPER_H

#include "Wrap/WinDllMacros.h"
#include <QStringList>

class ParameterItem;
class FitParameterItem;
class FitParameterContainerItem;

//! The FitParameterHelper class contains set of convenience static methods to handle
//! various fitting items in given JobItem.

class BA_CORE_API_ FitParameterHelper
{
public:
    static void createFitParameter(FitParameterContainerItem* container,
                                   ParameterItem* parameterItem);

    static void removeFromFitParameters(FitParameterContainerItem* container,
                                        ParameterItem* parameterItem);
    static void addToFitParameter(FitParameterContainerItem* container,
                                  ParameterItem* parameterItem, const QString& fitParName);

    static FitParameterItem* getFitParameterItem(FitParameterContainerItem* container,
                                                 ParameterItem* parameterItem);

    static QStringList getFitParameterNames(FitParameterContainerItem* container);
    static QString getParameterItemPath(const ParameterItem* parameterItem);
    static ParameterItem* getParameterItem(FitParameterContainerItem* container,
                                           const QString& link);
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_FITPARAMETERHELPER_H
