//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
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

//! Basic GISAS simulation with the detector phi[0,2], theta[0,2].

GISASSimulation* StandardSimulations::BasicGISAS() {
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(100, 0.0 * Units::deg, 2.0 * Units::deg, 100, 0.0 * Units::deg,
                                  2.0 * Units::deg);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);
    return result;
}

//! Basic GISAS for polarization studies.

GISASSimulation* StandardSimulations::BasicGISAS00() {
    GISASSimulation* result = BasicGISAS();
    kvector_t zplus(0.0, 0.0, 1.0);
    result->beam().setPolarization(zplus);
    result->setAnalyzerProperties(zplus, 1.0, 0.5);
    return result;
}

//! Basic GISAS simulation for spin flip channel.

GISASSimulation* StandardSimulations::BasicPolarizedGISAS() {
    GISASSimulation* result = BasicGISAS();
    kvector_t zplus(0.0, 0.0, 1.0);
    result->beam().setPolarization(zplus);
    result->setAnalyzerProperties(zplus, -1.0, 0.5);
    return result;
}

//! GISAS simulation with small detector and phi[-2,2], theta[0,2].

GISASSimulation* StandardSimulations::MiniGISAS() {
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(25, -2.0 * Units::deg, 2.0 * Units::deg, 25, 0.0 * Units::deg,
                                  2.0 * Units::deg);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);
    return result;
}

//! GISAS simulation with small detector and phi[-1,1], theta[0,1].

GISASSimulation* StandardSimulations::MiniGISAS_v2() {
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(25, -1.0 * Units::deg, 1.0 * Units::deg, 25, 0.0 * Units::deg,
                                  1.0 * Units::deg);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);
    return result;
}

//! GISAS simulation with beam divergence applied.

GISASSimulation* StandardSimulations::MiniGISASBeamDivergence() {
    GISASSimulation* result = MiniGISAS();

    DistributionLogNormal wavelength_distr(1.0 * Units::angstrom, 0.1);
    DistributionGaussian alpha_distr(0.2 * Units::deg, 0.02 * Units::deg);
    DistributionGate phi_distr(-0.1 * Units::deg, 0.02 * Units::deg);

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

GISASSimulation* StandardSimulations::GISASWithMasks() {
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(50, -1.0 * Units::deg, 1.0 * Units::deg, 50, 0.0 * Units::deg,
                                  2.0 * Units::deg);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);
    result->beam().setIntensity(1e+7);

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

GISASSimulation* StandardSimulations::MiniGISASDetectorResolution() {
    GISASSimulation* result = MiniGISAS();
    ResolutionFunction2DGaussian resfunc(0.0025, 0.0025);
    result->setDetectorResolutionFunction(resfunc);
    return result;
}

GISASSimulation* StandardSimulations::MiniGISASPolarizationPP() {
    GISASSimulation* result = MiniGISAS();

    kvector_t analyzer_dir(0.0, 0.0, 1.0);
    kvector_t beampol(0.0, 0.0, 1.0);

    result->beam().setPolarization(beampol);
    result->setAnalyzerProperties(analyzer_dir, 1.0, 0.5);
    return result;
}

GISASSimulation* StandardSimulations::MiniGISASPolarizationPM() {
    GISASSimulation* result = MiniGISAS();

    kvector_t analyzer_dir(0.0, 0.0, -1.0);
    kvector_t beampol(0.0, 0.0, 1.0);

    result->beam().setPolarization(beampol);
    result->setAnalyzerProperties(analyzer_dir, 1.0, 0.5);
    return result;
}

GISASSimulation* StandardSimulations::MiniGISASPolarizationMP() {
    GISASSimulation* result = MiniGISAS();

    kvector_t analyzer_dir(0.0, 0.0, 1.0);
    kvector_t beampol(0.0, 0.0, -1.0);

    result->beam().setPolarization(beampol);
    result->setAnalyzerProperties(analyzer_dir, 1.0, 0.5);
    return result;
}

GISASSimulation* StandardSimulations::MiniGISASPolarizationMM() {
    GISASSimulation* result = MiniGISAS();

    kvector_t analyzer_dir(0.0, 0.0, -1.0);
    kvector_t beampol(0.0, 0.0, -1.0);

    result->beam().setPolarization(beampol);
    result->setAnalyzerProperties(analyzer_dir, 1.0, 0.5);
    return result;
}

//! GISAS simulation with small detector and including specular peak.

GISASSimulation* StandardSimulations::MiniGISASSpecularPeak() {
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(25, -2.0 * Units::deg, 2.0 * Units::deg, 25, 0.0 * Units::deg,
                                  2.0 * Units::deg);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);
    result->getOptions().setIncludeSpecular(true);
    return result;
}

