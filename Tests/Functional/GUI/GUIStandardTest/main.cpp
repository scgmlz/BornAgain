// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUIStandardTest/main.cpp
//! @brief     Implements program GUIStandardTest to run gui functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUIStandardTest.h"
#include "StandardTestService.h"
#include <iostream>

//! Runs GUIStandardTest on a standard simulation indicated by argv[1].

int main(int argc, char** argv)
{
    bool ok =  StandardTestService<GUIStandardTest>().execute(argc, argv);
    if (!ok)
        std::cout << "\n"
                  << "hint: If this test fails while all other form-factor related tests\n"
                  << "pass then a likely cause is a change in the form factor API that is\n"
                  << "not correctly reflected in the GUIDomainSampleVisitor class.\n\n";
    return ok ? 0 : 1;
}
