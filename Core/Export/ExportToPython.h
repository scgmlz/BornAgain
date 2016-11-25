// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Export/ExportToPython.h
//! @brief     Defines class ExportToPython.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef EXPORTTOPYTHON_H
#define EXPORTTOPYTHON_H

#include "WinDllMacros.h"
#include <string>

class GISASSimulation;
class IParticle;
class MultiLayer;
class SampleLabelHandler;

//! Write a Python script that allows to run the current simulation.

class BA_CORE_API_ ExportToPython
{
public:
    ExportToPython(const MultiLayer& multilayer);
    virtual ~ExportToPython();

    std::string simulationToPythonLowlevel(const GISASSimulation* simulation);
    std::string defineGetSample() const;

private:
    std::string definePreamble() const;
    std::string defineGetSimulation(const GISASSimulation* simulation) const;
    std::string defineMaterials() const;
    std::string defineLayers() const;
    std::string defineFormFactors() const;
    std::string defineParticles() const;
    std::string defineCoreShellParticles() const;
    std::string defineParticleDistributions() const;
    std::string defineParticleCompositions() const;
    std::string defineInterferenceFunctions() const;
    std::string defineParticleLayouts() const;
    std::string defineRoughnesses() const;
    std::string addLayoutsToLayers() const;
    std::string defineMultiLayers() const;
    std::string defineDetector(const GISASSimulation* simulation) const;
    std::string defineDetectorResolutionFunction(const GISASSimulation* simulation) const;
    std::string defineBeam(const GISASSimulation* simulation) const;
    std::string defineParameterDistributions(const GISASSimulation* simulation) const;
    std::string defineMasks(const GISASSimulation* simulation) const;
    std::string defineSimulationOptions(const GISASSimulation* simulation) const;
    std::string definePlot(const GISASSimulation* simulation) const;

    std::string indent() const;
    void setRotationInformation(
        const IParticle* particle, std::string particle_name, std::ostringstream& result) const;
    void setPositionInformation(
        const IParticle* particle, std::string particle_name, std::ostringstream& result) const;

    SampleLabelHandler* m_label;
};

#endif // EXPORTTOPYTHON_H
