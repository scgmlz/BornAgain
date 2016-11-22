// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/StandardSimulations.cpp
//! @brief     Implements functions for standard simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "StandardSimulations.h"
#include "BornAgainNamespace.h"
#include "Distributions.h"
#include "Ellipse.h"
#include "GISASSimulation.h"
#include "IsGISAXSDetector.h"
#include "Line.h"
#include "ParameterPattern.h"
#include "Polygon.h"
#include "RealParameter.h"
#include "Rectangle.h"
#include "RectangularDetector.h"
#include "ResolutionFunction2DGaussian.h"
#include "SampleBuilderFactory.h"
#include "Units.h"

namespace {
    const int rdet_nbinsx(40), rdet_nbinsy(30);
    const double rdet_width(20.0), rdet_height(18.0), rdet_distance(1000.0);
}

GISASSimulation* StandardSimulations::PolarizedDWBAMagCylinders2()
{
    SampleBuilderFactory factory;
    std::shared_ptr<IMultiLayerBuilder> builder(factory.createItem("MagneticCylindersBuilder"));

    GISASSimulation* result = new GISASSimulation();

    result->setDetectorParameters(100, -1.0*Units::degree, 1.0*Units::degree,
                                  100, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    result->setBeamIntensity(1e7);
    result->setSampleBuilder( builder );
    return result;
}

//! Basic GISAS simulation with the detector phi[0,2], theta[0,2].

GISASSimulation* StandardSimulations::BasicGISAS()
{
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                  100, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    return result;
}

//! Basic GISAS for polarization studies.

GISASSimulation* StandardSimulations::BasicGISAS00()
{
    GISASSimulation* result = BasicGISAS();
    kvector_t zplus(0.0, 0.0, 1.0);
    result->setBeamPolarization(zplus);
    result->setAnalyzerProperties(zplus, 1.0, 0.5);
    return result;
}

//! GISAS simulation with small detector and phi[-2,2], theta[0,2].

GISASSimulation* StandardSimulations::MiniGISAS()
{
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(25, -2.0*Units::degree, 2.0*Units::degree,
                                  25, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    return result;
}

//! GISAS simulation with small detector and phi[-1,1], theta[0,1].

GISASSimulation* StandardSimulations::MiniGISAS_v2()
{
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(25, -1.0*Units::degree, 1.0*Units::degree,
                                  25, 0.0*Units::degree, 1.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    return result;
}

//! GISAS simulation with beam divergence applied.

GISASSimulation* StandardSimulations::MiniGISASBeamDivergence()
{
    GISASSimulation* result = MiniGISAS();

    DistributionLogNormal wavelength_distr(1.0*Units::angstrom, 0.1);
    DistributionGaussian alpha_distr(0.2*Units::degree, 0.1*Units::degree);
    DistributionGate phi_distr(-0.1*Units::degree, 0.1*Units::degree);

    ParameterPattern pattern1;
    pattern1.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Wavelength);
    result->addParameterDistribution(pattern1.toStdString(), wavelength_distr, 5);
    ParameterPattern pattern2;
    pattern2.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Inclination);
    result->addParameterDistribution(pattern2.toStdString(), alpha_distr, 4);
    ParameterPattern pattern3;
    pattern3.beginsWith("*").add(BornAgain::BeamType).add(BornAgain::Azimuth);
    result->addParameterDistribution(pattern3.toStdString(), phi_distr, 3);

    return result;
}

//! GISAS simulation with multiple masks on the detector plane.

GISASSimulation* StandardSimulations::GISASWithMasks()
{
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(50, -1.0*Units::degree, 1.0*Units::degree,
                                     50, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    result->setBeamIntensity(1e+7);

    result->maskAll();
    // pacman
    const double deg = Units::degree;
    result->addMask(Ellipse(0.0*deg, 1.0*deg, 0.5*deg, 0.5*deg), false);
    result->addMask(Ellipse(0.11*deg, 1.25*deg, 0.05*deg, 0.05*deg), true);

    std::vector<std::vector<double> >  points = {
        {0.0*deg, 1.0*deg}, {0.5*deg, 1.2*deg}, {0.5*deg, 0.8*deg}, {0.0*deg, 1.0*deg}
    };
    result->addMask(Polygon(points), true);

    result->addMask(Rectangle(0.45*deg, 0.95*deg, 0.55*deg, 1.05*deg), false);
    result->addMask(Rectangle(0.61*deg, 0.95*deg, 0.71*deg, 1.05*deg), false);
    result->addMask(Rectangle(0.75*deg, 0.95*deg, 0.85*deg, 1.05*deg), false);

    // more masks
    result->addMask(Ellipse(-0.5*deg, 1.5*deg, 0.3*deg, 0.1*deg, 45.*deg), false);
    result->addMask(VerticalLine(-0.6*deg), true);
    result->addMask(HorizontalLine(0.3*deg), false);

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

//! GISAS simulation with large detector to test performance.

GISASSimulation* StandardSimulations::MaxiGISAS()
{
    GISASSimulation* result = new GISASSimulation();
    result->setDetectorParameters(256, -2.0*Units::degree, 2.0*Units::degree,
                                  256, 0.0*Units::degree, 2.0*Units::degree);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    return result;
}

//! Basic GISAS for polarization studies.

GISASSimulation* StandardSimulations::MaxiGISAS00()
{
    GISASSimulation* result = MaxiGISAS();
    kvector_t zplus(0.0, 0.0, 1.0);
    result->setBeamPolarization(zplus);
    result->setAnalyzerProperties(zplus, 1.0, 0.5);
    return result;
}

//! Typical IsGISAXS simulation with the detector phi[-1,1], theta[0,2].

GISASSimulation* StandardSimulations::IsGISAXSSimulation1()
{
    GISASSimulation* result = new GISASSimulation();
    IsGISAXSDetector detector;
    detector.setDetectorParameters(100,-1.0*Units::degree, 1.0*Units::degree,
                                   100, 0.0*Units::degree, 2.0*Units::degree);
    result->setDetector(detector);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    return result;
}

//! Typical IsGISAXS simulation with the detector phi[0,2], theta[0,2].

GISASSimulation* StandardSimulations::IsGISAXSSimulation2()
{
    GISASSimulation* result = new GISASSimulation();
    IsGISAXSDetector detector;
    detector.setDetectorParameters(100, 0.0*Units::degree, 2.0*Units::degree,
                                   100, 0.0*Units::degree, 2.0*Units::degree);
    result->setDetector(detector);
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    return result;
}

//! GISAS simulation with generic rectangular detector.

GISASSimulation* StandardSimulations::RectDetectorGeneric()
{
    GISASSimulation* result = new GISASSimulation();
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    RectangularDetector detector(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    detector.setPosition(kvector_t(rdet_distance, 10.0, 5.0), rdet_width/2.,
                         1.0, kvector_t(0.1, -1.0, 0.2));

    result->setDetector(detector);
    return result;
}

//! GISAS simulation with the rectangular detector perpendicular to the sample.

GISASSimulation* StandardSimulations::RectDetectorPerpToSample()
{
    GISASSimulation* result = new GISASSimulation();
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    RectangularDetector detector(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    detector.setPerpendicularToSampleX(rdet_distance, rdet_width/2., 1.0);

    result->setDetector(detector);
    return result;
}

//! GISAS simulation with the rectangular detector perpendicular to the direct beam.

GISASSimulation* StandardSimulations::RectDetectorPerpToDirectBeam()
{
    GISASSimulation* result = new GISASSimulation();
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    RectangularDetector detector(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    detector.setPerpendicularToDirectBeam(rdet_distance, rdet_width/2., 1.0);

    result->setDetector(detector);
    return result;
}

//! GISAS simulation with the rectangular detector perpendicular to the reflected beam.

GISASSimulation* StandardSimulations::RectDetectorPerpToReflectedBeam()
{
    GISASSimulation* result = new GISASSimulation();
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    RectangularDetector detector(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    detector.setPerpendicularToReflectedBeam(rdet_distance, rdet_width/2., 1.0);

    result->setDetector(detector);
    return result;
}

//! GISAS simulation with the rectangular detector perpendicular to the reflected beam when
//! the coordinates of direct beam are known.

GISASSimulation* StandardSimulations::RectDetectorPerpToReflectedBeamDpos()
{
    GISASSimulation* result = new GISASSimulation();
    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);

    RectangularDetector detector(rdet_nbinsx, rdet_width, rdet_nbinsy, rdet_height);
    detector.setPerpendicularToReflectedBeam(rdet_distance);
    detector.setDirectBeamPosition(rdet_width/2., 1.0);

    result->setDetector(detector);
    return result;
}

//! GISAS simulation with Monte-Carlo integration switched ON.

GISASSimulation* StandardSimulations::MiniGISASMonteCarlo()
{
    GISASSimulation* result = MiniGISAS();
    result->getOptions().setMonteCarloIntegration(true, 100);
    return result;
}

//! GISAS simulation with spherical detector, region of interest and mask.

GISASSimulation *StandardSimulations::SphericalDetWithRoi() {
  GISASSimulation *result = new GISASSimulation();
  result->setDetectorParameters(40, -2.0 * Units::degree, 2.0 * Units::degree,
                                30, 0.0 * Units::degree, 3.0 * Units::degree);
  result->setBeamParameters(1.0 * Units::angstrom, 0.2 * Units::degree,
                            0.0 * Units::degree);
  result->addMask(Rectangle(-0.5 * Units::degree, 0.3 * Units::degree,
                                      -0.2 * Units::degree,
                                      0.6 * Units::degree));
  result->setRegionOfInterest(-1.5 * Units::degree, 0.25 * Units::degree,
                              1.5 * Units::degree, 1.75 * Units::degree);
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
