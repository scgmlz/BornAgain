// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/RectDetectorFitTest.cpp
//! @brief     Implements class RectDetectorFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "RectDetectorFitTest.h"
#include "GISASSimulation.h"
#include "Histogram2D.h"
#include "Rectangle.h"
#include "RectangularDetector.h"
#include "Units.h"

RectDetectorFitTest::RectDetectorFitTest()
    : IObsoleteMinimizerTest("Minuit2", "Migrad")
{
}

std::unique_ptr<Simulation> RectDetectorFitTest::createSimulation()
{
    std::unique_ptr<GISASSimulation> result(new GISASSimulation());

    double detector_distance(500.0);
    double width(20.0), height(18.0);
    RectangularDetector detector(20u, width, 18u, height);
//    RectangularDetector detector(500, width, 450, height);
    detector.setPerpendicularToSampleX(detector_distance, width/2., 0.0);

    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    result->setBeamIntensity(1e2);
    result->setDetector(detector);
    result->setRegionOfInterest(6.0, 6.0, 14.0, 12.0);
    result->addMask(Rectangle(8.0, 8.0, 10.0, 10.0), true);

    return std::move(result);
}

//! Creates cropped output data using histogram machinery
std::unique_ptr<OutputData<double>>
RectDetectorFitTest::createOutputData(const Simulation* simulation)
{
    std::unique_ptr<Simulation> simWithRoi(simulation->clone());
    simWithRoi->getInstrument().getDetector()->resetRegionOfInterest();
    simWithRoi->runSimulation();
    auto sim_result = simWithRoi->result();
    std::unique_ptr<OutputData<double>> result(sim_result.data());
    return result;
}
