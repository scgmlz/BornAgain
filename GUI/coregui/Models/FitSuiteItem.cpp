// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/FitSuiteItem.cpp
//! @brief     Implements class FitSuiteItem
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUI/coregui/Models/FitSuiteItem.h"
#include "GUI/coregui/Models/FitParameterItems.h"
#include "GUI/coregui/Models/MinimizerItem.h"

const QString FitSuiteItem::P_UPDATE_INTERVAL = "Update interval";
const QString FitSuiteItem::P_ITERATION_COUNT = "Number of iterations";
const QString FitSuiteItem::P_CHI2 = "Chi2";
const QString FitSuiteItem::T_FIT_PARAMETERS_CONTAINER = "Fit parameters container";
const QString FitSuiteItem::T_MINIMIZER = "Minimizer settings";

FitSuiteItem::FitSuiteItem() : SessionItem("FitSuite")
{
    addProperty(P_UPDATE_INTERVAL, 10);
    addProperty(P_ITERATION_COUNT, 0);
    addProperty(P_CHI2, 0.0);

    registerTag(T_FIT_PARAMETERS_CONTAINER, 1, 1, QStringList() << "FitParameterContainer");
    registerTag(T_MINIMIZER, 1, 1, QStringList() << "MinimizerContainer");
}

FitParameterContainerItem* FitSuiteItem::fitParameterContainerItem()
{
    return dynamic_cast<FitParameterContainerItem*>(
        getItem(FitSuiteItem::T_FIT_PARAMETERS_CONTAINER));
}

MinimizerContainerItem* FitSuiteItem::minimizerContainerItem()
{
    return dynamic_cast<MinimizerContainerItem*>(getItem(FitSuiteItem::T_MINIMIZER));
}
