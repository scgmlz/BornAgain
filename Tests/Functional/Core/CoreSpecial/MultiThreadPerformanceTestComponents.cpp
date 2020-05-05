// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Core/CoreSpecial/MultiThreadPerformanceTestComponents.h
//! @brief     Defines TestComponents namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "MultiThreadPerformanceTestComponents.h"
#include "CylindersBuilder.h"
#include "Distributions.h"
#include "FormFactorFullSphere.h"
#include "GISASSimulation.h"
#include "InterferenceFunction2DLattice.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MultiLayer.h"
#include "ParameterPattern.h"
#include "Particle.h"
#include "ParticleDistribution.h"
#include "ParticleLayout.h"
#include "Rectangle.h"
#include "RectangularDetector.h"
#include "Units.h"

namespace
{

//! Returns multilayer spheres distribution at lattice points.
std::unique_ptr<MultiLayer> createSampleSpheresDistribution(int nspheres)
{
    auto material_1 = HomogeneousMaterial("example06_Air", 0.0, 0.0);
    auto material_2 = HomogeneousMaterial("example08_Particle", 0.0006, 2e-08);
    auto material_3 = HomogeneousMaterial("example06_Substrate", 6e-06, 2e-08);

    Layer layer_1(material_1);
    Layer layer_2(material_3);

    FormFactorFullSphere formFactor_1(10.0 * Units::nm);
    Particle particle_1(material_2, formFactor_1);

    DistributionGaussian distr_1(10.0 * Units::nm, 1.0 * Units::nm);
    ParameterDistribution par_distr_1("/Particle/FullSphere/Radius", distr_1, nspheres, 4.71,
                                      RealLimits::limited(5.0 * Units::nm, 15.0 * Units::nm));
    ParticleDistribution particleDistribution_1(particle_1, par_distr_1);

    InterferenceFunction2DLattice interference_1(10.0 * Units::nm, 10.0 * Units::nm,
                                                 90.0 * Units::deg, 0.0 * Units::deg);
    FTDecayFunction2DCauchy interference_1_pdf(47.7464829276 * Units::nm, 15.9154943092 * Units::nm,
                                               0.0 * Units::deg);
    interference_1.setDecayFunction(interference_1_pdf);

    ParticleLayout layout_1;
    layout_1.addParticle(particleDistribution_1, 1.0);
    layout_1.setInterferenceFunction(interference_1);
    layout_1.setWeight(1);
    layout_1.setTotalParticleSurfaceDensity(0.01);

    layer_1.addLayout(layout_1);

    auto multiLayer_1 = std::make_unique<MultiLayer>();
    multiLayer_1->addLayer(layer_1);
    multiLayer_1->addLayer(layer_2);
    return multiLayer_1;
}

//! Creates realistic GISAS simulation (without sample).
//! Rectangular PILATUS detector 981x1043, ROI and masks.

std::unique_ptr<Simulation> CreateRealisticGISASSimulation()
{
    auto result = std::make_unique<GISASSimulation>();
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::degree, 0.0 * Units::degree);

    // define detector
    const int pilatus_npx{981}, pilatus_npy{1043};
    const double pilatus_pixel_size{0.172};
    const double detector_distance{1730.0};
    const double beam_xpos{597.1}, beam_ypos{0.0};
    RectangularDetector detector(pilatus_npx, pilatus_npx * pilatus_pixel_size, pilatus_npy,
                                 pilatus_npy * pilatus_pixel_size);
    const double u0 = beam_xpos * pilatus_pixel_size;
    const double v0 = beam_ypos * pilatus_pixel_size;
    detector.setPerpendicularToDirectBeam(detector_distance, u0, v0);
    result->setDetector(detector);
    // define ROI and masks
    result->setRegionOfInterest(45.0, 35.0, 120.0, 120.0);
    result->addMask(Rectangle(100, 60, 110, 100));
    return std::unique_ptr<Simulation>(result.release());
}

} // namespace

//! Creates simulation representing simple GISAS.
//! Spherical detector 100x100, cylinders in DWBA.
//! Intended to study the performance of "real time" parameter tuning in GUI.

