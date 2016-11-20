// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/RectDetectorFitTest.cpp
//! @brief     Implements class RectDetectorFitTest.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "RectDetectorFitTest.h"
#include "GISASSimulation.h"
#include "Histogram2D.h"
#include "Rectangle.h"
#include "RectangularDetector.h"
#include "Units.h"

RectDetectorFitTest::RectDetectorFitTest()
    : IMinimizerTest("Minuit2", "Migrad")
{
}

std::unique_ptr<GISASSimulation> RectDetectorFitTest::createSimulation()
{
    std::unique_ptr<GISASSimulation> result(new GISASSimulation());

    double detector_distance(500.0);
    double width(20.0), height(18.0);
    RectangularDetector detector(20, width, 18, height);
//    RectangularDetector detector(500, width, 450, height);
    detector.setPerpendicularToSampleX(detector_distance, width/2., 0.0);

    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    result->setDetector(detector);
    result->setRegionOfInterest(6.0, 6.0, 14.0, 12.0);
    result->addMask(Rectangle(8.0, 8.0, 10.0, 10.0), true);

    return result;
}

//! Creates cropped output data using histogram machinery
std::unique_ptr<OutputData<double> >
RectDetectorFitTest::createOutputData(const GISASSimulation *simulation)
{
    std::unique_ptr<GISASSimulation> simWithRoi(simulation->clone());
    simWithRoi->resetRegionOfInterest();
    simWithRoi->runSimulation();
//    std::unique_ptr<Histogram2D> tempHist(simulation->getIntensityData());
//    std::unique_ptr<Histogram2D> crop(tempHist->crop(2.0, 6.0, 16.0, 14.0));
//    std::unique_ptr<OutputData<double> > result(crop->createOutputData());
    std::unique_ptr<OutputData<double>> result(simWithRoi->getDetectorIntensity());
    return result;
}
