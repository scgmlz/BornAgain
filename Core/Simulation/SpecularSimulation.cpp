//  ************************************************************************************************
//
//  BornAgain: simulate and fit reflection and scattering
//
//! @file      Core/Simulation/SpecularSimulation.cpp
//! @brief     Implements class OffSpecularSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Core/Simulation/SpecularSimulation.h"
#include "Base/Axis/PointwiseAxis.h"
#include "Core/Computation/IBackground.h"
#include "Core/Computation/SpecularComputation.h"
#include "Core/Element/SpecularSimulationElement.h"
#include "Core/Scan/AngularSpecScan.h"
#include "Core/Scan/UnitConverter1D.h"
#include "Device/Beam/IFootprintFactor.h"
#include "Device/Detector/SpecularDetector1D.h"
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include "Param/Distrib/Distributions.h"

namespace {

// TODO: remove when pointwise resolution is implemented
std::unique_ptr<AngularSpecScan> mangledScan(const AngularSpecScan& scan, const Beam& beam)
{
    const double wl = beam.wavelength();
    const double angle_shift = beam.direction().alpha();
    std::vector<double> angles = scan.coordinateAxis()->binCenters();
    for (auto& val : angles)
        val += angle_shift;
    auto* result = new AngularSpecScan(wl, PointwiseAxis("alpha_i", std::move(angles)));
    result->setFootprintFactor(scan.footprintFactor());
    result->setWavelengthResolution(*scan.wavelengthResolution());
    result->setAngleResolution(*scan.angleResolution());
    return std::unique_ptr<AngularSpecScan>(result);
}

std::vector<SpecularSimulationElement> generateSimulationElements(const Instrument& instrument,
                                                                  const ISpecularScan& scan)
{
    // TODO: remove if statement when pointwise resolution is implemented
    if (const auto* aScan = dynamic_cast<const AngularSpecScan*>(&scan))
        return mangledScan(*aScan, instrument.beam())->generateSimulationElements(instrument);

    return scan.generateSimulationElements(instrument);
}

} // namespace

//  ************************************************************************************************
//  class SpecularSimulation
//  ************************************************************************************************

SpecularSimulation::SpecularSimulation() : ISimulation()
{
    initialize();
}

SpecularSimulation::SpecularSimulation(const SpecularSimulation& other)
    : ISimulation(other)
    , m_scan(other.m_scan ? other.m_scan->clone() : nullptr)
    , m_sim_elements(other.m_sim_elements)
    , m_cache(other.m_cache)
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
    if (detector().dimension() != 1) // detector must have only one axis
        throw std::runtime_error("Error in SpecularSimulation::prepareSimulation: the detector was "
                                 "not properly configured.");
    instrument().initDetector();
    ISimulation::prepareSimulation();
}

size_t SpecularSimulation::numberOfSimulationElements() const
{
    return m_scan->numberOfSimulationElements();
}

SimulationResult SpecularSimulation::result() const
{
    OutputData<double> data;
    data.addAxis(*coordinateAxis());

    if (!m_sim_elements.empty())
        data.setRawDataVector(m_scan->createIntensities(m_sim_elements));
    else
        data.setAllTo(0.0);

    auto converter = UnitConverter1D::createUnitConverter(*m_scan);
    return SimulationResult(data, *converter);
}

void SpecularSimulation::setScan(const ISpecularScan& scan)
{
    if(m_scan)
        throw std::runtime_error("Scan cannot be set twice");

    // TODO: move inside AngularSpecScan when pointwise resolution is implemented
    if (scan.coordinateAxis()->lowerBound() < 0.0)
        throw std::runtime_error(
            "Error in SpecularSimulation::setScan: minimum value on coordinate axis is negative.");

    m_scan.reset(scan.clone());

    SpecularDetector1D detector(*scan.coordinateAxis());
    instrument().setDetector(detector);

    // TODO: remove when pointwise resolution is implemented
    if (const auto* aScan = dynamic_cast<const AngularSpecScan*>(&scan))
        instrument().setBeamParameters(aScan->wavelength(), 0.0, 0.0);
}

