// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Fitting/AdjustMinimizerPlan.h
//! @brief     Defines collection of AdjustMinimizerPlan classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_ADJUSTMINIMIZERPLAN_H
#define BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_ADJUSTMINIMIZERPLAN_H

#include "Tests/Functional/Core/Fitting/Plan.h"

//! Two parameter fit: cylinders in BA with mini GISAS simulation.
//! Parameters are made far from their original values, Genetic+Minuit used in pair.

class AdjustMinimizerPlan : public Plan
{
public:
    AdjustMinimizerPlan();

    bool checkMinimizer(Fit::Minimizer& minimizer);
};

#endif // BORNAGAIN_TESTS_FUNCTIONAL_CORE_FITTING_ADJUSTMINIMIZERPLAN_H
