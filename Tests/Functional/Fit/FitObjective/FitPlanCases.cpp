// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/Fit/FitObjective/FitPlanCases.cpp
//! @brief     Implements collection of FitPlanCases classes
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "FitPlanCases.h"
#include "FitObjective.h"
#include "FormFactorCylinder.h"
#include "GISASSimulation.h"
#include "InterferenceFunction2DLattice.h"
#include "Layer.h"
#include "MaterialFactoryFuncs.h"
#include "MultiLayer.h"
#include "Parameters.h"
#include "Particle.h"
#include "ParticleLayout.h"
#include "Rectangle.h"
#include "RectangularDetector.h"
#include "FTDecayFunctions.h"
#include "Units.h"

using namespace Fit;

namespace {
    const double nm = Units::nanometer;
}

CylindersInBAPlan::CylindersInBAPlan()
    : FitPlan("CylindersInBAPlan")
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISAS");
    addParameter(Parameter("height", 4.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::lowerLimited(0.01), 0.01), 5.0*nm);
}

CylindersInBAEasyPlan::CylindersInBAEasyPlan()
    : FitPlan("CylindersInBAEasyPlan")
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISASFit");
    const double tolerance = 0.1;
    addParameter(Parameter("height", 4.5*nm, AttLimits::limited(4.0, 6.0), 0.1),
                 5.0*nm, tolerance);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::limited(4.0, 6.0), 0.1),
                 5.0*nm, tolerance);
}

CylindersInBAResidualPlan::CylindersInBAResidualPlan()
    : FitPlan("CylindersInBAResidualPlan", /*residual_based*/true)
{
    setBuilderName("CylindersInBABuilder");
    setSimulationName("MiniGISAS");
    addParameter(Parameter("height", 4.5*nm, AttLimits::limitless(), 0.01), 5.0*nm);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::limitless(), 0.01), 5.0*nm);
}

// ----------------------------------------------------------------------------

RectDetPlan::RectDetPlan()
    : FitPlan("RectDetPlan")
{
    setBuilderName("CylindersInBABuilder");
    addParameter(Parameter("height", 4.5*nm, AttLimits::limited(4.0, 6.0), 0.01), 5.0*nm);
    addParameter(Parameter("radius", 5.5*nm, AttLimits::limited(4.0, 6.0), 0.01), 5.0*nm);
}

RectDetPlan::~RectDetPlan() = default;

std::unique_ptr<Simulation> RectDetPlan::createSimulation(const Parameters&) const
{
    std::unique_ptr<GISASSimulation> result(new GISASSimulation());

    double detector_distance(500.0);
    double width(20.0), height(18.0);
    RectangularDetector detector(20u, width, 18u, height);
    detector.setPerpendicularToSampleX(detector_distance, width/2., 0.0);

    result->setBeamParameters(1.0*Units::angstrom, 0.2*Units::degree, 0.0*Units::degree);
    result->setDetector(detector);
    result->setRegionOfInterest(5.0, 6.0, 15.0, 12.0);
    result->addMask(Rectangle(0.0, 0.0, 2.0, 2.0), true);
    return std::unique_ptr<Simulation>(result.release());
}

// ----------------------------------------------------------------------------

SpecularPlan::SpecularPlan()
    : FitPlan("SpecularPlan")
{
    setSimulationName("BasicSpecular");
    setBuilderName("PlainMultiLayerBySLDBuilder");
    addParameter(Parameter("ti_thickness", 5.0 * nm, AttLimits::limited(1.0 * nm, 7.0 * nm), 0.1),
                 3.0 * nm);
}

SpecularPlan::~SpecularPlan() = default;

// ----------------------------------------------------------------------------

SpecularPlanQ::SpecularPlanQ()
    : FitPlan("SpecularPlanQ")
{
    setSimulationName("BasicSpecularQ");
    setBuilderName("PlainMultiLayerBySLDBuilder");
    addParameter(Parameter("ti_thickness", 5.0 * nm, AttLimits::limited(1.0 * nm, 7.0 * nm), 0.1),
                 3.0 * nm);
}

SpecularPlanQ::~SpecularPlanQ() = default;

// ----------------------------------------------------------------------------

MultipleSpecPlan::MultipleSpecPlan()
    : FitPlan("MultipleSpecPlan")
{
    setSimulationName("BasicSpecular");
    setBuilderName("PlainMultiLayerBySLDBuilder");
    addParameter(Parameter("ti_thickness", 5.0 * nm, AttLimits::limited(1.0 * nm, 7.0 * nm), 0.1),
                 3.0 * nm);
}

MultipleSpecPlan::~MultipleSpecPlan() = default;

std::unique_ptr<FitObjective> MultipleSpecPlan::createFitObjective() const
{
    std::unique_ptr<FitObjective> result(new FitObjective);

    simulation_builder_t builder = [&](const Fit::Parameters& params) {
        return buildSimulation(params);
    };

    result->addSimulationAndData(builder, *createOutputData(), nullptr, 0.5);
    result->addSimulationAndData(builder, *createOutputData(), nullptr, 0.5);
    result->initPrint(1);

    return result;
}

// ----------------------------------------------------------------------------

OffSpecFitPlan::OffSpecFitPlan()
    : FitPlan("OffSpecFitPlan")
{
    setBuilderName("ResonatorBuilder");
    setSimulationName("OffSpecMini");
    addParameter(
        Parameter("ti_thickness", 12.0 * nm, AttLimits::limited(11.5 * nm, 14.0 * nm), 0.1 * nm),
        13.0 * nm);
}
