// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/GISASSimulation.cpp
//! @brief     Implements class Simulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Simulation/GISASSimulation.h"
#include "Core/Computation/DWBAComputation.h"
#include "Core/Computation/IBackground.h"
#include "Core/Intensity/Histogram2D.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Simulation/UnitConverterUtils.h"
#include "Core/SimulationElement/SimulationElement.h"

GISASSimulation::GISASSimulation()
{
    initialize();
}

GISASSimulation::GISASSimulation(const MultiLayer& p_sample) : Simulation2D(p_sample)
{
    initialize();
}

GISASSimulation::GISASSimulation(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder)
    : Simulation2D(p_sample_builder)
{
    initialize();
}

void GISASSimulation::prepareSimulation()
{
    if (m_instrument.getDetectorDimension() != 2)
        throw Exceptions::LogicErrorException(
            "GISASSimulation::prepareSimulation() "
            "-> Error. The detector was not properly configured.");
    getInstrument().initDetector();
    Simulation2D::prepareSimulation();
}

SimulationResult GISASSimulation::result() const
{
    const auto& instrument = getInstrument();
    const auto converter = UnitConverterUtils::createConverterForGISAS(instrument);
    const std::unique_ptr<OutputData<double>> data(
        instrument.createDetectorIntensity(m_sim_elements));
    return SimulationResult(*data, *converter);
}

void GISASSimulation::setBeamParameters(double wavelength, double alpha_i, double phi_i)
{
    if (wavelength <= 0.0)
        throw Exceptions::ClassInitializationException(
            "Simulation::setBeamParameters() -> Error. Incoming wavelength <= 0.");
    m_instrument.setBeamParameters(wavelength, alpha_i, phi_i);
}

size_t GISASSimulation::intensityMapSize() const
{
    auto detector = getInstrument().getDetector();
    if (!detector)
        throw std::runtime_error(
            "Error in GISASSimulation::intensityMapSize: attempt to access non-initialized data.");
    size_t result = 0;
    detector->iterate([&result](IDetector::const_iterator) { ++result; }, true);
    return result;
}

GISASSimulation::GISASSimulation(const GISASSimulation& other) : Simulation2D(other)
{
    initialize();
}

void GISASSimulation::initSimulationElementVector()
{
    auto beam = m_instrument.getBeam();
    m_sim_elements = generateSimulationElements(beam);
    if (m_cache.empty())
        m_cache.resize(m_sim_elements.size(), 0.0);
}

void GISASSimulation::initialize()
{
    setName("GISASSimulation");
}