//! GISAS simulation with large detector to test performance.

GISASSimulation* StandardSimulations::MaxiGISAS() {
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(256, -2.0 * Units::deg, 2.0 * Units::deg, 256, 0.0 * Units::deg,
                                  2.0 * Units::deg);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);
    return result;
}

//! Basic GISAS for polarization studies.

GISASSimulation* StandardSimulations::MaxiGISAS00() {
    GISASSimulation* result = MaxiGISAS();
    kvector_t zplus(0.0, 0.0, 1.0);
    result->beam().setPolarization(zplus);
    result->setAnalyzerProperties(zplus, 1.0, 0.5);
    return result;
}

//! Typical IsGISAXS simulation with the detector phi[-1,1], theta[0,2].

GISASSimulation* StandardSimulations::IsGISAXSSimulation1() {
    GISASSimulation* result = new GISASSimulation();
    IsGISAXSDetector detector;
    detector.setDetectorParameters(100, -1.0 * Units::deg, 1.0 * Units::deg, 100, 0.0 * Units::deg,
                                   2.0 * Units::deg);
    result->setDetector(detector);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);
    return result;
}

//! Typical IsGISAXS simulation with the detector phi[0,2], theta[0,2].

GISASSimulation* StandardSimulations::IsGISAXSSimulation2() {
    GISASSimulation* result = new GISASSimulation();
    IsGISAXSDetector detector;
    detector.setDetectorParameters(100, 0.0 * Units::deg, 2.0 * Units::deg, 100, 0.0 * Units::deg,
                                   2.0 * Units::deg);
    result->setDetector(detector);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);
    return result;
}

//! GISAS simulation with generic rectangular detector.

GISASSimulation* StandardSimulations::RectDetectorGeneric() {
    GISASSimulation* result = new GISASSimulation();
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);

    RectangularDetector detector(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    detector.setPosition(kvector_t(rdet_distance, 10.0, 5.0), rdet_width / 2., 1.0,
                         kvector_t(0.1, -1.0, 0.2));

    result->setDetector(detector);
    return result;
}

//! GISAS simulation with the rectangular detector perpendicular to the sample.

GISASSimulation* StandardSimulations::RectDetectorPerpToSample() {
    GISASSimulation* result = new GISASSimulation();
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);

    RectangularDetector detector(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    detector.setPerpendicularToSampleX(rdet_distance, rdet_width / 2., 1.0);

    result->setDetector(detector);
    return result;
}

//! GISAS simulation with the rectangular detector perpendicular to the direct beam.

GISASSimulation* StandardSimulations::RectDetectorPerpToDirectBeam() {
    GISASSimulation* result = new GISASSimulation();
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);

    RectangularDetector detector(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    detector.setPerpendicularToDirectBeam(rdet_distance, rdet_width / 2., 1.0);

    result->setDetector(detector);
    return result;
}

//! GISAS simulation with the rectangular detector perpendicular to the reflected beam.

GISASSimulation* StandardSimulations::RectDetectorPerpToReflectedBeam() {
    GISASSimulation* result = new GISASSimulation();
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);

    RectangularDetector detector(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    detector.setPerpendicularToReflectedBeam(rdet_distance, rdet_width / 2., 1.0);

    result->setDetector(detector);
    return result;
}

//! GISAS simulation with the rectangular detector perpendicular to the reflected beam when
//! the coordinates of direct beam are known.

GISASSimulation* StandardSimulations::RectDetectorPerpToReflectedBeamDpos() {
    GISASSimulation* result = new GISASSimulation();
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);

    RectangularDetector detector(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    detector.setPerpendicularToReflectedBeam(rdet_distance);
    detector.setDirectBeamPosition(rdet_width / 2., 1.0);

    result->setDetector(detector);
    return result;
}

//! GISAS simulation with Monte-Carlo integration switched ON.

GISASSimulation* StandardSimulations::MiniGISASMonteCarlo() {
    GISASSimulation* result = MiniGISAS();
    result->getOptions().setMonteCarloIntegration(true, 100);
    return result;
}

