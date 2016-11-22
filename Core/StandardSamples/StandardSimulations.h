// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/StandardSimulations.h
//! @brief     Defines namespace and functions for standard simulations.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDARDSIMULATIONS_H
#define STANDARDSIMULATIONS_H

class GISASSimulation;

//! Standard pre-defined simulations.

namespace StandardSimulations {

// Special tests:
GISASSimulation* PolarizedDWBAMagCylinders2();

// CoreSuite tests:
GISASSimulation* BasicGISAS();
GISASSimulation* BasicGISAS00();
GISASSimulation* MiniGISAS();
GISASSimulation* MiniGISAS_v2();
GISASSimulation* MiniGISASBeamDivergence();
GISASSimulation* MiniGISASDetectorResolution();
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

} // namespace StandardSimulations

#endif // STANDARDSIMULATIONS_H
