//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Core/Simulation/StandardSimulations.cpp
//! @brief     Implements functions for standard simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Simulation/StandardSimulations.h"
#include "Base/Const/Units.h"
#include "Core/Computation/ConstantBackground.h"
#include "Core/Scan/AngularSpecScan.h"
#include "Core/Scan/QSpecScan.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecularSimulation.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Device/Beam/FootprintGauss.h"
#include "Device/Beam/FootprintSquare.h"
#include "Device/Detector/IsGISAXSDetector.h"
#include "Device/Detector/RectangularDetector.h"
#include "Device/Mask/Ellipse.h"
#include "Device/Mask/Line.h"
#include "Device/Mask/Polygon.h"
#include "Device/Mask/Rectangle.h"
#include "Device/Resolution/ResolutionFunction2DGaussian.h"
#include "Device/Resolution/ScanResolution.h"
#include "Param/Base/RealParameter.h"
#include "Param/Distrib/Distributions.h"
#include "Param/Distrib/RangedDistributions.h"
#include "Param/Varia/ParameterPattern.h"
#include "Sample/StandardSamples/SampleBuilderFactory.h"
#include <memory>

namespace {

const size_t rdet_nbinsx(40), rdet_nbinsy(30);
const double rdet_width(20.0), rdet_height(18.0), rdet_distance(1000.0);

} // namespace

using Units::angstrom;
using Units::deg;

//! Basic GISAS simulation with the detector phi[0,2], theta[0,2].

GISASSimulation* StandardSimulations::BasicGISAS()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    SphericalDetector det(100, 0 * deg, 2 * deg, 100, 0 * deg, 2 * deg);
    return new GISASSimulation(beam, det);
}

//! Basic GISAS for polarization studies.

GISASSimulation* StandardSimulations::BasicGISAS00()
{
    GISASSimulation* result = BasicGISAS();
    kvector_t zplus(0.0, 0.0, 1.0);
    result->beam().setPolarization(zplus);
    result->detector().setAnalyzerProperties(zplus, 1.0, 0.5);
    return result;
}

//! Basic GISAS simulation for spin flip channel.

GISASSimulation* StandardSimulations::BasicPolarizedGISAS()
{
    GISASSimulation* result = BasicGISAS();
    kvector_t zplus(0.0, 0.0, 1.0);
    result->beam().setPolarization(zplus);
    result->detector().setAnalyzerProperties(zplus, -1.0, 0.5);
    return result;
}

//! GISAS simulation with small detector and phi[-2,2], theta[0,2].

GISASSimulation* StandardSimulations::MiniGISAS()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    SphericalDetector det(25, -2 * deg, 2 * deg, 25, 0 * deg, 2 * deg);
    return new GISASSimulation(beam, det);
}

//! GISAS simulation with small detector and phi[-1,1], theta[0,1].

GISASSimulation* StandardSimulations::MiniGISAS_v2()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    SphericalDetector det(25, -1 * deg, 1 * deg, 25, 0 * deg, 1 * deg);
    return new GISASSimulation(beam, det);
}

//! GISAS simulation with beam divergence applied.

GISASSimulation* StandardSimulations::MiniGISASBeamDivergence()
{
    GISASSimulation* result = MiniGISAS();

    DistributionLogNormal wavelength_distr(1 * angstrom, 0.1);
    DistributionGaussian alpha_distr(0.2 * deg, 0.02 * deg);
    DistributionGate phi_distr(-0.1 * deg, 0.02 * deg);

    ParameterPattern pattern1;
    pattern1.beginsWith("*").add("Beam").add("Wavelength");
    result->addParameterDistribution(pattern1.toStdString(), wavelength_distr, 5);
    ParameterPattern pattern2;
    pattern2.beginsWith("*").add("Beam").add("InclinationAngle");
    result->addParameterDistribution(pattern2.toStdString(), alpha_distr, 4);
    ParameterPattern pattern3;
    pattern3.beginsWith("*").add("Beam").add("AzimuthalAngle");
    result->addParameterDistribution(pattern3.toStdString(), phi_distr, 3);

    return result;
}

//! GISAS simulation with multiple masks on the detector plane.

