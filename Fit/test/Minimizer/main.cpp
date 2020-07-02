// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/test/Minimizer/main.cpp
//! @brief     Implements program FitTest to run fit functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MinimizerTestFactory.h"
#include "TestService.h"

//! Runs functional tests.

int main(int argc, char** argv)
{
    return TestService<MinimizerTestFactory>().execute(argc, argv) ? 0 : 1;
}
