// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/Simulation2D.cpp
//! @brief     Implements class Simulation2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Simulation/Simulation2D.h"
#include "Core/Computation/DWBAComputation.h"
#include "Core/Computation/IBackground.h"
#include "Core/Detector/DetectorContext.h"
#include "Core/Detector/DetectorFunctions.h"
#include "Core/Intensity/Histogram2D.h"
#include "Core/SimulationElement/SimulationElement.h"

Simulation2D::Simulation2D() = default;

Simulation2D::Simulation2D(const MultiLayer& p_sample) : Simulation(p_sample) {}

Simulation2D::Simulation2D(const std::shared_ptr<ISampleBuilder> p_sample_builder)
    : Simulation(p_sample_builder)
{
}

Simulation2D::~Simulation2D() = default;

void Simulation2D::prepareSimulation()
{
    Simulation::prepareSimulation();
    m_detector_context = m_instrument.detector2D().createContext();
}

void Simulation2D::removeMasks()
{
    m_instrument.detector2D().removeMasks();
}

void Simulation2D::addMask(const IShape2D& shape, bool mask_value)
{
    m_instrument.detector2D().addMask(shape, mask_value);
}

void Simulation2D::maskAll()
{
    m_instrument.detector2D().maskAll();
}

void Simulation2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)
{
    m_instrument.detector2D().setRegionOfInterest(xlow, ylow, xup, yup);
}

Simulation2D::Simulation2D(const Simulation2D& other)
    : Simulation(other), m_sim_elements(other.m_sim_elements), m_cache(other.m_cache)
{
}

size_t Simulation2D::numberOfSimulationElements() const
{
    if (!m_detector_context)
        throw std::runtime_error("Error in numberOfSimulationElements(): no detector context");
    return m_detector_context->numberOfSimulationElements();
}

void Simulation2D::setDetectorParameters(size_t n_x, double x_min, double x_max, size_t n_y,
                                         double y_min, double y_max)
{
    m_instrument.detector2D().setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);
    updateIntensityMap();
}

void Simulation2D::setDetector(const IDetector2D& detector)
{
    m_instrument.setDetector(detector);
    initUnitConverter();
}

std::unique_ptr<IComputation> Simulation2D::generateSingleThreadedComputation(size_t start,
                                                                              size_t n_elements)
{
    ASSERT(start < m_sim_elements.size() && start + n_elements <= m_sim_elements.size());
    const auto& begin = m_sim_elements.begin() + static_cast<long>(start);
    return std::make_unique<DWBAComputation>(*sample(), m_options, m_progress, begin,
                                             begin + static_cast<long>(n_elements));
}

std::vector<SimulationElement> Simulation2D::generateSimulationElements(const Beam& beam)
{
    const double wavelength = beam.getWavelength();
    const double alpha_i = -beam.getAlpha(); // Defined to be always positive in Beam
    const double phi_i = beam.getPhi();
    const Eigen::Matrix2cd beam_polarization = beam.getPolarization();

    const IDetector2D& detector = m_instrument.detector2D();
    const Eigen::Matrix2cd analyzer_operator = detector.detectionProperties().analyzerOperator();
    const size_t spec_index = detector.indexOfSpecular(beam);

    const size_t N = m_detector_context->numberOfSimulationElements();

    std::vector<SimulationElement> result;
    result.reserve(N);
    for (size_t element_index = 0; element_index < N; ++element_index) {
        SimulationElement element(wavelength, alpha_i, phi_i,
                                  m_detector_context->createPixel(element_index));
        element.setPolarization(beam_polarization);
        element.setAnalyzerOperator(analyzer_operator);
        if (m_detector_context->detectorIndex(element_index) == spec_index)
            element.setSpecular(true);
        result.emplace_back(std::move(element));
    }
    return result;
}

void Simulation2D::normalize(size_t start_ind, size_t n_elements)
{
    const double beam_intensity = getBeamIntensity();
    if (beam_intensity == 0.0)
        return; // no normalization when beam intensity is zero
    for (size_t i = start_ind, stop_point = start_ind + n_elements; i < stop_point; ++i) {
        SimulationElement& element = m_sim_elements[i];
        double sin_alpha_i = std::abs(std::sin(element.getAlphaI()));
        if (sin_alpha_i == 0.0)
            sin_alpha_i = 1.0;
        const double solid_angle = element.getSolidAngle();
        element.setIntensity(element.getIntensity() * beam_intensity * solid_angle / sin_alpha_i);
    }
}

void Simulation2D::addBackGroundIntensity(size_t start_ind, size_t n_elements)
{
    if (!mP_background)
        return;
    for (size_t i = start_ind, stop_point = start_ind + n_elements; i < stop_point; ++i) {
        SimulationElement& element = m_sim_elements[i];
        element.setIntensity(mP_background->addBackGround(element.getIntensity()));
    }
}

void Simulation2D::addDataToCache(double weight)
{
    if (m_sim_elements.size() != m_cache.size())
        throw std::runtime_error("Error in Simulation2D::addDataToCache(double): cache size"
                                 " not the same as element size");
    for (unsigned i = 0; i < m_sim_elements.size(); i++)
        m_cache[i] += m_sim_elements[i].getIntensity() * weight;
}

void Simulation2D::moveDataFromCache()
{
    ASSERT(!m_cache.empty());
    if (!m_cache.empty()) {
        for (unsigned i = 0; i < m_sim_elements.size(); i++)
            m_sim_elements[i].setIntensity(m_cache[i]);
        m_cache.clear();
    }
}

std::vector<double> Simulation2D::rawResults() const
{
    std::vector<double> result;
    result.resize(m_sim_elements.size());
    for (unsigned i = 0; i < m_sim_elements.size(); ++i)
        result[i] = m_sim_elements[i].getIntensity();
    return result;
}

void Simulation2D::setRawResults(const std::vector<double>& raw_data)
{
    initSimulationElementVector();
    if (raw_data.size() != m_sim_elements.size())
        throw std::runtime_error("Simulation2D::setRawResults: size of vector passed as "
                                 "argument doesn't match number of elements in this simulation");
    for (unsigned i = 0; i < raw_data.size(); i++)
        m_sim_elements[i].setIntensity(raw_data[i]);
    transferResultsToIntensityMap();
}