//! GISAS simulation with spherical detector, region of interest and mask.

GISASSimulation* StandardSimulations::SphericalDetWithRoi() {
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(40, -2.0 * Units::deg, 2.0 * Units::deg, 30, 0.0 * Units::deg,
                                  3.0 * Units::deg);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);
    result->addMask(
        Rectangle(-0.5 * Units::deg, 0.3 * Units::deg, -0.2 * Units::deg, 0.6 * Units::deg));
    result->setRegionOfInterest(-1.5 * Units::deg, 0.25 * Units::deg, 1.5 * Units::deg,
                                1.75 * Units::deg);
    return result;
}

//! GISAS simulation with rectangular detector, region of interest and mask.

GISASSimulation* StandardSimulations::RectDetWithRoi() {
    GISASSimulation* result = RectDetectorPerpToDirectBeam();
    result->addMask(Rectangle(3.0, 4.0, 5.0, 7.0));
    result->setRegionOfInterest(2.0, 3.0, 18.0, 15.0);
    return result;
}

GISASSimulation* StandardSimulations::ConstantBackgroundGISAS() {
    GISASSimulation* result = MiniGISAS();
    ConstantBackground bg(1e3);
    result->setBackground(bg);
    return result;
}

//! GISAS simulation with an extra long wavelength