const IAxis* SpecularSimulation::coordinateAxis() const
{
    if (!m_scan || !m_scan->coordinateAxis())
        throw std::runtime_error(
            "Error in SpecularSimulation::getAlphaAxis: coordinate axis was not initialized.");
    return m_scan->coordinateAxis();
}

const IFootprintFactor* SpecularSimulation::footprintFactor() const
{
    return m_scan->footprintFactor();
}

size_t SpecularSimulation::intensityMapSize() const
{
    return m_scan->coordinateAxis()->size();
}

void SpecularSimulation::initSimulationElementVector()
{
    if (!m_scan)
        throw std::runtime_error("Error in SpecularSimulation: beam parameters were not set.");
    m_sim_elements = generateSimulationElements(instrument(), *m_scan);

    if (!m_cache.empty())
        return;
    m_cache.resize(m_sim_elements.size(), 0);
}

std::unique_ptr<IComputation>
SpecularSimulation::generateSingleThreadedComputation(size_t start, size_t n_elements)
{
    ASSERT(start < m_sim_elements.size() && start + n_elements <= m_sim_elements.size());
    const auto& begin = m_sim_elements.begin() + static_cast<long>(start);
    return std::make_unique<SpecularComputation>(*sample(), options(), progress(), begin,
                                                 begin + static_cast<long>(n_elements));
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
    instrument()
        .beam()
        .parameter("InclinationAngle")
        ->setLimits(RealLimits::limited(-M_PI_2, M_PI_2));
}

void SpecularSimulation::normalize(size_t start_ind, size_t n_elements)
{
    const double beam_intensity = beam().intensity();

    std::vector<double> footprints;
    // TODO: use just m_scan when pointwise resolution is implemented
    if (const auto* aScan = dynamic_cast<const AngularSpecScan*>(m_scan.get()))
        footprints = mangledScan(*aScan, beam())->footprint(start_ind, n_elements);
    else
        footprints = m_scan->footprint(start_ind, n_elements);

    for (size_t i = start_ind, k = 0; i < start_ind + n_elements; ++i, ++k) {
        auto& element = m_sim_elements[i];
        element.setIntensity(element.intensity() * beam_intensity * footprints[k]);
    }
}

void SpecularSimulation::addBackgroundIntensity(size_t start_ind, size_t n_elements)
{
    if (!background())
        return;
    for (size_t i = start_ind, stop_point = start_ind + n_elements; i < stop_point; ++i) {
        auto& element = m_sim_elements[i];
        element.setIntensity(background()->addBackground(element.intensity()));
    }
}

void SpecularSimulation::addDataToCache(double weight)
{
    checkCache();
    for (size_t i = 0, size = m_sim_elements.size(); i < size; ++i)
        m_cache[i] += m_sim_elements[i].intensity() * weight;
}

void SpecularSimulation::moveDataFromCache()
{
    checkCache();
    for (size_t i = 0, size = m_sim_elements.size(); i < size; ++i)
        m_sim_elements[i].setIntensity(m_cache[i]);
    m_cache.clear();
    m_cache.shrink_to_fit();
}

std::vector<double> SpecularSimulation::rawResults() const
{
    std::vector<double> result;
    result.resize(m_sim_elements.size());
    for (unsigned i = 0; i < m_sim_elements.size(); ++i)
        result[i] = m_sim_elements[i].intensity();
    return result;
}

void SpecularSimulation::setRawResults(const std::vector<double>& raw_data)
{
    initSimulationElementVector();
    if (raw_data.size() != m_sim_elements.size())
        throw std::runtime_error("SpecularSimulation::setRawResults: size of vector passed as "
                                 "argument doesn't match number of elements in this simulation");
    for (unsigned i = 0; i < raw_data.size(); i++)
        m_sim_elements[i].setIntensity(raw_data[i]);
    transferResultsToIntensityMap();
}

void SpecularSimulation::setAnalyzerProperties(const kvector_t direction, double efficiency,
                           double total_transmission)
{
    if(!m_scan)
        throw std::runtime_error("Scan has not been specified");


    ISimulation::setAnalyzerProperties(direction, efficiency, total_transmission);
}

