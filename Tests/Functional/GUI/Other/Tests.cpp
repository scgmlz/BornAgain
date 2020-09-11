// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/Other/Tests.cpp
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/GUI/Other/SaveLoadProject.h"
#include "Tests/GTestWrapper/google_test.h"

class Other : public ::testing::Test
{
};

/* TODO restore
   currently times out, or when run interactively, writes:
     GUISaveLoadProject::run_job()
     QEventLoop: Cannot be used without QApplication

TEST_F(Other, SaveLoad)
{
    EXPECT_TRUE(GUISaveLoadProject().runTest());
}
*/