std::unique_ptr<Simulation> TestComponents::CreateSimpleGISAS()
{
    auto result = std::make_unique<GISASSimulation>();
    result->setDetectorParameters(100, 0.0 * Units::degree, 2.0 * Units::degree, 100,
                                  0.0 * Units::degree, 2.0 * Units::degree);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::degree, 0.0 * Units::degree);

    auto sample = std::unique_ptr<MultiLayer>(CylindersInDWBABuilder().buildSample());
    result->setSample(*sample);
    return std::unique_ptr<Simulation>(result.release());
}

//! Creates simulation representing realistic GISAS.
//! Intended to study the performance of some real life experiment.

std::unique_ptr<Simulation> TestComponents::CreateRealisticGISAS()
{
    auto result = CreateRealisticGISASSimulation();
    auto sample = std::unique_ptr<MultiLayer>(CylindersInDWBABuilder().buildSample());
    result->setSample(*sample);
    return result;
}

//! Creates simulation representing realistic GISAS.
//! Rectangular PILATUS detector 981x1043, truncated spheres with size distribution at lattice,
//! ROI and masks, noise, background.
//! Intended to study the performance of some real life experiment.

std::unique_ptr<Simulation> TestComponents::CreateRealisticAndHeavyGISAS()
{
    auto result = CreateRealisticGISASSimulation();
    auto sample = createSampleSpheresDistribution(50);
    result->setSample(*sample);
    return result;
}

//! Creates simulation representing GISAS with gigantic detector.
//! Spherical detector 2048x2048, cylinders in BA.
//! Intended to study the influence of SimulationElements and IPixel constructions on overall
//! performance.

std::unique_ptr<Simulation> TestComponents::CreateGiganticGISAS()
{
    const int nbins = 2048;
    auto result = std::make_unique<GISASSimulation>();
    result->setDetectorParameters(nbins, -2.0 * Units::degree, 2.0 * Units::degree, nbins,
                                  0.0 * Units::degree, 2.0 * Units::degree);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::degree, 0.0 * Units::degree);
    auto sample = std::unique_ptr<MultiLayer>(CylindersInBABuilder().buildSample());
    result->setSample(*sample);
    return std::unique_ptr<Simulation>(result.release());
}

//! Creates simulation representing GISAS with huge wavelength.
//! Tiny spherical detector 64x64, cylinders in BA, huge wavelength.
//! Intended to study parameter distribution in Simulation::runSingleSimulation context.

std::unique_ptr<Simulation> TestComponents::CreateWavelengthGISAS()
{
    const int nbins = 64;
    auto result = std::make_unique<GISASSimulation>();
    result->setDetectorParameters(nbins, -2.0 * Units::degree, 2.0 * Units::degree, nbins,
                                  0.0 * Units::degree, 2.0 * Units::degree);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::degree, 0.0 * Units::degree);

    // create parameter distribution
    DistributionLogNormal wavelength_distr(1.0 * Units::angstrom, 0.1);
    ParameterPattern pattern1;
    pattern1.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Wavelength);
    result->addParameterDistribution(pattern1.toStdString(), wavelength_distr, 1000);

    auto sample = std::unique_ptr<MultiLayer>(CylindersInBABuilder().buildSample());
    result->setSample(*sample);
    return std::unique_ptr<Simulation>(result.release());
}

//! Creates simulation representing simple GISAS with MonteCarlo ON.
//! Spherical detector 100x100, cylinders in DWBA.
//! Intended to study the performance in MonteCarlo mode.

std::unique_ptr<Simulation> TestComponents::CreateMCGISAS()
{
    auto result = std::make_unique<GISASSimulation>();
    result->setDetectorParameters(100, 0.0 * Units::degree, 2.0 * Units::degree, 100,
                                  0.0 * Units::degree, 2.0 * Units::degree);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::degree, 0.0 * Units::degree);

    auto sample = createSampleSpheresDistribution(10);
    result->setSample(*sample);
    result->getOptions().setMonteCarloIntegration(true, 50);
    return std::unique_ptr<Simulation>(result.release());
}
