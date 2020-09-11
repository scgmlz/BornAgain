// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SimulationFactory.cpp
//! @brief     Implement class SimulationFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Simulation/SimulationFactory.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Simulation/DepthProbeSimulation.h"
#include "Core/Simulation/GISASSimulation.h"
#include "Core/Simulation/OffSpecSimulation.h"
#include "Core/Simulation/SpecularSimulation.h"
#include "Core/Simulation/StandardSimulations.h"

SimulationFactory::SimulationFactory()
{
    registerItem("BasicGISAS", StandardSimulations::BasicGISAS);

    registerItem("BasicGISAS00", StandardSimulations::BasicGISAS00);

    registerItem("BasicPolarizedGISAS", StandardSimulations::BasicPolarizedGISAS);

    registerItem("MiniGISAS", StandardSimulations::MiniGISAS);

    registerItem("MiniGISAS_v2", StandardSimulations::MiniGISAS_v2);

    registerItem("MiniGISASBeamDivergence", StandardSimulations::MiniGISASBeamDivergence);

    registerItem("MiniGISASDetectorResolution", StandardSimulations::MiniGISASDetectorResolution);

    registerItem("MiniGISASSpecular", StandardSimulations::MiniGISASSpecularPeak);

    registerItem("GISASWithMasks", StandardSimulations::GISASWithMasks);

    registerItem("MaxiGISAS", StandardSimulations::MaxiGISAS);

    registerItem("MaxiGISAS00", StandardSimulations::MaxiGISAS00);

    registerItem("IsGISAXSSimulation1", StandardSimulations::IsGISAXSSimulation1);

    registerItem("IsGISAXSSimulation2", StandardSimulations::IsGISAXSSimulation2);

    // polarization

    registerItem("MiniGISASPolarizationPP", StandardSimulations::MiniGISASPolarizationPP);

    registerItem("MiniGISASPolarizationPM", StandardSimulations::MiniGISASPolarizationPM);

    registerItem("MiniGISASPolarizationMP", StandardSimulations::MiniGISASPolarizationMP);

    registerItem("MiniGISASPolarizationMM", StandardSimulations::MiniGISASPolarizationMM);

    // rectangular detectors

    registerItem("RectDetectorGeneric", StandardSimulations::RectDetectorGeneric);

    registerItem("RectDetectorPerpToSample", StandardSimulations::RectDetectorPerpToSample);

    registerItem("RectDetectorPerpToDirectBeam", StandardSimulations::RectDetectorPerpToDirectBeam);

    registerItem("RectDetectorPerpToReflectedBeam",
                 StandardSimulations::RectDetectorPerpToReflectedBeam);

    registerItem("RectDetectorPerpToReflectedBeamDpos",
                 StandardSimulations::RectDetectorPerpToReflectedBeamDpos);

    registerItem("ExtraLongWavelengthGISAS", StandardSimulations::ExtraLongWavelengthGISAS);

    // Monte-Carlo
    registerItem("MiniGISASMonteCarlo", StandardSimulations::MiniGISASMonteCarlo);

    // region of interest

    registerItem("SphericalDetWithRoi", StandardSimulations::SphericalDetWithRoi);
    registerItem("RectDetWithRoi", StandardSimulations::RectDetWithRoi);

    // background

    registerItem("ConstantBackground", StandardSimulations::ConstantBackgroundGISAS);

    // specular simulations

    registerItem("BasicSpecular", StandardSimulations::BasicSpecular);

    registerItem("BasicSpecularQ", StandardSimulations::BasicSpecularQ);

    registerItem("SpecularWithGaussianBeam", StandardSimulations::SpecularWithGaussianBeam);

    registerItem("SpecularWithSquareBeam", StandardSimulations::SpecularWithSquareBeam);

    registerItem("SpecularDivergentBeam", StandardSimulations::SpecularDivergentBeam);

    registerItem("TOFRWithRelativeResolution", StandardSimulations::TOFRWithRelativeResolution);

    registerItem("TOFRWithPointwiseResolution", StandardSimulations::TOFRWithPointwiseResolution);

    registerItem("OffSpecMini", StandardSimulations::MiniOffSpec);

    // polarized specular

    registerItem("BasicSpecularPP", StandardSimulations::BasicSpecularPP);

    registerItem("BasicSpecularMM", StandardSimulations::BasicSpecularMM);

    registerItem("BasicQSpecularPP", StandardSimulations::BasicSpecularQPP);

    registerItem("BasicQSpecularMM", StandardSimulations::BasicSpecularQMM);

    // depth probe simulations

    registerItem("BasicDepthProbe", StandardSimulations::BasicDepthProbe);

    registerItem("MiniGISASFit", StandardSimulations::MiniGISASFit);
}
