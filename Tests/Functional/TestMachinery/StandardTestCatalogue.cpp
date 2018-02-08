// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/StandardTestCatalogue.cpp
//! @brief     Implements class StandardTestCatalogue.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "StandardTestCatalogue.h"
#include "StringUtils.h"
#include <iostream>

StandardTestCatalogue::StandardTestCatalogue()
{
    add("FormFactors",
        "Test of all form factors defined",
        "MiniGISAS",
        "ParticleInTheAirBuilder",
        2e-10);

    add("FormFactorsAbs",
        "Test of all form factors defined, absorption case",
        "MiniGISAS_v2",
        "LayersWithAbsorptionBuilder",
        2e-10);

    add("CylindersAndPrisms",
        "Mixture of cylinders and prisms without interference",
        "MiniGISAS",
        "CylindersAndPrismsBuilder",
        2e-10);

    add("RadialParaCrystal",
        "Interference function of radial paracrystal",
        "MiniGISAS",
        "RadialParaCrystalBuilder",
        2e-10);

    add("Basic2DParaCrystal",
        "Interference function of basic 2D paracrystal with variety of FT distributions",
        "MiniGISAS",
        "Basic2DParaCrystalBuilder",
        2e-10);

    add("HexParaCrystal",
        "Interference function of 2D hexagonal paracrystal",
        "MiniGISAS",
        "HexParaCrystalBuilder",
        2e-10);

    add("Lattice1D",
        "Interference function of 21D lattice",
        "MiniGISAS",
        "Lattice1DBuilder",
        2e-10);

    add("RectParaCrystal",
        "Interference function of 2D rectanguler paracrystal",
        "MiniGISAS",
        "RectParaCrystalBuilder",
        2e-10);

    // --- CoreShell ---

    add("CoreShellParticle",
        "Core shell particle",
        "MiniGISAS",
        "CoreShellParticleBuilder",
        2e-10);

    add("CoreShellBoxRotateZandY",
        "Rotation and translation of core shell box particle in 3 layers system",
        "MiniGISAS",
        "CoreShellBoxRotateZandYBuilder",
        2e-10);

    // ---

    add("MultiLayerWithRoughness",
        "Multilayer with roughness",
        "MiniGISAS",
        "MultiLayerWithRoughnessBuilder",
        2e-10);

    add("SquareLattice",
        "Interference function of 2D square lattice",
        "MiniGISAS",
        "SquareLatticeBuilder",
        2e-10);

    add("CenteredSquareLattice",
        "Interference function of 2D square lattice",
        "MiniGISAS",
        "CenteredSquareLatticeBuilder",
        2e-10);

    add("RotatedSquareLattice",
        "Interference function of rotated 2D square lattice",
        "MiniGISAS",
        "RotatedSquareLatticeBuilder",
        2e-10);

    add("RotatedPyramids",
        "Interference function of rotated 2D square lattice",
        "MiniGISAS",
        "RotatedPyramidsBuilder",
        2e-10);

    // --- Compositions ---

    add("ParticleComposition",
        "Two layers of spheres at hex lattice",
        "MiniGISAS",
        "ParticleCompositionBuilder",
        2e-10);

    add("BoxCompositionRotateX",
        "Two boxes in particle composition rotated in X by 90 degrees",
        "MiniGISAS",
        "BoxCompositionRotateXBuilder",
        2e-10);

    add("BoxCompositionRotateY",
        "Two boxes in particle composition rotated in Y by 90 degrees",
        "MiniGISAS",
        "BoxCompositionRotateYBuilder",
        2e-10);

    add("BoxCompositionRotateZ",
        "Two boxes in particle composition rotated in Z by 90 degrees",
        "MiniGISAS",
        "BoxCompositionRotateZBuilder",
        2e-10);

    add("BoxCompositionRotateZandY",
        "Two boxes in particle composition rotated in Z and Y by 90 degrees",
        "MiniGISAS",
        "BoxCompositionRotateZandYBuilder",
        2e-10);

    add("BoxStackComposition",
        "Two different boxes are first rotated and then composed, composition is then rotated.",
        "MiniGISAS",
        "BoxStackCompositionBuilder",
        2e-10);

    // ---

    add("CylindersWithSizeDistribution",
        "Cylinders in BA with size distributions",
        "MiniGISAS",
        "CylindersWithSizeDistributionBuilder",
        2e-10);

    add("TwoTypesCylindersDistribution",
        "Cylinders in BA with size distributions",
        "MiniGISAS",
        "TwoTypesCylindersDistributionBuilder",
        2e-10);

    add("RotatedPyramidsDistribution",
        "Rotated pyramids distribution",
        "MiniGISAS",
        "RotatedPyramidsDistributionBuilder",
        2e-10);

    add("SpheresWithLimitsDistribution",
        "Spherical particles with the distribution applied to the radius and RealLimits defined.",
        "MiniGISAS",
        "SpheresWithLimitsDistributionBuilder",
        2e-10);

    add("ConesWithLimitsDistribution",
        "Spherical particles with the distribution applied to the radius and RealLimits defined.",
        "MiniGISAS",
        "ConesWithLimitsDistributionBuilder",
        2e-10);

    // ---

    add("BeamDivergence",
        "Cylinders in BA in the presence of beam divergence",
        "MiniGISASBeamDivergence",
        "CylindersInBABuilder",
        2e-10);

    add("DetectorResolution",
        "Cylinders in BA with detector resolution",
        "MiniGISASDetectorResolution",
        "CylindersInBABuilder",
        2e-10);

    add("MultipleLayout",
        "Two types of particles in different layouts",
        "MiniGISAS",
        "MultipleLayoutBuilder",
        2e-10);

    add("ApproximationDA",
        "Size distribution model: decoupling approximation",
        "MiniGISAS",
        "SizeDistributionDAModelBuilder",
        2e-10);

    add("ApproximationLMA",
        "Size distribution model: local monodisperse approximation",
        "MiniGISAS",
        "SizeDistributionLMAModelBuilder",
        2e-10);

    add("ApproximationSSCA",
        "Size distribution model: size space coupling approximation",
        "MiniGISAS",
        "SizeDistributionSSCAModelBuilder",
        2e-10);

    add("CylindersInSSCA",
        "Size spacing correlation approximation",
        "MiniGISAS",
        "CylindersInSSCABuilder",
        2e-10);

    add("CosineRipple",
        "Cosine ripple within radial paracrystal model",
        "MiniGISAS",
        "CosineRippleBuilder",
        2e-10);

    add("TriangularRipple",
        "Triangular ripple within radial paracrystal model",
        "MiniGISAS",
        "TriangularRippleBuilder",
        2e-10);

    add("AsymRipple",
        "Triangular ripple with asymetry within radial paracrystal model",
        "MiniGISAS",
        "AsymRippleBuilder",
        2e-10);

    add("MesoCrystal",
        "Cylindrical mesocrystal composed of spherical nano particles",
        "MiniGISAS",
        "MesoCrystalBuilder",
        2e-10);

    add("CustomMorphology",
        "Custom particle mixture a la isgisaxs morphology approach",
        "MiniGISAS",
        "CustomMorphologyBuilder",
        2e-10);

    add("MagneticParticleZeroField",
        "Magnetic cylinders with zero field",
        "MiniGISAS",
        "MagneticParticleZeroFieldBuilder",
        2e-10);

    add("MagneticSubstrateZeroField",
        "Magnetic substrate with zero field",
        "MiniGISASPolarizationPP",
        "MagneticSubstrateZeroFieldBuilder",
        2e-10);

    add("MagneticRotation",
        "Rotated magnetic particle in magnetic substrate",
        "MiniGISASSpinFlipZ",
        "MagneticRotationBuilder",
        2e-10);

    add("MagneticSpheres",
        "Magnetic spheres inside substrate",
        "MiniGISASSpinFlipZ",
        "MagneticSpheresBuilder",
        2e-10);

    add("TransformBox",
        "Rotated/translated box in 3 layers system",
        "MiniGISAS",
        "TransformBoxBuilder",
        1e-10);

    // Masking

    add("SimulationWithMasks",
        "Various masks are added to the simulation",
        "GISASWithMasks",
        "CylindersAndPrismsBuilder",
        1e-10);

    // Various rectangular detector alignment

    add("RectDetectorGeneric",
        "Various masks are added to the simulation",
        "RectDetectorGeneric",
        "CylindersInBABuilder",
        1e-10);

    add("RectDetectorPerpToSample",
        "Various masks are added to the simulation",
        "RectDetectorPerpToSample",
        "CylindersInBABuilder",
        1e-10);

    add("RectDetectorPerpToDirectBeam",
        "Various masks are added to the simulation",
        "RectDetectorPerpToDirectBeam",
        "CylindersInBABuilder",
        1e-10);

    add("RectDetectorPerpToReflectedBeam",
        "Various masks are added to the simulation",
        "RectDetectorPerpToReflectedBeam",
        "CylindersInBABuilder",
        1e-10);

    add("RectDetectorPerpToReflectedBeamDpos",
        "Various masks are added to the simulation",
        "RectDetectorPerpToReflectedBeamDpos",
        "CylindersInBABuilder",
        1e-10);

    add("LargeCylindersMonteCarlo",
        "Large cylinders simulated with MonteCarlo integration",
        "MiniGISASMonteCarlo",
        "LargeCylindersInDWBABuilder",
        5e-1);

    add("SphericalDetWithRoi",
        "Spherical detector with ROI and mask defined",
        "SphericalDetWithRoi",
        "CylindersAndPrismsBuilder",
        1e-10);

    add("RectDetWithRoi",
        "Rectangular detector with ROI and mask defined",
        "RectDetWithRoi",
        "CylindersAndPrismsBuilder",
        1e-10);

    add("BoxesWithSpecular",
        "Boxes in square lattice including specular peak",
        "MiniGISASSpecular",
        "BoxesSquareLatticeBuilder",
        1e-10);

    add("RotatedCylinder",
        "Rotated cylinder in substrate",
        "MiniGISAS",
        "RotatedCylindersBuilder",
        1e-10);

    add("SlicedComposition",
        "Spherical particle made of two different materials crossing interface",
        "MiniGISAS",
        "SlicedCompositionBuilder",
        1e-10);

    // Simulations with background

    add("ConstantBackground",
        "Constant background is added to the simulation",
        "ConstantBackground",
        "CylindersInBABuilder",
        1e-10);

    // Specular simulations

    add("HomogeneousTiNiSample",
        "Specular simulation for 10 interchanging Ti-Ni homogeneous layers",
        "BasicSpecular",
        "HomogeneousMultilayerBuilder",
        1e-10);

    add("HomogeneousTiNiSampleWithAbsorption",
        "Specular simulation for 10 interchanging Ti-Ni homogeneous "
            "layers with absorptive SLD material (exaggerated absorption for Ti)",
        "BasicSpecular",
        "MaterialBySLDBuilder",
        1e-10);

    add("RoughnessInSpecular",
        "Specular simulation with rough sample",
        "BasicSpecular",
        "MultiLayerWithRoughnessBuilder",
        2e-9);

    add("GaussianBeamFootprint",
        "Similar to HomogeneousTiNiSample, but with finite-sized gaussian beam",
        "SpecularWithGaussianBeam",
        "HomogeneousMultilayerBuilder",
        1e-10);

    add("SquareBeamFootprint",
        "Similar to HomogeneousTiNiSample, but with finite-sized square beam",
        "SpecularWithSquareBeam",
        "HomogeneousMultilayerBuilder",
        1e-10);

    add("SpecularDivergentBeam",
        "Simulates beam divergence both in wavelength and inclination angle",
        "SpecularDivergentBeam",
        "HomogeneousMultilayerBuilder",
        1e-10);

    add("OffSpecularResonator",
        "Simulates resonator in OffSpec setup",
        "OffSpecMini",
        "ResonatorBuilder",
        1e-10);
}