GISASSimulation* StandardSimulations::ExtraLongWavelengthGISAS() {
    auto* simulation = new GISASSimulation;
    simulation->setDetectorParameters(100, -1.0 * Units::deg, 1.0 * Units::deg, 100, 0.0,
                                      2.0 * Units::deg);

    simulation->setBeamParameters(13.52 * Units::nm, 0.2 * Units::deg, 0.0 * Units::deg);
    simulation->beam().setIntensity(1.0e+08);
    simulation->getOptions().setIncludeSpecular(true);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecular() {
    const double wavelength = 1.54 * Units::angstrom;
    const int number_of_bins = 2000;
    const double min_angle = 0 * Units::deg;
    const double max_angle = 5 * Units::deg;
    AngularSpecScan scan(wavelength, FixedBinAxis("axis", number_of_bins, min_angle, max_angle));

    auto* result = new SpecularSimulation();
    result->setScan(scan);
    result->getOptions().setUseAvgMaterials(true);
    return result;
}

SpecularSimulation* StandardSimulations::BasicSpecularQ() {
    std::vector<double> qs;
    {
        const double wavelength_0 = 1.54 * Units::angstrom;
        const int number_of_bins = 2000;
        const double min_angle = 0 * Units::deg;
        const double max_angle = 5 * Units::deg;
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

SpecularSimulation* StandardSimulations::SpecularWithGaussianBeam() {
    const double wavelength = 1.54 * Units::angstrom;
    const int number_of_bins = 2000;
    const double min_angle = 0 * Units::deg;
    const double max_angle = 5 * Units::deg;
    auto gaussian_ff = std::make_unique<FootprintGauss>(1.0);
    AngularSpecScan scan(wavelength, FixedBinAxis("axis", number_of_bins, min_angle, max_angle));
    scan.setFootprintFactor(gaussian_ff.get());

    auto* result = new SpecularSimulation;
    result->setScan(scan);
    return result;
}

SpecularSimulation* StandardSimulations::SpecularWithSquareBeam() {
    const double wavelength = 1.54 * Units::angstrom;
    const int number_of_bins = 2000;
    const double min_angle = 0 * Units::deg;
    const double max_angle = 5 * Units::deg;
    auto square_ff = std::make_unique<FootprintSquare>(1.0);
    AngularSpecScan scan(wavelength, FixedBinAxis("axis", number_of_bins, min_angle, max_angle));
    scan.setFootprintFactor(square_ff.get());

    auto* result = new SpecularSimulation;
    result->setScan(scan);
    return result;
}

SpecularSimulation* StandardSimulations::SpecularDivergentBeam() {
    const double wavelength = 1.54 * Units::angstrom;
    const int number_of_bins = 20;
    const size_t n_integration_points = 10;
    const double min_angle = 0 * Units::deg;
    const double max_angle = 5 * Units::deg;
    const double wl_stddev = 0.1 * Units::angstrom;
    const double ang_stddev = 0.1 * Units::deg;
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

SpecularSimulation* StandardSimulations::TOFRWithRelativeResolution() {
    FixedBinAxis qs("axis", 500, 0.0, 1.0);
    QSpecScan q_scan(qs);
    q_scan.setRelativeQResolution(RangedDistributionGaussian(20, 2.0), 0.03);

    auto* result = new SpecularSimulation;
    result->setScan(q_scan);
    result->getOptions().setUseAvgMaterials(true);
    return result;
}

SpecularSimulation* StandardSimulations::TOFRWithPointwiseResolution() {
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
SpecularSimulation* StandardSimulations::BasicSpecularPP() {
    auto* simulation = BasicSpecular();
    simulation->beam().setPolarization({0.0, 1.0, 0.0});
    simulation->setAnalyzerProperties({0.0, 1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularPM() {
    auto* simulation = BasicSpecular();
    simulation->beam().setPolarization({0.0, 1.0, 0.0});
    simulation->setAnalyzerProperties({0.0, -1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularMP() {
    auto* simulation = BasicSpecular();
    simulation->beam().setPolarization({0.0, -1.0, 0.0});
    simulation->setAnalyzerProperties({0.0, 1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularMM() {
    auto* simulation = BasicSpecular();
    simulation->beam().setPolarization({0.0, -1.0, 0.0});
    simulation->setAnalyzerProperties({0.0, -1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularQPP() {
    auto* simulation = BasicSpecularQ();
    simulation->beam().setPolarization({0.0, 1.0, 0.0});
    simulation->setAnalyzerProperties({0.0, 1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularQMM() {
    auto* simulation = BasicSpecularQ();
    simulation->beam().setPolarization({0.0, -1.0, 0.0});
    simulation->setAnalyzerProperties({0.0, -1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularQPM() {
    auto* simulation = BasicSpecularQ();
    simulation->beam().setPolarization({0.0, 1.0, 0.0});
    simulation->setAnalyzerProperties({0.0, -1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

SpecularSimulation* StandardSimulations::BasicSpecularQMP() {
    auto* simulation = BasicSpecularQ();
    simulation->beam().setPolarization({0.0, -1.0, 0.0});
    simulation->setAnalyzerProperties({0.0, 1.0, 0.0}, 1.0, 0.5);
    return simulation;
}

// ----------------------- off-spec simulations ------------------

// OffSpecular simulation used in ResonatorOffSpecularSetup.py
OffSpecularSimulation* StandardSimulations::MiniOffSpecular() {
    auto* result = new OffSpecularSimulation;

    const int n_alpha(19);
    const double alpha_min(0.0 * Units::deg);
    const double alpha_max(4.0 * Units::deg);
    const int n_phi(9);
    const double phi_min(-0.1 * Units::deg);
    const double phi_max(0.1 * Units::deg);

    result->setDetectorParameters(n_phi, phi_min, phi_max, n_alpha, alpha_min, alpha_max);

    const int n_scan_points(n_alpha);
    const double alpha_i_min(alpha_min);
    const double alpha_i_max(alpha_max);

    FixedBinAxis alpha_i_axis("alpha_i", n_scan_points, alpha_i_min, alpha_i_max);
    result->setBeamParameters(5.0 * Units::angstrom, alpha_i_axis, 0.0);

    result->beam().setIntensity(1e9);
    result->getOptions().setIncludeSpecular(true);

    return result;
}

DepthProbeSimulation* StandardSimulations::BasicDepthProbe() {
    auto* result = new DepthProbeSimulation;

    const double wavelength = 10.0 * Units::angstrom;
    const size_t n_alpha = 20;
    const double alpha_min = 0.0 * Units::deg;
    const double alpha_max = 1.0 * Units::deg;
    const size_t n_z = n_alpha;
    const double z_min = -100.0 * Units::nm;
    const double z_max = 100.0 * Units::nm;

    result->setBeamParameters(wavelength, n_alpha, alpha_min, alpha_max);
    result->setZSpan(n_z, z_min, z_max);

    return result;
}

//! ISimulation with fitting.
//! Beam intensity set to provide reasonably large values in detector channels.
GISASSimulation* StandardSimulations::MiniGISASFit() {
    auto* result = new GISASSimulation;
    result->setDetectorParameters(25, -2.0 * Units::deg, 2.0 * Units::deg, 25, 0.0 * Units::deg,
                                  2.0 * Units::deg);
    result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::deg, 0.0 * Units::deg);
    result->beam().setIntensity(1e6);
    return result;
}
