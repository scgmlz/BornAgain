// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/StandardSimulationsRegistry.cpp
//! @brief     Implements class StandardSimulationsRegistry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StandardSimulationsRegistry.h"
#include "Exceptions.h"
#include "StringUtils.h"

StandardSimulationsRegistry::StandardSimulationsRegistry()
{
    add("FormFactors",
        "Test of all form factors defined",
        "MiniGISAS",
        "ParticleInTheAirBuilder",
        "FormFactors",
        2e-10);

    add("FormFactorsAbs",
        "Test of all form factors defined, absorption case",
        "MiniGISAS_v2",
        "LayersWithAbsorptionBuilder",
        "FormFactors",
        2e-10);

    add("CylindersAndPrisms",
        "Mixture of cylinders and prisms without interference",
        "MiniGISAS",
        "CylindersAndPrismsBuilder",
        "None",
        2e-10);

    add("RadialParaCrystal",
        "Interference function of radial paracrystal",
        "MiniGISAS",
        "RadialParaCrystalBuilder",
        "None",
        2e-10);

    add("Basic2DParaCrystal",
        "Interference function of basic 2D paracrystal with variety of FT distributions",
        "MiniGISAS",
        "Basic2DParaCrystalBuilder",
        "FTDistributions2D",
        2e-10);

    add("HexParaCrystal",
        "Interference function of 2D hexagonal paracrystal",
        "MiniGISAS",
        "HexParaCrystalBuilder",
        "None",
        2e-10);

    add("Lattice1D",
        "Interference function of 21D lattice",
        "MiniGISAS",
        "Lattice1DBuilder",
        "None",
        2e-10);

    add("RectParaCrystal",
        "Interference function of 2D rectanguler paracrystal",
        "MiniGISAS",
        "RectParaCrystalBuilder",
        "None",
        2e-10);

    // --- CoreShell ---

    add("CoreShellParticle",
        "Core shell particle",
        "MiniGISAS",
        "CoreShellParticleBuilder",
        "None",
        2e-10);

    add("CoreShellBoxRotateZandY",
        "Rotation and translation of core shell box particle in 3 layers system",
        "MiniGISAS",
        "CoreShellBoxRotateZandYBuilder",
        "None",
        2e-10);

    // ---

    add("MultiLayerWithRoughness",
        "Multilayer with roughness",
        "MiniGISAS",
        "MultiLayerWithRoughnessBuilder",
        "None",
        2e-10);

    add("SquareLattice",
        "Interference function of 2D square lattice",
        "MiniGISAS",
        "SquareLatticeBuilder",
        "None",
        2e-10);

    add("CenteredSquareLattice",
        "Interference function of 2D square lattice",
        "MiniGISAS",
        "CenteredSquareLatticeBuilder",
        "None",
        2e-10);

    add("RotatedSquareLattice",
        "Interference function of rotated 2D square lattice",
        "MiniGISAS",
        "RotatedSquareLatticeBuilder",
        "None",
        2e-10);

    add("RotatedPyramids",
        "Interference function of rotated 2D square lattice",
        "MiniGISAS",
        "RotatedPyramidsBuilder",
        "None",
        2e-10);

    // --- Compositions ---

    add("ParticleComposition",
        "Two layers of spheres at hex lattice",
        "MiniGISAS",
        "ParticleCompositionBuilder",
        "None",
        2e-10);

    add("BoxCompositionRotateX",
        "Two boxes in particle composition rotated in X by 90 degrees",
        "MiniGISAS",
        "BoxCompositionRotateXBuilder",
        "None",
        2e-10);

    add("BoxCompositionRotateY",
        "Two boxes in particle composition rotated in Y by 90 degrees",
        "MiniGISAS",
        "BoxCompositionRotateYBuilder",
        "None",
        2e-10);

    add("BoxCompositionRotateZ",
        "Two boxes in particle composition rotated in Z by 90 degrees",
        "MiniGISAS",
        "BoxCompositionRotateZBuilder",
        "None",
        2e-10);

    add("BoxCompositionRotateZandY",
        "Two boxes in particle composition rotated in Z and Y by 90 degrees",
        "MiniGISAS",
        "BoxCompositionRotateZandYBuilder",
        "None",
        2e-10);

    add("BoxStackComposition",
        "Two different boxes are first rotated and then composed, composition is then rotated.",
        "MiniGISAS",
        "BoxStackCompositionBuilder",
        "None",
        2e-10);

    // ---

    add("CylindersWithSizeDistribution",
        "Cylinders in BA with size distributions",
        "MiniGISAS",
        "CylindersWithSizeDistributionBuilder",
        "None",
        2e-10);

    add("TwoTypesCylindersDistribution",
        "Cylinders in BA with size distributions",
        "MiniGISAS",
        "TwoTypesCylindersDistributionBuilder",
        "None",
        2e-10);

    add("BeamDivergence",
        "Cylinders in BA in the presence of beam divergence",
        "MiniGISASBeamDivergence",
        "CylindersInBABuilder",
        "None",
        2e-10);

    add("DetectorResolution",
        "Cylinders in BA with detector resolution",
        "MiniGISASDetectorResolution",
        "CylindersInBABuilder",
        "None",
        2e-10);

    add("MultipleLayout",
        "Two types of particles in different layouts",
        "MiniGISAS",
        "MultipleLayoutBuilder",
        "None",
        2e-10);

    add("ApproximationDA",
        "Size distribution model: decoupling approximation",
        "MiniGISAS",
        "SizeDistributionDAModelBuilder",
        "None",
        2e-10);

    add("ApproximationLMA",
        "Size distribution model: local monodisperse approximation",
        "MiniGISAS",
        "SizeDistributionLMAModelBuilder",
        "None",
        2e-10);

    add("ApproximationSSCA",
        "Size distribution model: size space coupling approximation",
        "MiniGISAS",
        "SizeDistributionSSCAModelBuilder",
        "None",
        2e-10);

    add("CylindersInSSCA",
        "Size spacing correlation approximation",
        "MiniGISAS",
        "CylindersInSSCABuilder",
        "None",
        2e-10);

    add("CosineRipple",
        "Cosine ripple within radial paracrystal model",
        "MiniGISAS",
        "CosineRippleBuilder",
        "None",
        2e-10);

    add("TriangularRipple",
        "Triangular ripple within radial paracrystal model",
        "MiniGISAS",
        "TriangularRippleBuilder",
        "None",
        2e-10);

    add("MesoCrystal",
        "Cylindrical mesocrystal composed of spherical nano particles",
        "MiniGISAS",
        "MesoCrystalBuilder",
        "None",
        2e-10);

    add("CustomMorphology",
        "Custom particle mixture a la isgisaxs morphology approach",
        "MiniGISAS",
        "CustomMorphologyBuilder",
        "None",
        2e-10);

    add("MagneticParticleZeroField",
        "Magnetic cylinders with zero field",
        "MiniGISAS",
        "MagneticParticleZeroFieldBuilder",
        "None",
        2e-10);

    add("TransformBox",
        "Rotated/translated box in 3 layers system",
        "MiniGISAS",
        "TransformBoxBuilder",
        "None",
        1e-10);

    // Masking

    add("SimulationWithMasks",
        "Various masks are added to the simulation",
        "GISASWithMasks",
        "CylindersAndPrismsBuilder",
        "None",
        1e-10);

    // Various rectangular detector alignment

    add("RectDetectorGeneric",
        "Various masks are added to the simulation",
        "RectDetectorGeneric",
        "CylindersInBABuilder",
        "None",
        1e-10);

    add("RectDetectorPerpToSample",
        "Various masks are added to the simulation",
        "RectDetectorPerpToSample",
        "CylindersInBABuilder",
        "None",
        1e-10);

    add("RectDetectorPerpToDirectBeam",
        "Various masks are added to the simulation",
        "RectDetectorPerpToDirectBeam",
        "CylindersInBABuilder",
        "None",
        1e-10);

    add("RectDetectorPerpToReflectedBeam",
        "Various masks are added to the simulation",
        "RectDetectorPerpToReflectedBeam",
        "CylindersInBABuilder",
        "None",
        1e-10);

    add("RectDetectorPerpToReflectedBeamDpos",
        "Various masks are added to the simulation",
        "RectDetectorPerpToReflectedBeamDpos",
        "CylindersInBABuilder",
        "None",
        1e-10);

    add("LargeCylindersMonteCarlo",
        "Large cylinders simulated with MonteCarlo integration",
        "MiniGISASMonteCarlo",
        "LargeCylindersInDWBABuilder",
        "None",
        5e-1);

    add("SphericalDetWithRoi",
        "Spherical detector with ROI and mask defined",
        "SphericalDetWithRoi",
        "CylindersAndPrismsBuilder",
        "None",
        1e-10);

    add("RectDetWithRoi",
        "Rectangular detector with ROI and mask defined",
        "RectDetWithRoi",
        "CylindersAndPrismsBuilder",
        "None",
        1e-10);
}

