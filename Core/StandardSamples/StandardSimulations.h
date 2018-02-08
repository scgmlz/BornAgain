// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/StandardSimulations.h
//! @brief     Defines namespace and functions for standard simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef STANDARDSIMULATIONS_H
#define STANDARDSIMULATIONS_H

class GISASSimulation;
class SpecularSimulation;
class OffSpecSimulation;

//! Standard pre-defined simulations.

namespace StandardSimulations {

// Special tests:
GISASSimulation* PolarizedDWBAMagCylinders2();

// CoreSuite tests:
GISASSimulation* BasicGISAS();
GISASSimulation* BasicGISAS00();
GISASSimulation* BasicPolarizedGISAS();
GISASSimulation* MiniGISAS();
GISASSimulation* MiniGISAS_v2();
GISASSimulation* MiniGISASBeamDivergence();
GISASSimulation* MiniGISASDetectorResolution();
GISASSimulation* MiniGISASPolarizationPP();
GISASSimulation* MiniGISASSpinFlipZ();
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

// Specular simulation tests:
SpecularSimulation* BasicSpecular();
SpecularSimulation* SpecularWithGaussianBeam();
SpecularSimulation* SpecularWithSquareBeam();
SpecularSimulation* SpecularDivergentBeam();

// OffSpec simulations
OffSpecSimulation* MiniOffSpec();


} // namespace StandardSimulations

#endif // STANDARDSIMULATIONS_H
