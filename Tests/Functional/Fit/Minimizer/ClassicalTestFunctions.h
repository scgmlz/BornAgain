// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/Minimizer/ClassicalTestFunctions.h
//! @brief     Declares set of ObjectiveTestFunctions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_CLASSICALTESTFUNCTIONS_H
#define BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_CLASSICALTESTFUNCTIONS_H

#include "Wrap/WinDllMacros.h"
#include <vector>

//! @class StandaloneFitTest
//! @ingroup standard_samples
//! @brief Collection of objective functions for minimization library testing.
//! Borrowed from StressFit test framework of http://root.cern.ch.

namespace TestFunctions
{
BA_CORE_API_ double RosenBrock(const std::vector<double>& par);
BA_CORE_API_ double WoodFour(const std::vector<double>& par);
BA_CORE_API_ double DecayingSin(double x, const std::vector<double>& par);
} // namespace TestFunctions

#endif // BORNAGAIN_TESTS_FUNCTIONAL_FIT_MINIMIZER_CLASSICALTESTFUNCTIONS_H
