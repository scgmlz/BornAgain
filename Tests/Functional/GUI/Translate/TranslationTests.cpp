// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/Translate/TranslationTests.cpp
//! @brief     Defines classes from TranslationCases family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/GUI/Translate/GUITranslationTest.h"
#include "Tests/GTestWrapper/google_test.h"

class Translate : public ::testing::Test
{
};

bool run(const std::string& sim_name, const std::string& sample_name)
{
    return GUITranslationTest(sim_name, sample_name).runTest();
}

TEST_F(Translate, Basic)
{
    EXPECT_TRUE(run("BasicGISAS", "CylindersAndPrismsBuilder"));
}

TEST_F(Translate, RadialPara)
{
    EXPECT_TRUE(run("BasicGISAS", "RadialParaCrystalBuilder"));
}

TEST_F(Translate, HardDisk)
{
    EXPECT_TRUE(run("BasicGISAS", "HardDiskBuilder"));
}

TEST_F(Translate, HexPara)
{
    EXPECT_TRUE(run("BasicGISAS", "HexParaCrystalBuilder"));
}

TEST_F(Translate, CoreShell)
{
    EXPECT_TRUE(run("BasicGISAS", "CoreShellParticleBuilder"));
}

TEST_F(Translate, Roughness)
{
    EXPECT_TRUE(run("BasicGISAS", "MultiLayerWithRoughnessBuilder"));
}

TEST_F(Translate, SquareLattice)
{
    EXPECT_TRUE(run("BasicGISAS", "SquareLatticeBuilder"));
}

TEST_F(Translate, Rotation)
{
    EXPECT_TRUE(run("BasicGISAS", "RotatedPyramidsBuilder"));
}

TEST_F(Translate, SizeDistribution)
{
    EXPECT_TRUE(run("BasicGISAS", "CylindersWithSizeDistributionBuilder"));
}

TEST_F(Translate, Composition)
{
    EXPECT_TRUE(run("BasicGISAS", "ParticleCompositionBuilder"));
}

TEST_F(Translate, Para2D)
{
    EXPECT_TRUE(run("BasicGISAS", "Basic2DParaCrystalBuilder"));
}

TEST_F(Translate, Lattice1D)
{
    EXPECT_TRUE(run("BasicGISAS", "Lattice1DBuilder"));
}

TEST_F(Translate, Lattice2D)
{
    EXPECT_TRUE(run("BasicGISAS", "Basic2DLatticeBuilder"));
}

TEST_F(Translate, TwoLayerRoughness)
{
    EXPECT_TRUE(run("BasicGISAS", "TwoLayerRoughnessBuilder"));
}

TEST_F(Translate, MesoCrystal)
{
    EXPECT_TRUE(run("BasicGISAS", "MesoCrystalBuilder"));
}

TEST_F(Translate, MagneticSpheres)
{
    EXPECT_TRUE(run("BasicPolarizedGISAS", "MagneticSpheresBuilder"));
}
