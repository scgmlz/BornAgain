// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/TranslationCases.cpp
//! @brief     Defines classes from TranslationCases family.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "TranslationCases.h"

BasicTranslationTest::BasicTranslationTest()
    : GUITranslationTest("BasicGISAS", "CylindersAndPrismsBuilder")
{
}

BasicTranslationTest::~BasicTranslationTest() = default;

RadialParaTranslationTest::RadialParaTranslationTest()
    : GUITranslationTest("BasicGISAS", "RadialParaCrystalBuilder")
{
}

RadialParaTranslationTest::~RadialParaTranslationTest() = default;

HardDiskTranslationTest::HardDiskTranslationTest()
    : GUITranslationTest("BasicGISAS", "HardDiskBuilder")
{
}

HardDiskTranslationTest::~HardDiskTranslationTest() = default;

HexParaTranslationTest::HexParaTranslationTest()
    : GUITranslationTest("BasicGISAS", "HexParaCrystalBuilder")
{
}

HexParaTranslationTest::~HexParaTranslationTest() = default;

CoreShellTranslationTest::CoreShellTranslationTest()
    : GUITranslationTest("BasicGISAS", "CoreShellParticleBuilder")
{
}

CoreShellTranslationTest::~CoreShellTranslationTest() = default;

RoughnessTranslationTest::RoughnessTranslationTest()
    : GUITranslationTest("BasicGISAS", "MultiLayerWithRoughnessBuilder")
{
}

RoughnessTranslationTest::~RoughnessTranslationTest() = default;

SquareLatticeTranslationTest::SquareLatticeTranslationTest()
    : GUITranslationTest("BasicGISAS", "SquareLatticeBuilder")
{
}

SquareLatticeTranslationTest::~SquareLatticeTranslationTest() = default;

RotationTranslationTest::RotationTranslationTest()
    : GUITranslationTest("BasicGISAS", "RotatedPyramidsBuilder")
{
}

RotationTranslationTest::~RotationTranslationTest() = default;

SizeDistributionTranslationTest::SizeDistributionTranslationTest()
    : GUITranslationTest("BasicGISAS", "CylindersWithSizeDistributionBuilder")
{
}

SizeDistributionTranslationTest::~SizeDistributionTranslationTest() = default;

CompositionTranslationTest::CompositionTranslationTest()
    : GUITranslationTest("BasicGISAS", "ParticleCompositionBuilder")
{
}

CompositionTranslationTest::~CompositionTranslationTest() = default;

Para2DTranslationTest::Para2DTranslationTest()
    : GUITranslationTest("BasicGISAS", "Basic2DParaCrystalBuilder")
{
}

Para2DTranslationTest::~Para2DTranslationTest() = default;

Lattice1DTranslationTest::Lattice1DTranslationTest()
    : GUITranslationTest("BasicGISAS", "Lattice1DBuilder")
{
}

Lattice1DTranslationTest::~Lattice1DTranslationTest() = default;

Lattice2DTranslationTest::Lattice2DTranslationTest()
    : GUITranslationTest("BasicGISAS", "Basic2DLatticeBuilder")
{
}

Lattice2DTranslationTest::~Lattice2DTranslationTest() = default;

TwoLayerRoughnessTranslationTest::TwoLayerRoughnessTranslationTest()
    : GUITranslationTest("BasicGISAS", "TwoLayerRoughnessBuilder")
{
}

TwoLayerRoughnessTranslationTest::~TwoLayerRoughnessTranslationTest() = default;

MesoCrystalTranslationTest::MesoCrystalTranslationTest()
    : GUITranslationTest("BasicGISAS", "MesoCrystalBuilder")
{
}

MesoCrystalTranslationTest::~MesoCrystalTranslationTest() = default;

MagneticSpheresTranslationTest::MagneticSpheresTranslationTest()
    : GUITranslationTest("BasicPolarizedGISAS", "MagneticSpheresBuilder")
{
}

MagneticSpheresTranslationTest::~MagneticSpheresTranslationTest() = default;
