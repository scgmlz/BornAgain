// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/StandardSimulations.h
//! @brief     Defines namespace and functions for standard simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SIMULATION_STANDARDSIMULATIONS_H
#define BORNAGAIN_CORE_SIMULATION_STANDARDSIMULATIONS_H

class DepthProbeSimulation;
class GISASSimulation;
class SpecularSimulation;
class OffSpecSimulation;

//! Standard pre-defined simulations.

namespace StandardSimulations
{

// CoreSuite tests:
GISASSimulation* BasicGISAS();
GISASSimulation* BasicGISAS00();
GISASSimulation* BasicPolarizedGISAS();
GISASSimulation* MiniGISAS();
GISASSimulation* MiniGISAS_v2();
GISASSimulation* MiniGISASBeamDivergence();
GISASSimulation* MiniGISASDetectorResolution();
GISASSimulation* MiniGISASSpecularPeak();
GISASSimulation* GISASWithMasks();
GISASSimulation* MaxiGISAS();
GISASSimulation* MaxiGISAS00();
GISASSimulation* IsGISAXSSimulation1();
GISASSimulation* IsGISAXSSimulation2();
GISASSimulation* RectDetectorGeneric();
GISASSimulation* RectDetectorPerpToSample();
GISASSimulation* RectDetectorPerpToDirectBeam();
GISASSimulation* RectDetectorPerpToReflectedBeam();
GISASSimulation* RectDetectorPerpToReflectedBeamDpos();
GISASSimulation* MiniGISASMonteCarlo();
GISASSimulation* SphericalDetWithRoi();
GISASSimulation* RectDetWithRoi();
GISASSimulation* ConstantBackgroundGISAS();
GISASSimulation* MiniGISASFit();
GISASSimulation* ExtraLongWavelengthGISAS();

// polarized GISAS:
GISASSimulation* MiniGISASPolarizationPP();
GISASSimulation* MiniGISASPolarizationPM();
GISASSimulation* MiniGISASPolarizationMP();
GISASSimulation* MiniGISASPolarizationMM();

// Specular simulation tests:
SpecularSimulation* BasicSpecular();
SpecularSimulation* BasicSpecularQ();
SpecularSimulation* SpecularWithGaussianBeam();
SpecularSimulation* SpecularWithSquareBeam();
SpecularSimulation* SpecularDivergentBeam();
SpecularSimulation* TOFRWithRelativeResolution();
SpecularSimulation* TOFRWithPointwiseResolution();

// polarized specular:
SpecularSimulation* BasicSpecularPP();
SpecularSimulation* BasicSpecularMM();
SpecularSimulation* BasicSpecularPM();
SpecularSimulation* BasicSpecularMP();
SpecularSimulation* BasicSpecularQPP();
SpecularSimulation* BasicSpecularQMM();
SpecularSimulation* BasicSpecularQPM();
SpecularSimulation* BasicSpecularQMP();

// OffSpec simulations
OffSpecSimulation* MiniOffSpec();

// Depth probe simulations
DepthProbeSimulation* BasicDepthProbe();

} // namespace StandardSimulations

#endif // BORNAGAIN_CORE_SIMULATION_STANDARDSIMULATIONS_H
