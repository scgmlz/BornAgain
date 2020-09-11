// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/DepthProbeSimulation.cpp
//! @brief     Implements class DepthProbeSimulation
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Simulation/DepthProbeSimulation.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Beam/IFootprintFactor.h"
#include "Core/Computation/DepthProbeComputation.h"
#include "Core/Computation/IBackground.h"
#include "Core/Detector/SpecularDetector1D.h"
#include "Core/Intensity/Histogram1D.h"
#include "Core/Intensity/SimpleUnitConverters.h"
#include "Core/Material/MaterialUtils.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"

namespace
{
const RealLimits alpha_limits = RealLimits::limited(0.0, M_PI_2);
const double zero_phi_i = 0.0;
const double zero_alpha_i = 0.0;
} // namespace

DepthProbeSimulation::DepthProbeSimulation() : Simulation()
{
    initialize();
}

DepthProbeSimulation::DepthProbeSimulation(const MultiLayer& sample) : Simulation(sample)
{
    initialize();
}

DepthProbeSimulation::DepthProbeSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder)
    : Simulation(sample_builder)
{
    initialize();
}

DepthProbeSimulation::~DepthProbeSimulation() = default;

DepthProbeSimulation* DepthProbeSimulation::clone() const
{
    return new DepthProbeSimulation(*this);
}

size_t DepthProbeSimulation::numberOfSimulationElements() const
{
    return getAlphaAxis()->size();
}

SimulationResult DepthProbeSimulation::result() const
{
    validityCheck();
    auto data = createIntensityData();
    return SimulationResult(*data, *createUnitConverter().get());
}

void DepthProbeSimulation::setBeamParameters(double lambda, int nbins, double alpha_i_min,
                                             double alpha_i_max, const IFootprintFactor* beam_shape)
{
    FixedBinAxis axis("alpha_i", static_cast<size_t>(nbins), alpha_i_min, alpha_i_max);
    setBeamParameters(lambda, axis, beam_shape);
}

void DepthProbeSimulation::setZSpan(size_t n_bins, double z_min, double z_max)
{
    if (z_max <= z_min)
        throw std::runtime_error("Error in DepthProbeSimulation::setZSpan: maximum on-axis value "
                                 "is less or equal to the minimum one");
    m_z_axis = std::make_unique<FixedBinAxis>("z", n_bins, z_min, z_max);
}

const IAxis* DepthProbeSimulation::getAlphaAxis() const
{
    if (!m_alpha_axis)
        throw std::runtime_error("Error in DepthProbeSimulation::getAlphaAxis: incident angle axis "
                                 "was not initialized.");
    return m_alpha_axis.get();
}

const IAxis* DepthProbeSimulation::getZAxis() const
{
    if (!m_z_axis)
        throw std::runtime_error("Error in DepthProbeSimulation::getZAxis: position axis "
                                 "was not initialized.");
    return m_z_axis.get();
}

size_t DepthProbeSimulation::intensityMapSize() const
{
    if (!m_z_axis || !m_alpha_axis)
        throw std::runtime_error("Error in DepthProbeSimulation::intensityMapSize: attempt to "
                                 "access non-initialized data.");
    return m_z_axis->size() * m_alpha_axis->size();
}

std::unique_ptr<IUnitConverter> DepthProbeSimulation::createUnitConverter() const
{
    return std::make_unique<DepthProbeConverter>(m_instrument.getBeam(), *m_alpha_axis, *m_z_axis);
}

DepthProbeSimulation::DepthProbeSimulation(const DepthProbeSimulation& other)
    : Simulation(other), m_sim_elements(other.m_sim_elements), m_cache(other.m_cache)
{
    if (other.m_alpha_axis)
        m_alpha_axis.reset(other.m_alpha_axis->clone());
    if (other.m_z_axis)
        m_z_axis.reset(other.m_z_axis->clone());
    if (!m_sim_elements.empty())
        for (auto iter = m_sim_elements.begin(); iter != m_sim_elements.end(); ++iter)
            iter->setZPositions(m_alpha_axis.get());
    initialize();
}

