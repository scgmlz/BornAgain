// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitObjectiveTestFactory.cpp
//! @brief     Defines class FitObjectiveTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitObjectiveTestFactory.h"
#include "FitObjectiveTestCases.h"

FitObjectiveTestFactory::FitObjectiveTestFactory()
{
    registerItem("MigradCylindersInBA", create_new<MigradCylindersInBA>,
                 "Minuit + CylindersInBA");
    registerItem("MigradResidualCylindersInBA", create_new<MigradResidualCylindersInBA>,
                 "Minuit + ResidualCylindersInBA");
    registerItem("BfgsCylindersInBA", create_new<BfgsCylindersInBA>,
                 "BFGS + CylindersInBA");
    registerItem("SteepestDescentCylindersInBA", create_new<SteepestDescentCylindersInBA>,
                 "SteepestDescent + CylindersInBA");
    registerItem("FumuliCylindersInBA", create_new<FumuliCylindersInBA>,
                 "Fumili + CylindersInBA (Residual)");
    registerItem("LevenbergMarquardtCylindersInBA", create_new<LevenbergMarquardtCylindersInBA>,
                 "Levenberg-Marquardt + CylindersInBA (Residual)");
    registerItem("SimAnCylindersInBA", create_new<SimAnCylindersInBA>,
                 "Simulated annealing + CylindersInBA (Easy)");
    registerItem("GeneticCylindersInBA", create_new<GeneticCylindersInBA>,
                 "Genetic + CylindersInBA (Easy)");
    registerItem("RectDetectorFit", create_new<RectDetectorFit>,
                 "Minuit + RectDet with ROI, CylindersInBA");
    registerItem("AdjustMinimizerFit", create_new<AdjustMinimizerFit>,
                 "Minuit + Genetic, CylindersInBA");
    registerItem("SpecularFitTest", create_new<SpecularFitTest>,
                 "Minuit, Basic specular fitting");
    registerItem("SpecularFitTestQ", create_new<SpecularFitTestQ>,
                 "Minuit, Basic specular fitting (q-defined instrument)");
    registerItem("MultipleSpecFittingTest", create_new<MultipleSpecFittingTest>,
                 "Minuit, fitting of several reflectometry curves");
    registerItem("OffSpecFitTest", create_new<OffSpecFitTest>,
                 "Minuit, basic off-spec fitting");
}
