// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/main.cpp
//! @brief     Implements program to run tests from CoreSpecialTestFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "TestService.h"
#include "CoreSpecialTestFactory.h"

//! Runs PyEmbedded functional test.
int main(int argc, char** argv)
{
    return TestService<CoreSpecialTestFactory>().execute(argc, argv) ? 0 : 1;
}