//! Adds test description to the catalogue.

void StandardTestCatalogue::add(const std::string& test_name, const std::string& test_description,
    const std::string& simulation_name, const std::string& sample_builder_name,
    double threshold )
{
    if (contains(test_name))
        throw std::runtime_error("StandardTestCatalogue::add() -> Error. "
                                 "Existing item '"+test_name+"'");

    m_catalogue[test_name] = StandardTestInfo(test_name, test_description, simulation_name,
                                              sample_builder_name, threshold);
}

//! Returns test info for given test name.

StandardTestInfo StandardTestCatalogue::testInfo(const std::string& test_name)
{
    if (!contains(test_name))
        throw std::runtime_error("StandardTestCatalogue::testInfo() -> Error. No info for "
                                 "given name '"+test_name+"'");

    return m_catalogue[test_name];
}

//! Returns true if catalogue contains info for test with given name.

bool StandardTestCatalogue::contains(const std::string& test_name)
{
    return m_catalogue.find( test_name ) != m_catalogue.end();
}

void StandardTestCatalogue::printCatalogue(std::ostream& ostr) const
{
    for (auto it : m_catalogue) {
        ostr << StringUtils::padRight(it.second.m_test_name, 40) << " | ";
        ostr << StringUtils::padRight(it.second.m_test_description, 65) << "\n";
    }
}
