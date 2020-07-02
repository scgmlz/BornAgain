// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/FitObjective/AdjustMinimizerPlan.h
//! @brief     Defines collection of AdjustMinimizerPlan classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ADJUSTMINIMIZERPLAN_H
#define ADJUSTMINIMIZERPLAN_H

#include "FitPlan.h"

//! Two parameter fit: cylinders in BA with mini GISAS simulation.
//! Parameters are made far from their original values, Genetic+Minuit used in pair.

class AdjustMinimizerPlan : public FitPlan
{
public:
    AdjustMinimizerPlan();

    bool checkMinimizer(Fit::Minimizer& minimizer);
};

#endif //  ADJUSTMINIMIZERPLAN_H