GISASSimulation* StandardSimulations::GISASWithMasks()
{
    Beam beam(1e7, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    SphericalDetector det(50, -1 * deg, 1 * deg, 50, 0 * deg, 2 * deg);
    GISASSimulation* result = new GISASSimulation(beam, det);

    result->maskAll();
    // pacman
    const double deg = Units::deg;
    result->addMask(Ellipse(0.0 * deg, 1.0 * deg, 0.5 * deg, 0.5 * deg), false);
    result->addMask(Ellipse(0.11 * deg, 1.25 * deg, 0.05 * deg, 0.05 * deg), true);

    std::vector<std::vector<double>> points = {{0.0 * deg, 1.0 * deg},
                                               {0.5 * deg, 1.2 * deg},
                                               {0.5 * deg, 0.8 * deg},
                                               {0.0 * deg, 1.0 * deg}};
    result->addMask(Polygon(points), true);

    result->addMask(Rectangle(0.45 * deg, 0.95 * deg, 0.55 * deg, 1.05 * deg), false);
    result->addMask(Rectangle(0.61 * deg, 0.95 * deg, 0.71 * deg, 1.05 * deg), false);
    result->addMask(Rectangle(0.75 * deg, 0.95 * deg, 0.85 * deg, 1.05 * deg), false);

    // more masks
    result->addMask(Ellipse(-0.5 * deg, 1.5 * deg, 0.3 * deg, 0.1 * deg, 45. * deg), false);
    result->addMask(VerticalLine(-0.6 * deg), true);
    result->addMask(HorizontalLine(0.3 * deg), false);

    return result;
}

//! GISAS simulation with detector resolution.

GISASSimulation* StandardSimulations::MiniGISASDetectorResolution()
{
    GISASSimulation* result = MiniGISAS();
    ResolutionFunction2DGaussian resfunc(0.0025, 0.0025);
    result->setDetectorResolutionFunction(resfunc);
    return result;
}

GISASSimulation* StandardSimulations::MiniGISASPolarizationPP()
{
    GISASSimulation* result = MiniGISAS();

    kvector_t analyzer_dir(0.0, 0.0, 1.0);
    kvector_t beampol(0.0, 0.0, 1.0);

    result->beam().setPolarization(beampol);
    result->detector().setAnalyzerProperties(analyzer_dir, 1.0, 0.5);
    return result;
}

GISASSimulation* StandardSimulations::MiniGISASPolarizationPM()
{
    GISASSimulation* result = MiniGISAS();

    kvector_t analyzer_dir(0.0, 0.0, -1.0);
    kvector_t beampol(0.0, 0.0, 1.0);

    result->beam().setPolarization(beampol);
    result->detector().setAnalyzerProperties(analyzer_dir, 1.0, 0.5);
    return result;
}

GISASSimulation* StandardSimulations::MiniGISASPolarizationMP()
{
    GISASSimulation* result = MiniGISAS();

    kvector_t analyzer_dir(0.0, 0.0, 1.0);
    kvector_t beampol(0.0, 0.0, -1.0);

    result->beam().setPolarization(beampol);
    result->detector().setAnalyzerProperties(analyzer_dir, 1.0, 0.5);
    return result;
}

GISASSimulation* StandardSimulations::MiniGISASPolarizationMM()
{
    GISASSimulation* result = MiniGISAS();

    kvector_t analyzer_dir(0.0, 0.0, -1.0);
    kvector_t beampol(0.0, 0.0, -1.0);

    result->beam().setPolarization(beampol);
    result->detector().setAnalyzerProperties(analyzer_dir, 1.0, 0.5);
    return result;
}

//! GISAS simulation with small detector and including specular peak.

GISASSimulation* StandardSimulations::MiniGISASSpecularPeak()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    SphericalDetector det(25, -2 * deg, 2 * deg, 25, 0 * deg, 2 * deg);
    GISASSimulation* result = new GISASSimulation(beam, det);
    result->setBeamParameters(1 * angstrom, 0.2 * deg, 0 * deg);
    result->getOptions().setIncludeSpecular(true);
    return result;
}

//! GISAS simulation with large detector to test performance.

GISASSimulation* StandardSimulations::MaxiGISAS()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    SphericalDetector det(256, -2 * deg, 2 * deg, 256, 0 * deg, 2 * deg);
    return new GISASSimulation(beam, det);
}

//! Basic GISAS for polarization studies.

GISASSimulation* StandardSimulations::MaxiGISAS00()
{
    GISASSimulation* result = MaxiGISAS();
    kvector_t zplus(0.0, 0.0, 1.0);
    result->beam().setPolarization(zplus);
    result->detector().setAnalyzerProperties(zplus, 1.0, 0.5);
    return result;
}

