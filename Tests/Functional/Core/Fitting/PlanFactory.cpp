// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/PlanFactory.cpp
//! @brief     Implements class PlanFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/Core/Fitting/PlanFactory.h"
#include "Tests/Functional/Core/Fitting/AdjustMinimizerPlan.h"
#include "Tests/Functional/Core/Fitting/PlanCases.h"

PlanFactory::PlanFactory()
{
    registerItem("CylindersInBAPlan", create_new<CylindersInBAPlan>);
    registerItem("CylindersInBAEasyPlan", create_new<CylindersInBAEasyPlan>);
    registerItem("CylindersInBAResidualPlan", create_new<CylindersInBAResidualPlan>);
    registerItem("RectDetPlan", create_new<RectDetPlan>);
    registerItem("AdjustMinimizerPlan", create_new<AdjustMinimizerPlan>);
    registerItem("SpecularPlan", create_new<SpecularPlan>);
    registerItem("SpecularPlanQ", create_new<SpecularPlanQ>);
    registerItem("MultipleSpecPlan", create_new<MultipleSpecPlan>);
    registerItem("OffSpecPlan", create_new<OffSpecPlan>);
}
