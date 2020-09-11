// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/Consistence/macros.cpp
//! @brief     Implements Core standard tests through gtest macros.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/GTestWrapper/google_test.h"
#include <string>

int compare(const std::string& name0, const std::string& name1, const double limit);

class Consistence : public ::testing::Test
{
};

TEST_F(Consistence, SpecularWithSlicing)
{
    EXPECT_TRUE(compare("SpecularWithSlicing_01", "SpecularWithSlicing_02", 2e-10));
    EXPECT_TRUE(compare("SpecularWithSlicing_01", "SpecularWithSlicing_03", 2e-10));
}

TEST_F(Consistence, InstrumentDefinitionComparison)
{
    EXPECT_TRUE(
        compare("InstrumentDefinitionComparison_0", "InstrumentDefinitionComparison_Q", 2e-10));
}

TEST_F(Consistence, TOFResolutionComparison)
{
    EXPECT_TRUE(compare("TOFResolutionComparison_TP", "TOFResolutionComparison_TR", 2e-10));
}

TEST_F(Consistence, PolarizedQAngleReflectivity)
{
    EXPECT_TRUE(
        compare("PolarizedQAngleReflectivityPP_0", "PolarizedQAngleReflectivityPP_Q", 2e-10));
    EXPECT_TRUE(
        compare("PolarizedQAngleReflectivityMM_0", "PolarizedQAngleReflectivityMM_Q", 2e-10));
}
