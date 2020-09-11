// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Std/Run.h
//! @brief     Declares function run for use in standard tests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_FUNCTIONAL_STD_RUN_H
#define BORNAGAIN_TESTS_FUNCTIONAL_STD_RUN_H

#include <string>

int run(const std::string& test_name, const std::string& sim_name,
        const std::string& sample_builder_name, const double limit);

#endif // BORNAGAIN_TESTS_FUNCTIONAL_STD_RUN_H