void DepthProbeSimulation::setBeamParameters(double lambda, const IAxis& alpha_axis,
                                             const IFootprintFactor* beam_shape)
{
    if (lambda <= 0.0)
        throw std::runtime_error(
            "Error in DepthProbeSimulation::setBeamParameters: wavelength must be positive.");
    if (alpha_axis.getMin() < 0.0)
        throw std::runtime_error(
            "Error in DepthProbeSimulation::setBeamParameters: minimum value on "
            "angle axis is negative.");
    if (alpha_axis.getMin() >= alpha_axis.getMax())
        throw std::runtime_error(
            "Error in DepthProbeSimulation::setBeamParameters: maximal value on "
            "angle axis is less or equal to the minimal one.");
    if (alpha_axis.size() == 0)
        throw std::runtime_error(
            "Error in DepthProbeSimulation::setBeamParameters: angle axis is empty");

    SpecularDetector1D detector(alpha_axis);
    m_instrument.setDetector(detector);
    m_alpha_axis.reset(alpha_axis.clone());

    // beam is initialized with zero-valued angles
    // Zero-valued incident alpha is required for proper
    // taking into account beam resolution effects
    m_instrument.setBeamParameters(lambda, zero_alpha_i, zero_phi_i);

    if (beam_shape)
        m_instrument.getBeam().setFootprintFactor(*beam_shape);
}

void DepthProbeSimulation::initSimulationElementVector()
{
    const auto& beam = m_instrument.getBeam();
    m_sim_elements = generateSimulationElements(beam);

    if (!m_cache.empty())
        return;
    m_cache.resize(m_sim_elements.size(), std::valarray<double>(0.0, getZAxis()->size()));
}

std::vector<DepthProbeElement> DepthProbeSimulation::generateSimulationElements(const Beam& beam)
{
    std::vector<DepthProbeElement> result;

    const double wavelength = beam.getWavelength();
    const double angle_shift = beam.getAlpha();

    const size_t axis_size = getAlphaAxis()->size();
    result.reserve(axis_size);
    for (size_t i = 0; i < axis_size; ++i) {
        double result_angle = incidentAngle(i) + angle_shift;
        result.emplace_back(wavelength, -result_angle, getZAxis());
        if (!alpha_limits.isInRange(result_angle))
            result.back().setCalculationFlag(false); // false = exclude from calculations
    }
    return result;
}

std::unique_ptr<IComputation>
DepthProbeSimulation::generateSingleThreadedComputation(size_t start, size_t n_elements)
{
    ASSERT(start < m_sim_elements.size() && start + n_elements <= m_sim_elements.size());
    const auto& begin = m_sim_elements.begin() + static_cast<long>(start);
    return std::make_unique<DepthProbeComputation>(*sample(), m_options, m_progress, begin,
                                                   begin + static_cast<long>(n_elements));
}

void DepthProbeSimulation::validityCheck() const
{
    const MultiLayer* current_sample = sample();
    if (!current_sample)
        throw std::runtime_error(
            "Error in DepthProbeSimulation::validityCheck: no sample found in the simulation.");

    const size_t data_size = m_sim_elements.size();
    if (data_size != getAlphaAxis()->size())
        throw std::runtime_error(
            "Error in DepthProbeSimulation::validityCheck: length of simulation "
            "element vector is not equal to the number of inclination angles");
}

void DepthProbeSimulation::checkCache() const
{
    if (m_sim_elements.size() != m_cache.size())
        throw std::runtime_error("Error in DepthProbeSimulation: the sizes of simulation element "
                                 "vector and of its cache are different");
}

void DepthProbeSimulation::validateParametrization(const ParameterDistribution& par_distr) const
{
    const bool zero_mean = par_distr.getDistribution()->getMean() == 0.0;
    if (zero_mean)
        return;

    std::unique_ptr<ParameterPool> parameter_pool(createParameterTree());
    const std::vector<RealParameter*> names =
        parameter_pool->getMatchedParameters(par_distr.getMainParameterName());
    for (const auto par : names)
        if (par->getName().find("InclinationAngle") != std::string::npos && !zero_mean)
            throw std::runtime_error("Error in DepthProbeSimulation: parameter distribution of "
                                     "beam inclination angle should have zero mean.");
}

