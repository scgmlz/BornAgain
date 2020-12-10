//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/GTestWrapper/TestAll.cpp
//! @brief     Implements main, for use in various test directories.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Tests/GTestWrapper/google_test.h"

//! Main program for use in various test directories.
//!
//! We need this function instead of gtest_main [1] because we want to use our
//! wrapper google_test.h instead of gtest.h.
//!
//! We compile this function separately in each test directory, and link it with
//! source files that contain TEST_F macros.
//!
//! [1] https://github.com/google/googletest/blob/master/googletest/docs/primer.md
//!     #writing-the-main-function

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // run all google tests
    return RUN_ALL_TESTS();
}