//! Typical IsGISAXS simulation with the detector phi[-1,1], theta[0,2].

GISASSimulation* StandardSimulations::IsGISAXSSimulation1()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    IsGISAXSDetector det(100, -1 * deg, 1 * deg, 100, 0 * deg, 2 * deg);
    return new GISASSimulation(beam, det);
}

//! Typical IsGISAXS simulation with the detector phi[0,2], theta[0,2].

GISASSimulation* StandardSimulations::IsGISAXSSimulation2()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    SphericalDetector det(100, 0 * deg, 2 * deg, 100, 0 * deg, 2 * deg);
    return new GISASSimulation(beam, det);
}

//! GISAS simulation with generic rectangular detector.

GISASSimulation* StandardSimulations::RectDetectorGeneric()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    RectangularDetector det(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    det.setPosition(kvector_t(rdet_distance, 10.0, 5.0), rdet_width / 2., 1.0,
                    kvector_t(0.1, -1.0, 0.2));
    return new GISASSimulation(beam, det);
}

//! GISAS simulation with the rectangular detector perpendicular to the sample.

GISASSimulation* StandardSimulations::RectDetectorPerpToSample()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    RectangularDetector det(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    det.setPerpendicularToSampleX(rdet_distance, rdet_width / 2., 1.0);
    return new GISASSimulation(beam, det);
}

//! GISAS simulation with the rectangular detector perpendicular to the direct beam.

GISASSimulation* StandardSimulations::RectDetectorPerpToDirectBeam()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    RectangularDetector det(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    det.setPerpendicularToDirectBeam(rdet_distance, rdet_width / 2., 1.0);
    return new GISASSimulation(beam, det);
}

//! GISAS simulation with the rectangular detector perpendicular to the reflected beam.

GISASSimulation* StandardSimulations::RectDetectorPerpToReflectedBeam()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    RectangularDetector det(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    det.setPerpendicularToReflectedBeam(rdet_distance, rdet_width / 2., 1.0);
    return new GISASSimulation(beam, det);
}

//! GISAS simulation with the rectangular detector perpendicular to the reflected beam when
//! the coordinates of direct beam are known.

GISASSimulation* StandardSimulations::RectDetectorPerpToReflectedBeamDpos()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    RectangularDetector det(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    det.setPerpendicularToReflectedBeam(rdet_distance);
    det.setDirectBeamPosition(rdet_width / 2., 1.0);
    return new GISASSimulation(beam, det);
}

//! GISAS simulation with Monte-Carlo integration switched ON.

GISASSimulation* StandardSimulations::MiniGISASMonteCarlo()
{
    GISASSimulation* result = MiniGISAS();
    result->getOptions().setMonteCarloIntegration(true, 100);
    return result;
}

//! GISAS simulation with spherical detector, region of interest and mask.

GISASSimulation* StandardSimulations::SphericalDetWithRoi()
{
    Beam beam(1.0, 1 * angstrom, Direction(0.2 * deg, 0 * deg));
    SphericalDetector det(40, -2 * deg, 2 * deg, 30, 0 * deg, 3 * deg);
    GISASSimulation* result = new GISASSimulation(beam, det);
    result->addMask(Rectangle(-0.5 * deg, 0.3 * deg, -0.2 * deg, 0.6 * deg));
    result->setRegionOfInterest(-1.5 * deg, 0.25 * deg, 1.5 * deg, 1.75 * deg);
    return result;
}

//! GISAS simulation with rectangular detector, region of interest and mask.

GISASSimulation* StandardSimulations::RectDetWithRoi()
{
    GISASSimulation* result = RectDetectorPerpToDirectBeam();
    result->addMask(Rectangle(3.0, 4.0, 5.0, 7.0));
    result->setRegionOfInterest(2.0, 3.0, 18.0, 15.0);
    return result;
}

GISASSimulation* StandardSimulations::ConstantBackgroundGISAS()
{
    GISASSimulation* result = MiniGISAS();
    ConstantBackground bg(1e3);
    result->setBackground(bg);
    return result;
}

//! GISAS simulation with an extra long wavelength

