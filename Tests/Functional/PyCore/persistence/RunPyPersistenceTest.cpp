// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/PyCore/persistence/RunPyPersistenceTest.cpp
//! @brief     Implements program PyPersistenceStandardTest, to run functional tests
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyPersistenceTest.h"
#include <cstdlib>
#include <iostream>
#include <string>

//! Runs persistence test on a Python script, which writes output to PYPERSIST_OUT_DIR.
//!   (in principle, it would work with any other program as well, but currently
//!    PyPersistenceTest::runTest adds an extension .py, which has been removed
//!    upstream by the persistence/CMakeLists.txt).

int main(int argc, char** argv)
{
    if(argc<4){
        std::cout
            << "Usage: " << argv[0] << " <directory> <script name> <tolerance>\n"
            << "  where <script name> is the stem without extension '.py'\n";
        std::exit(1);
    }
    PyPersistenceTest test(argv[1], argv[2], std::stod(argv[3]));
    return test.runTest() ? 0 : 1;
}