void StandardSimulationsRegistry::add(
    const std::string& test_name, const std::string& test_description,
    const std::string& simulation_name, const std::string& sample_builder_name,
    const std::string& subtest_type, double threshold )
{
    if( m_catalogue.find(test_name) != m_catalogue.end() )
        throw Exceptions::ExistingClassRegistrationException(
            "StandardSimulationsRegistry::add() -> Error. Existing item " + test_name);
    m_catalogue[test_name] = SimulationInfo(
        test_name, test_description, simulation_name,
        sample_builder_name, subtest_type, threshold);
}

const SimulationInfo* StandardSimulationsRegistry::getItemOrExplain(
    const std::string& test_name, const std::string& suite_name) const
{
    auto it = m_catalogue.find(test_name);
    if( it == m_catalogue.end() ) {
        if(test_name!="")
            std::cout<<"There is no test named '"<< test_name << "'\n";
        std::cout << "Usage: "<< suite_name << " <test_name>\n";
        std::cout << "Available tests:\n";
        printCatalogue(std::cout);
        return nullptr;
    }
    return &(it->second);
}

void StandardSimulationsRegistry::printCatalogue(std::ostream& ostr) const
{
    for(auto it = m_catalogue.begin(); it != m_catalogue.end(); ++it) {
        SimulationInfo info = it->second;
        ostr << StringUtils::padRight(info.m_test_name, 20) << " | ";
        ostr << StringUtils::padRight(info.m_test_description, 40) << " | ";
        ostr << info.m_simulation_name << ", ";
        ostr << info.m_sample_builder_name << ", ";
        ostr << info.m_subtest_type;
        ostr << "\n";
    }
}
