// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitSuiteItem.h
//! @brief     Defines class FitSuiteItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_GUI_COREGUI_MODELS_FITSUITEITEM_H
#define BORNAGAIN_GUI_COREGUI_MODELS_FITSUITEITEM_H

#include "GUI/coregui/Models/SessionItem.h"

class FitParameterContainerItem;
class MinimizerContainerItem;

class BA_CORE_API_ FitSuiteItem : public SessionItem
{

public:
    static const QString P_UPDATE_INTERVAL;
    static const QString P_ITERATION_COUNT;
    static const QString P_CHI2;
    static const QString T_FIT_PARAMETERS_CONTAINER;
    static const QString T_MINIMIZER;
    explicit FitSuiteItem();

    FitParameterContainerItem* fitParameterContainerItem();
    MinimizerContainerItem* minimizerContainerItem();
};

#endif // BORNAGAIN_GUI_COREGUI_MODELS_FITSUITEITEM_H
