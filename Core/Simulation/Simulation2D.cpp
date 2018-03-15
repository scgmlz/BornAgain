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

#include "Simulation2D.h"
#include "DetectorElement.h"
#include "DetectorFunctions.h"
#include "DWBAComputation.h"
#include "Histogram2D.h"
#include "IBackground.h"
#include "SimulationElement.h"

namespace
{
IDetector2D* Detector2D(Instrument& instrument);
}

Simulation2D::Simulation2D(const MultiLayer& p_sample)
    : Simulation(p_sample)
{}

Simulation2D::Simulation2D(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder)
    : Simulation(p_sample_builder)
{}

void Simulation2D::removeMasks()
{
    Detector2D(m_instrument)->removeMasks();
}

void Simulation2D::addMask(const IShape2D& shape, bool mask_value)
{
    Detector2D(m_instrument)->addMask(shape, mask_value);
}

void Simulation2D::maskAll()
{
    Detector2D(m_instrument)->maskAll();
}

void Simulation2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)
{
    Detector2D(m_instrument)->setRegionOfInterest(xlow, ylow, xup, yup);
}

Simulation2D::Simulation2D(const Simulation2D& other)
    : Simulation(other)
    , m_sim_elements(other.m_sim_elements)
    , m_cache(other.m_cache)
{}

void Simulation2D::setDetectorParameters(size_t n_x, double x_min, double x_max,
                                         size_t n_y, double y_min, double y_max)
{
    if (auto detector = Detector2D(m_instrument))
        detector->setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);
    else
        throw std::runtime_error(
            "Error in Simulation2D::setDetectorParameters: wrong detector type");
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
    assert(start < m_sim_elements.size() && start + n_elements <= m_sim_elements.size());
    const auto& begin = m_sim_elements.begin() + static_cast<long>(start);
    return std::make_unique<DWBAComputation>(*sample(), m_options, m_progress, begin,
                                             begin + static_cast<long>(n_elements));
}

std::vector<SimulationElement> Simulation2D::generateSimulationElements(const Beam& beam)
{
    std::vector<SimulationElement> result;

    const double wavelength = beam.getWavelength();
    const double alpha_i = - beam.getAlpha();  // Defined to be always positive in Beam
    const double phi_i = beam.getPhi();
    const Eigen::Matrix2cd& beam_polarization = beam.getPolarization();
    auto detector = Detector2D(m_instrument);
    auto detector_elements = detector->createDetectorElements(beam);

    result.reserve(detector_elements.size());
    for (auto it=detector_elements.begin(); it!=detector_elements.end(); ++it) {
        result.emplace_back(wavelength, alpha_i, phi_i, it->pixel());
        auto& sim_element = result.back();
        sim_element.setPolarization(beam_polarization);
        sim_element.setAnalyzerOperator(it->getAnalyzerOperator());
        if (it->isSpecular())
            sim_element.setSpecular(true);
    }
    return result;
}

void Simulation2D::normalizeIntensity(size_t index, double beam_intensity)
{
    SimulationElement& element = m_sim_elements[index];
    double sin_alpha_i = std::abs(std::sin(element.getAlphaI()));
    if (sin_alpha_i == 0.0)
        sin_alpha_i = 1.0;
    const double solid_angle = element.getSolidAngle();
    element.setIntensity(element.getIntensity() * beam_intensity * solid_angle / sin_alpha_i);
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
    for (unsigned i=0; i<m_sim_elements.size(); i++) {
        m_cache[i] += m_sim_elements[i].getIntensity()*weight;
    }
}

void Simulation2D::moveDataFromCache()
{
    assert(!m_cache.empty());
    if (!m_cache.empty()) {
        for (unsigned i=0; i<m_sim_elements.size(); i++) {
             m_sim_elements[i].setIntensity(m_cache[i]);
        }
        m_cache.clear();
    }
}

std::vector<double> Simulation2D::rawResults() const
{
    std::vector<double> result;
    result.resize(m_sim_elements.size());
    for (unsigned i=0; i<m_sim_elements.size(); ++i) {
        result[i] = m_sim_elements[i].getIntensity();
    }
    return result;
}

void Simulation2D::setRawResults(const std::vector<double>& raw_data)
{
    initSimulationElementVector();
    if (raw_data.size() != m_sim_elements.size())
        throw std::runtime_error("Simulation2D::setRawResults: size of vector passed as "
                                 "argument doesn't match number of elements in this simulation");
    for (unsigned i=0; i<raw_data.size(); i++) {
        m_sim_elements[i].setIntensity(raw_data[i]);
    }
    transferResultsToIntensityMap();
}

namespace
{
IDetector2D* Detector2D(Instrument& instrument)
{
    IDetector2D* p_detector = dynamic_cast<IDetector2D*>(instrument.getDetector());
    if (!p_detector)
        throw std::runtime_error(
            "Error in Simulation2D: wrong detector type");
    return p_detector;
}
}
