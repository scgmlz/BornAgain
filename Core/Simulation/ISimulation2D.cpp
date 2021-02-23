//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Core/Simulation/ISimulation2D.cpp
//! @brief     Implements interface ISimulation2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Simulation/ISimulation2D.h"
#include "Base/Pixel/SimulationElement.h"
#include "Base/Utils/Assert.h"
#include "Core/Computation/DWBAComputation.h"
#include "Core/Computation/IBackground.h"
#include "Device/Detector/DetectorContext.h"

ISimulation2D::ISimulation2D(const Beam& beam, const MultiLayer& sample, const IDetector& detector)
    : ISimulation(beam, sample, detector)
{
}

#ifndef SWIG
ISimulation2D::ISimulation2D(const Beam& beam, const IDetector& detector)
    : ISimulation(beam, detector)
{
}
#endif // SWIG

ISimulation2D::ISimulation2D() = default;

ISimulation2D::~ISimulation2D() = default;

IDetector2D& ISimulation2D::detector2D()
{
    ASSERT(getDetector());
    IDetector2D* p = dynamic_cast<IDetector2D*>(getDetector());
    ASSERT(p);
    return *p;
}

const IDetector2D& ISimulation2D::detector2D() const
{
    ASSERT(getDetector());
    const IDetector2D* p = dynamic_cast<const IDetector2D*>(getDetector());
    ASSERT(p);
    return *p;
}

void ISimulation2D::prepareSimulation()
{
    ISimulation::prepareSimulation();
    m_detector_context = detector2D().createContext();
}

void ISimulation2D::addMask(const IShape2D& shape, bool mask_value)
{
    detector2D().addMask(shape, mask_value);
}

void ISimulation2D::maskAll()
{
    detector2D().maskAll();
}

void ISimulation2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)
{
    detector2D().setRegionOfInterest(xlow, ylow, xup, yup);
}

ISimulation2D::ISimulation2D(const ISimulation2D& other)
    : ISimulation(other), m_sim_elements(other.m_sim_elements), m_cache(other.m_cache)
{
}

size_t ISimulation2D::numberOfSimulationElements() const
{
    if (!m_detector_context)
        throw std::runtime_error("Error in numberOfSimulationElements(): no detector context");
    return m_detector_context->numberOfSimulationElements();
}

void ISimulation2D::setDetectorParameters(size_t n_x, double x_min, double x_max, size_t n_y,
                                          double y_min, double y_max)
{
    detector2D().setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);
    updateIntensityMap();
}

void ISimulation2D::setDetector(const IDetector2D& detector)
{
    instrument().setDetector(detector);
    initUnitConverter();
}

std::unique_ptr<IComputation> ISimulation2D::generateSingleThreadedComputation(size_t start,
                                                                               size_t n_elements)
{
    ASSERT(start < m_sim_elements.size() && start + n_elements <= m_sim_elements.size());
    const auto& begin = m_sim_elements.begin() + static_cast<long>(start);
    const auto polarized =
        this->detector().detectionProperties().analyzerDirection() != kvector_t{};
    return std::make_unique<DWBAComputation>(*sample(), options(), progress(), begin,
                                             begin + static_cast<long>(n_elements), polarized);
}

std::vector<SimulationElement> ISimulation2D::generateSimulationElements(const Beam& beam)
{
    const double wavelength = beam.wavelength();
    const double alpha_i = -beam.direction().alpha(); // Defined to be always positive in Beam
    const double phi_i = beam.direction().phi();
    const Eigen::Matrix2cd beam_polarization = beam.getPolarization();

    const IDetector2D& detector = detector2D();
    const Eigen::Matrix2cd analyzer_operator = detector.detectionProperties().analyzerOperator();
    const size_t spec_index = detector.indexOfSpecular(beam);

    const size_t N = m_detector_context->numberOfSimulationElements();

    std::vector<SimulationElement> result;
    result.reserve(N);
    for (size_t element_index = 0; element_index < N; ++element_index) {
        SimulationElement element(wavelength, alpha_i, phi_i,
                                  m_detector_context->createPixel(element_index), beam_polarization,
                                  analyzer_operator,
                                  m_detector_context->detectorIndex(element_index) == spec_index);
        result.emplace_back(std::move(element));
    }
    return result;
}

void ISimulation2D::normalize(size_t start_ind, size_t n_elements)
{
    const double beam_intensity = beam().intensity();
    for (size_t i = start_ind, stop_point = start_ind + n_elements; i < stop_point; ++i) {
        SimulationElement& element = m_sim_elements[i];
        double sin_alpha_i = std::abs(std::sin(element.getAlphaI()));
        if (sin_alpha_i == 0.0) {
            element.setIntensity(0);
            continue;
        }
        const double solid_angle = element.solidAngle();
        element.setIntensity(element.intensity() * beam_intensity * solid_angle / sin_alpha_i);
    }
}

void ISimulation2D::addBackgroundIntensity(size_t start_ind, size_t n_elements)
{
    if (!background())
        return;
    for (size_t i = start_ind, stop_point = start_ind + n_elements; i < stop_point; ++i) {
        SimulationElement& element = m_sim_elements[i];
        element.setIntensity(background()->addBackground(element.intensity()));
    }
}

void ISimulation2D::addDataToCache(double weight)
{
    if (m_sim_elements.size() != m_cache.size())
        throw std::runtime_error("Error in ISimulation2D::addDataToCache(double): cache size"
                                 " not the same as element size");
    for (unsigned i = 0; i < m_sim_elements.size(); i++)
        m_cache[i] += m_sim_elements[i].intensity() * weight;
}

void ISimulation2D::moveDataFromCache()
{
    ASSERT(!m_cache.empty());
    if (!m_cache.empty()) {
        for (unsigned i = 0; i < m_sim_elements.size(); i++)
            m_sim_elements[i].setIntensity(m_cache[i]);
        m_cache.clear();
    }
}

std::vector<double> ISimulation2D::rawResults() const
{
    std::vector<double> result;
    result.resize(m_sim_elements.size());
    for (unsigned i = 0; i < m_sim_elements.size(); ++i)
        result[i] = m_sim_elements[i].intensity();
    return result;
}

void ISimulation2D::setRawResults(const std::vector<double>& raw_data)
{
    initSimulationElementVector();
    if (raw_data.size() != m_sim_elements.size())
        throw std::runtime_error("ISimulation2D::setRawResults: size of vector passed as "
                                 "argument doesn't match number of elements in this simulation");
    for (unsigned i = 0; i < raw_data.size(); i++)
        m_sim_elements[i].setIntensity(raw_data[i]);
    transferResultsToIntensityMap();
}
