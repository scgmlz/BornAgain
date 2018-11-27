// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/GUISpecialTestFactory.cpp
//! @brief     Implements GUISpecialTestFactory class.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "GUISpecialTestFactory.h"
#include "CsvImportAssistantPerformanceTest.h"
#include "TranslationCases.h"
#include "GUIPerformanceTest.h"
#include "GUISaveLoadProject.h"

GUISpecialTestFactory::GUISpecialTestFactory()
{
    registerItem("BasicTranslation",
                 create_new<BasicTranslationTest>,
                 "BasicTranslation test");

    registerItem("RadialParaTranslation",
                 create_new<RadialParaTranslationTest>,
                 "RadialParaTranslation test");

    registerItem("HexParaTranslation",
                 create_new<HexParaTranslationTest>,
                 "HexParaTranslation test");

    registerItem("CoreShellTranslation",
                 create_new<CoreShellTranslationTest>,
                 "CoreShellTranslation test");

    registerItem("RoughnessTranslation",
                 create_new<RoughnessTranslationTest>,
                 "RoughnessTranslation test");

    registerItem("SquareLatticeTranslation",
                 create_new<SquareLatticeTranslationTest>,
                 "SquareLatticeTranslation test");

    registerItem("RotationTranslation",
                 create_new<RotationTranslationTest>,
                 "RotationTranslation test");

    registerItem("SizeDistributionTranslation",
                 create_new<SizeDistributionTranslationTest>,
                 "SizeDistributionTranslation test");

    registerItem("CompositionTranslation",
                 create_new<CompositionTranslationTest>,
                 "CompositionTranslation test");

    registerItem("Para2DTranslation",
                 create_new<Para2DTranslationTest>,
                 "Para2DTranslation test");

    registerItem("Lattice1DTranslation",
                 create_new<Lattice1DTranslationTest>,
                 "Lattice1DTranslation test");

    registerItem("Lattice2DTranslation",
                 create_new<Lattice2DTranslationTest>,
                 "Lattice2DTranslation test");

    registerItem("TwoLayerRoughnessTranslation",
                 create_new<TwoLayerRoughnessTranslationTest>,
                 "TwoLayerRoughnessTranslation test");

    registerItem("MesoCrystalTranslation",
                 create_new<MesoCrystalTranslationTest>,
                 "MesoCrystalTranslation test");

    registerItem("MagneticSpheresTranslation",
                 create_new<MagneticSpheresTranslationTest>,
                 "MagneticSpheresTranslation test");

    registerItem("GUIPerformance",
                 create_new<GUIPerformanceTest>,
                 "Measuring GUI performance on typical tasks.");

    registerItem("SaveLoadProject",
                 create_new<GUISaveLoadProject>,
                 "Save/load project test");
    registerItem("CsvImportAssistant",
                 create_new<CsvImportAssistantPerformanceTest>,
                 "Measuring performance of loading ascii files");
}
