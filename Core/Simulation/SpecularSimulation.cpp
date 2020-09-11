// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/SpecularSimulation.cpp
//! @brief     Implements class OffSpecSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Simulation/SpecularSimulation.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Beam/IFootprintFactor.h"
#include "Core/Binning/PointwiseAxis.h"
#include "Core/Computation/IBackground.h"
#include "Core/Computation/SpecularComputation.h"
#include "Core/Detector/SpecularDetector1D.h"
#include "Core/Instrument/AngularSpecScan.h"
#include "Core/Instrument/ISpecularScan.h"
#include "Core/Intensity/Histogram1D.h"
#include "Core/Intensity/UnitConverter1D.h"
#include "Core/Material/MaterialUtils.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Multilayer/SpecularSimulationElement.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"

namespace
{
// TODO: remove when pointwise resolution is implemented
std::unique_ptr<ISpecularScan> mangledDataHandler(const ISpecularScan& data_handler,
                                                  const Beam& beam);

const RealLimits alpha_limits = RealLimits::limited(0.0, M_PI_2);
const double zero_phi_i = 0.0;
const double zero_alpha_i = 0.0;
} // namespace

SpecularSimulation::SpecularSimulation() : Simulation()
{
    initialize();
}

SpecularSimulation::SpecularSimulation(const MultiLayer& sample) : Simulation(sample)
{
    initialize();
}

SpecularSimulation::SpecularSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder)
    : Simulation(sample_builder)
{
    initialize();
}

SpecularSimulation::~SpecularSimulation() = default;

SpecularSimulation* SpecularSimulation::clone() const
{
    return new SpecularSimulation(*this);
}

void SpecularSimulation::prepareSimulation()
{
    if (m_instrument.getDetectorDimension() != 1) // detector must have only one axis
        throw std::runtime_error("Error in SpecularSimulation::prepareSimulation: the detector was "
                                 "not properly configured.");
    getInstrument().initDetector();
    Simulation::prepareSimulation();
}

size_t SpecularSimulation::numberOfSimulationElements() const
{
    return m_data_handler->numberOfSimulationElements();
}

SimulationResult SpecularSimulation::result() const
{
    auto data = createIntensityData();
    auto converter = UnitConverter1D::createUnitConverter(*m_data_handler);
    return SimulationResult(*data, *converter);
}

void SpecularSimulation::setScan(const ISpecularScan& scan)
{
    // TODO: move inside AngularSpecScan when pointwise resolution is implemented
    if (scan.coordinateAxis()->getMin() < 0.0)
        throw std::runtime_error(
            "Error in SpecularSimulation::setScan: minimum value on coordinate axis is negative.");

    m_data_handler.reset(scan.clone());

    SpecularDetector1D detector(*scan.coordinateAxis());
    m_instrument.setDetector(detector);

    // TODO: remove when pointwise resolution is implemented
    if (scan.dataType() == ISpecularScan::angle) {
        const auto& angular_scan = static_cast<const AngularSpecScan&>(scan);
        m_instrument.setBeamParameters(angular_scan.wavelength(), zero_alpha_i, zero_phi_i);
    }
}

const IAxis* SpecularSimulation::coordinateAxis() const
{
    if (!m_data_handler || !m_data_handler->coordinateAxis())
        throw std::runtime_error(
            "Error in SpecularSimulation::getAlphaAxis: coordinate axis was not initialized.");
    return m_data_handler->coordinateAxis();
}

const IFootprintFactor* SpecularSimulation::footprintFactor() const
{
    return m_data_handler->footprintFactor();
}

size_t SpecularSimulation::intensityMapSize() const
{
    return m_data_handler->coordinateAxis()->size();
}

void SpecularSimulation::initSimulationElementVector()
{
    const auto& beam = m_instrument.getBeam();
    m_sim_elements = generateSimulationElements(beam);

    if (!m_cache.empty())
        return;
    m_cache.resize(m_sim_elements.size(), 0);
}

std::vector<SpecularSimulationElement>
SpecularSimulation::generateSimulationElements(const Beam& beam)
{
    if (!m_data_handler)
        throw std::runtime_error("Error in SpecularSimulation::generateSimulationElements: beam "
                                 "parameters were not set.");

    std::vector<SpecularSimulationElement> elements;

    // TODO: remove if-else statement when pointwise resolution is implemented
    if (m_data_handler->dataType() == ISpecularScan::angle)
        elements = mangledDataHandler(*m_data_handler, beam)->generateSimulationElements();
    else
        elements = m_data_handler->generateSimulationElements();

    // add polarization and analyzer operators
    const auto& polarization = beam.getPolarization();
    const auto& analyzer = m_instrument.getDetector()->detectionProperties().analyzerOperator();

    for (auto& elem : elements)
        elem.setPolarizationHandler({polarization, analyzer});

    return elements;
}

std::unique_ptr<IComputation>
SpecularSimulation::generateSingleThreadedComputation(size_t start, size_t n_elements)
{
    ASSERT(start < m_sim_elements.size() && start + n_elements <= m_sim_elements.size());
    const auto& begin = m_sim_elements.begin() + static_cast<long>(start);
    return std::make_unique<SpecularComputation>(*sample(), m_options, m_progress, begin,
                                                 begin + static_cast<long>(n_elements));
}