void DepthProbeSimulation::initialize()
{
    setName("DepthProbeSimulation");

    // allow for negative inclinations in the beam of specular simulation
    // it is required for proper averaging in the case of divergent beam
    auto inclination = m_instrument.getBeam().parameter("InclinationAngle");
    inclination->setLimits(RealLimits::limited(-M_PI_2, M_PI_2));
}

void DepthProbeSimulation::normalize(size_t start_ind, size_t n_elements)
{
    const double beam_intensity = getBeamIntensity();
    if (beam_intensity == 0.0)
        return; // no normalization when beam intensity is zero
    for (size_t i = start_ind, stop_point = start_ind + n_elements; i < stop_point; ++i) {
        auto& element = m_sim_elements[i];
        const double alpha_i = -element.getAlphaI();
        const auto footprint = m_instrument.getBeam().footprintFactor();
        double intensity_factor = beam_intensity;
        if (footprint != nullptr)
            intensity_factor = intensity_factor * footprint->calculate(alpha_i);
        element.setIntensities(element.getIntensities() * intensity_factor);
    }
}

void DepthProbeSimulation::addBackGroundIntensity(size_t, size_t)
{
    if (!mP_background)
        return;
    throw std::runtime_error("Error in DepthProbeSimulation::addBackGroundIntensity: background is "
                             "not allowed for this type of simulation");
}

void DepthProbeSimulation::addDataToCache(double weight)
{
    checkCache();
    for (size_t i = 0, size = m_sim_elements.size(); i < size; ++i)
        m_cache[i] += m_sim_elements[i].getIntensities() * weight;
}

void DepthProbeSimulation::moveDataFromCache()
{
    checkCache();
    for (size_t i = 0, size = m_sim_elements.size(); i < size; ++i)
        m_sim_elements[i].setIntensities(std::move(m_cache[i]));
    m_cache.clear();
    m_cache.shrink_to_fit();
}

double DepthProbeSimulation::incidentAngle(size_t index) const
{
    return m_alpha_axis->getBin(index).getMidPoint();
}

std::unique_ptr<OutputData<double>> DepthProbeSimulation::createIntensityData() const
{
    std::unique_ptr<OutputData<double>> result = std::make_unique<OutputData<double>>();
    result->addAxis(*getAlphaAxis());
    result->addAxis(*getZAxis());

    std::vector<double> rawData;
    rawData.reserve(getAlphaAxis()->size() * getZAxis()->size());
    for (size_t i = 0, size = m_sim_elements.size(); i < size; ++i) {
        const std::valarray<double>& fixed_angle_result = m_sim_elements[i].getIntensities();
        rawData.insert(rawData.end(), std::begin(fixed_angle_result), std::end(fixed_angle_result));
    }
    result->setRawDataVector(rawData);

    return result;
}

std::vector<double> DepthProbeSimulation::rawResults() const
{
    validityCheck();
    const size_t z_size = getZAxis()->size();
    const size_t alpha_size = getAlphaAxis()->size();

    std::vector<double> result;
    result.reserve(alpha_size * z_size);
    for (size_t i = 0; i < alpha_size; ++i) {
        if (m_sim_elements[i].size() != z_size)
            throw std::runtime_error("Error in DepthProbeSimulation::rawResults: simulation "
                                     "element size is not equal to the size of the position axis");
        const auto& intensities = m_sim_elements[i].getIntensities();
        result.insert(result.end(), std::begin(intensities), std::end(intensities));
    }

    return result;
}

void DepthProbeSimulation::setRawResults(const std::vector<double>& raw_results)
{
    validityCheck();
    const size_t z_size = getZAxis()->size();
    const size_t alpha_size = getAlphaAxis()->size();

    if (raw_results.size() != z_size * alpha_size)
        throw std::runtime_error(
            "Error in DepthProbeSimulation::setRawResults: the vector to set is of invalid size");

    const double* raw_array = raw_results.data();
    for (size_t i = 0; i < alpha_size; ++i) {
        std::valarray<double> fixed_angle_result(raw_array, z_size);
        m_sim_elements[i].setIntensities(std::move(fixed_angle_result));
        raw_array += z_size;
    }
}
