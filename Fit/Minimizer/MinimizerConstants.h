// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerConstants.h
//! @brief     Defines class MinimizerConstants.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MINIMIZERCONSTANTS_H
#define MINIMIZERCONSTANTS_H

#include <string>

//! Names of minimizer libraries, like Minuit2, GSLLMA, ...

namespace MinimizerNames {

const std::string Minuit2 = "Minuit2";
const std::string GSLMultiMin = "GSLMultiMin";
const std::string GSLLMA = "GSLLMA";
const std::string GSLSimAn = "GSLSimAn";
const std::string Genetic = "Genetic";
const std::string Test = "Test";

} // namespace MinimizerNames

//! Names of minimizer algorithms, like Migrad, SteepestDescent, ...

namespace AlgorithmNames {

const std::string Migrad = "Migrad";
const std::string Simplex = "Simplex";
const std::string Combined = "Combined";
const std::string Scan = "Scan";
const std::string Fumili = "Fumili";

const std::string SteepestDescent = "SteepestDescent";
const std::string ConjugateFR = "ConjugateFR";
const std::string ConjugatePR = "ConjugatePR";
const std::string BFGS = "BFGS";
const std::string BFGS2 = "BFGS2";

const std::string Default = "Default";

} // namespace AlgorithmNames

//! Various name constants used in fit library.

namespace OptionNames {
const std::string Strategy = "Strategy";
const std::string ErrorDef = "ErrorDef";
const std::string Tolerance = "Tolerance";
const std::string Precision = "Precision";
const std::string PrintLevel = "PrintLevel";
const std::string MaxFunctionCalls = "MaxFunctionCalls";
const std::string MaxIterations = "MaxIterations";
const std::string PopulationSize = "PopSize";
const std::string RandomSeed = "RandomSeed";
const std::string IterationTemp = "IterationsAtTemp";
const std::string StepSize = "StepSize";
const std::string BoltzmannK = "k";
const std::string BoltzmannInitT = "t_init";
const std::string BoltzmannMu = "mu";
const std::string BoltzmannTmin = "t_min";

} // namespace OptionsNames

#endif // MINIMIZERCONSTANTS_H