SpecularSimulation::SpecularSimulation(const SpecularSimulation& other)
    : Simulation(other),
      m_data_handler(other.m_data_handler ? other.m_data_handler->clone() : nullptr),
      m_sim_elements(other.m_sim_elements), m_cache(other.m_cache)
{
    initialize();
}

void SpecularSimulation::checkCache() const
{
    if (m_sim_elements.size() != m_cache.size())
        throw std::runtime_error("Error in SpecularSimulation: the sizes of simulation element "
                                 "vector and of its cache are different");
}

void SpecularSimulation::validateParametrization(const ParameterDistribution& par_distr) const
{
    const bool zero_mean = par_distr.getDistribution()->getMean() == 0.0;
    if (zero_mean)
        return;

    std::unique_ptr<ParameterPool> parameter_pool(createParameterTree());
    const std::vector<RealParameter*> names =
        parameter_pool->getMatchedParameters(par_distr.getMainParameterName());
    for (const auto par : names)
        if (par->getName().find("InclinationAngle") != std::string::npos && !zero_mean)
            throw std::runtime_error("Error in SpecularSimulation: parameter distribution of "
                                     "beam inclination angle should have zero mean.");
}

void SpecularSimulation::initialize()
{
    setName("SpecularSimulation");

    // allow for negative inclinations in the beam of specular simulation
    // it is required for proper averaging in the case of divergent beam
    auto inclination = m_instrument.getBeam().parameter("InclinationAngle");
    inclination->setLimits(RealLimits::limited(-M_PI_2, M_PI_2));
}

void SpecularSimulation::normalize(size_t start_ind, size_t n_elements)
{
    const double beam_intensity = getBeamIntensity();
    if (beam_intensity == 0.0)
        return; // no normalization when beam intensity is zero

    std::vector<double> footprints;
    // TODO: use just m_data_handler when pointwise resolution is implemented
    if (m_data_handler->dataType() == ISpecularScan::angle)
        footprints = mangledDataHandler(*m_data_handler, getInstrument().getBeam())
                         ->footprint(start_ind, n_elements);
    else
        footprints = m_data_handler->footprint(start_ind, n_elements);

    for (size_t i = start_ind, k = 0; i < start_ind + n_elements; ++i, ++k) {
        auto& element = m_sim_elements[i];
        element.setIntensity(element.getIntensity() * beam_intensity * footprints[k]);
    }
}

void SpecularSimulation::addBackGroundIntensity(size_t start_ind, size_t n_elements)
{
    if (!mP_background)
        return;
    for (size_t i = start_ind, stop_point = start_ind + n_elements; i < stop_point; ++i) {
        auto& element = m_sim_elements[i];
        element.setIntensity(mP_background->addBackGround(element.getIntensity()));
    }
}

void SpecularSimulation::addDataToCache(double weight)
{
    checkCache();
    for (size_t i = 0, size = m_sim_elements.size(); i < size; ++i)
        m_cache[i] += m_sim_elements[i].getIntensity() * weight;
}

void SpecularSimulation::moveDataFromCache()
{
    checkCache();
    for (size_t i = 0, size = m_sim_elements.size(); i < size; ++i)
        m_sim_elements[i].setIntensity(m_cache[i]);
    m_cache.clear();
    m_cache.shrink_to_fit();
}

std::unique_ptr<OutputData<double>> SpecularSimulation::createIntensityData() const
{
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    result->addAxis(*coordinateAxis());

    if (!m_sim_elements.empty()) {
        std::vector<double> data = m_data_handler->createIntensities(m_sim_elements);
        result->setRawDataVector(data);
    } else
        result->setAllTo(0.0);

    return result;
}

std::vector<double> SpecularSimulation::rawResults() const
{
    std::vector<double> result;
    result.resize(m_sim_elements.size());
    for (unsigned i = 0; i < m_sim_elements.size(); ++i) {
        result[i] = m_sim_elements[i].getIntensity();
    }
    return result;
}

void SpecularSimulation::setRawResults(const std::vector<double>& raw_data)
{
    initSimulationElementVector();
    if (raw_data.size() != m_sim_elements.size())
        throw std::runtime_error("SpecularSimulation::setRawResults: size of vector passed as "
                                 "argument doesn't match number of elements in this simulation");
    for (unsigned i = 0; i < raw_data.size(); i++) {
        m_sim_elements[i].setIntensity(raw_data[i]);
    }
    transferResultsToIntensityMap();
}

namespace
{
// TODO: remove when pointwise resolution is implemented
std::unique_ptr<ISpecularScan> mangledDataHandler(const ISpecularScan& data_handler,
                                                  const Beam& beam)
{
    if (data_handler.dataType() != ISpecularScan::angle)
        throw std::runtime_error("Error in mangledDataHandler: invalid usage");
    auto& scan = static_cast<const AngularSpecScan&>(data_handler);

    const double wl = beam.getWavelength();
    const double angle_shift = beam.getAlpha();
    std::vector<double> angles = scan.coordinateAxis()->getBinCenters();
    for (auto& val : angles)
        val += angle_shift;
    auto result =
        std::make_unique<AngularSpecScan>(wl, PointwiseAxis("alpha_i", std::move(angles)));
    result->setFootprintFactor(scan.footprintFactor());
    result->setWavelengthResolution(*scan.wavelengthResolution());
    result->setAngleResolution(*scan.angleResolution());
    return std::unique_ptr<ISpecularScan>(result.release());
}
} // namespace