GISASSimulation* StandardSimulations::ExtraLongWavelengthGISAS()
{
    Beam beam(1e8, 13.52 * Units::nm, Direction(0.2 * deg, 0 * deg));
    SphericalDetector det(100, -1 * deg, 1 * deg, 100, 0.0, 2 * deg);
    auto* simulation = new GISASSimulation(beam, det);
    simulation->getOptions().setIncludeSpecular(true);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecular()
{
    const double wavelength = 1.54 * angstrom;
    const int number_of_bins = 2000;
    const double min_angle = 0 * deg;
    const double max_angle = 5 * deg;
    AngularSpecScan scan(wavelength, FixedBinAxis("axis", number_of_bins, min_angle, max_angle));

    auto* result = new SpecularSimulation();
    result->setScan(scan);
    result->getOptions().setUseAvgMaterials(true);
    return result;
}

SpecularSimulation* StandardSimulations::BasicSpecularQ()
{
    std::vector<double> qs;
    {
        const double wavelength_0 = 1.54 * angstrom;
        const int number_of_bins = 2000;
        const double min_angle = 0 * deg;
        const double max_angle = 5 * deg;
        FixedBinAxis angle_axis("axis", number_of_bins, min_angle, max_angle);
        auto angles = angle_axis.binCenters();

        qs.resize(angle_axis.size(), 0.0);
        for (size_t i = 0, size = qs.size(); i < size; ++i)
            qs[i] = 4.0 * M_PI * std::sin(angles[i]) / wavelength_0;
    }
    QSpecScan q_scan(qs);

    auto* result = new SpecularSimulation;
    result->setScan(q_scan);
    result->getOptions().setUseAvgMaterials(true);
    return result;
}

SpecularSimulation* StandardSimulations::SpecularWithGaussianBeam()
{
    const double wavelength = 1.54 * angstrom;
    const int number_of_bins = 2000;
    const double min_angle = 0 * deg;
    const double max_angle = 5 * deg;
    auto gaussian_ff = std::make_unique<FootprintGauss>(1.0);
    AngularSpecScan scan(wavelength, FixedBinAxis("axis", number_of_bins, min_angle, max_angle));
    scan.setFootprintFactor(gaussian_ff.get());

    auto* result = new SpecularSimulation;
    result->setScan(scan);
    return result;
}

SpecularSimulation* StandardSimulations::SpecularWithSquareBeam()
{
    const double wavelength = 1.54 * angstrom;
    const int number_of_bins = 2000;
    const double min_angle = 0 * deg;
    const double max_angle = 5 * deg;
    auto square_ff = std::make_unique<FootprintSquare>(1.0);
    AngularSpecScan scan(wavelength, FixedBinAxis("axis", number_of_bins, min_angle, max_angle));
    scan.setFootprintFactor(square_ff.get());

    auto* result = new SpecularSimulation;
    result->setScan(scan);
    return result;
}

SpecularSimulation* StandardSimulations::SpecularDivergentBeam()
{
    const double wavelength = 1.54 * angstrom;
    const int number_of_bins = 20;
    const size_t n_integration_points = 10;
    const double min_angle = 0 * deg;
    const double max_angle = 5 * deg;
    const double wl_stddev = 0.1 * angstrom;
    const double ang_stddev = 0.1 * deg;
    AngularSpecScan scan(wavelength, FixedBinAxis("axis", number_of_bins, min_angle, max_angle));

    RangedDistributionGaussian wl_distr(n_integration_points, /*sigma_factor = */ 2.0);
    std::unique_ptr<ScanResolution> wl_res(
        ScanResolution::scanAbsoluteResolution(wl_distr, wl_stddev));

    RangedDistributionGaussian alpha_distr(n_integration_points, /*sigma_factor = */ 2.0);
    std::unique_ptr<ScanResolution> ang_res(
        ScanResolution::scanAbsoluteResolution(alpha_distr, ang_stddev));

    scan.setWavelengthResolution(*wl_res);
    scan.setAngleResolution(*ang_res);

    auto* result = new SpecularSimulation;
    result->setScan(scan);
    return result;
}

SpecularSimulation* StandardSimulations::TOFRWithRelativeResolution()
{
    FixedBinAxis qs("axis", 500, 0.0, 1.0);
    QSpecScan q_scan(qs);
    q_scan.setRelativeQResolution(RangedDistributionGaussian(20, 2.0), 0.03);

    auto* result = new SpecularSimulation;
    result->setScan(q_scan);
    result->getOptions().setUseAvgMaterials(true);
    return result;
}

SpecularSimulation* StandardSimulations::TOFRWithPointwiseResolution()
{
    FixedBinAxis qs("axis", 500, 0.0, 1.0);
    QSpecScan q_scan(qs);

    std::vector<double> resolutions;
    resolutions.reserve(qs.size());
    auto qs_vector = qs.binCenters();
    std::for_each(qs_vector.begin(), qs_vector.end(),
                  [&resolutions](double q_val) { resolutions.push_back(0.03 * q_val); });
    q_scan.setAbsoluteQResolution(RangedDistributionGaussian(20, 2.0), resolutions);

    auto* result = new SpecularSimulation;
    result->setScan(q_scan);
    result->getOptions().setUseAvgMaterials(true);
    return result;
}

// ------------ polarized specular ----------------
SpecularSimulation* StandardSimulations::BasicSpecularPP()
{
    auto* simulation = BasicSpecular();
    simulation->beam().setPolarization({0.0, 1.0, 0.0});
    simulation->detector().setAnalyzerProperties({0.0, 1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularPM()
{
    auto* simulation = BasicSpecular();
    simulation->beam().setPolarization({0.0, 1.0, 0.0});
    simulation->detector().setAnalyzerProperties({0.0, -1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularMP()
{
    auto* simulation = BasicSpecular();
    simulation->beam().setPolarization({0.0, -1.0, 0.0});
    simulation->detector().setAnalyzerProperties({0.0, 1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularMM()
{
    auto* simulation = BasicSpecular();
    simulation->beam().setPolarization({0.0, -1.0, 0.0});
    simulation->detector().setAnalyzerProperties({0.0, -1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularQPP()
{
    auto* simulation = BasicSpecularQ();
    simulation->beam().setPolarization({0.0, 1.0, 0.0});
    simulation->detector().setAnalyzerProperties({0.0, 1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularQMM()
{
    auto* simulation = BasicSpecularQ();
    simulation->beam().setPolarization({0.0, -1.0, 0.0});
    simulation->detector().setAnalyzerProperties({0.0, -1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularQPM()
{
    auto* simulation = BasicSpecularQ();
    simulation->beam().setPolarization({0.0, 1.0, 0.0});
    simulation->detector().setAnalyzerProperties({0.0, -1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularQMP()
{
    auto* simulation = BasicSpecularQ();
    simulation->beam().setPolarization({0.0, -1.0, 0.0});
    simulation->detector().setAnalyzerProperties({0.0, 1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

// ----------------------- off-spec simulations ------------------

// OffSpecular simulation used in ResonatorOffSpecularSetup.py
OffSpecularSimulation* StandardSimulations::MiniOffSpecular()
{
    auto* result = new OffSpecularSimulation;

    const int n_alpha(19);
    const double alpha_min(0 * deg);
    const double alpha_max(4 * deg);
    const int n_phi(9);
    const double phi_min(-0.1 * deg);
    const double phi_max(0.1 * deg);

    result->setDetectorParameters(n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max);

    const int n_scan_points(n_alpha);
    const double alpha_i_min(alpha_min);
    const double alpha_i_max(alpha_max);

    FixedBinAxis alpha_i_axis("alpha_i", n_scan_points, alpha_i_min, alpha_i_max);
    result->setBeamParameters(5 * angstrom, alpha_i_axis, 0.0);

    result->beam().setIntensity(1e9);
    result->getOptions().setIncludeSpecular(true);

    return result;
}

DepthProbeSimulation* StandardSimulations::BasicDepthProbe()
{
    auto* result = new DepthProbeSimulation;

    const double wavelength = 10 * angstrom;
    const size_t n_alpha = 20;
    const double alpha_min = 0 * deg;
    const double alpha_max = 1 * deg;
    const size_t n_z = n_alpha;
    const double z_min = -100.0 * Units::nm;
    const double z_max = 100.0 * Units::nm;

    result->setBeamParameters(wavelength, n_alpha, alpha_min, alpha_max);
    result->setZSpan(n_z, z_min, z_max);

    return result;
}

//! ISimulation with fitting.
//! Beam intensity set to provide reasonably large values in detector channels.
GISASSimulation* StandardSimulations::MiniGISASFit()
{
    auto* result = new GISASSimulation;
    result->setDetectorParameters(25, -2 * deg, 2 * deg, 25, 0 * deg, 2 * deg);
    result->setBeamParameters(1 * angstrom, 0.2 * deg, 0 * deg);
    result->beam().setIntensity(1e6);
    return result;
}
