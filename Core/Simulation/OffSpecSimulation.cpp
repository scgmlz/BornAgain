// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/OffSpecSimulation.cpp
//! @brief     Implements class OffSpecSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Simulation/OffSpecSimulation.h"
#include "Core/Computation/DWBAComputation.h"
#include "Core/Intensity/Histogram2D.h"
#include "Core/Intensity/SimpleUnitConverters.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/Distributions.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/SimulationElement/SimulationElement.h"

OffSpecSimulation::OffSpecSimulation()
{
    initialize();
}

OffSpecSimulation::OffSpecSimulation(const MultiLayer& p_sample) : Simulation2D(p_sample)
{
    initialize();
}

OffSpecSimulation::OffSpecSimulation(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder)
    : Simulation2D(p_sample_builder)
{
    initialize();
}

void OffSpecSimulation::prepareSimulation()
{
    checkInitialization();
    Simulation2D::prepareSimulation();
}

size_t OffSpecSimulation::numberOfSimulationElements() const
{
    checkInitialization();
    return Simulation2D::numberOfSimulationElements() * mP_alpha_i_axis->size();
}

SimulationResult OffSpecSimulation::result() const
{
    auto data = std::unique_ptr<OutputData<double>>(m_intensity_map.clone());
    auto p_det = dynamic_cast<const IDetector2D*>(getInstrument().getDetector());
    if (p_det) {
        OffSpecularConverter converter(*p_det, getInstrument().getBeam(), *mP_alpha_i_axis);
        return SimulationResult(*data, converter);
    }
    throw std::runtime_error("Error in OffSpecSimulation::result: "
                             "wrong or absent detector type");
}

void OffSpecSimulation::setBeamParameters(double wavelength, const IAxis& alpha_axis, double phi_i)
{
    mP_alpha_i_axis.reset(alpha_axis.clone());
    if (alpha_axis.size() < 1)
        throw Exceptions::ClassInitializationException("OffSpecSimulation::prepareSimulation() "
                                                       "-> Error. Incoming alpha range size < 1.");
    const double alpha_zero = alpha_axis.getMin();
    m_instrument.setBeamParameters(wavelength, alpha_zero, phi_i);
    updateIntensityMap();
}

const IAxis* OffSpecSimulation::beamAxis() const
{
    return mP_alpha_i_axis.get();
}

std::unique_ptr<IUnitConverter> OffSpecSimulation::createUnitConverter() const
{
    const IDetector* detector = getInstrument().getDetector();
    const IAxis* axis = beamAxis();
    if (!detector || !axis)
        throw std::runtime_error("Error in OffSpecSimulation::createUnitConverter: missing detector"
                                 "or inclination angle axis");
    return std::make_unique<OffSpecularConverter>(static_cast<const IDetector2D&>(*detector),
                                                  getInstrument().getBeam(), *axis);
}

size_t OffSpecSimulation::intensityMapSize() const
{
    checkInitialization();
    return mP_alpha_i_axis->size() * m_instrument.getDetectorAxis(1).size();
}

OffSpecSimulation::OffSpecSimulation(const OffSpecSimulation& other) : Simulation2D(other)
{
    if (other.mP_alpha_i_axis)
        mP_alpha_i_axis.reset(other.mP_alpha_i_axis->clone());
    m_intensity_map.copyFrom(other.m_intensity_map);
    initialize();
}

void OffSpecSimulation::initSimulationElementVector()
{
    m_sim_elements.clear();
    Beam beam = m_instrument.getBeam();
    const double wavelength = beam.getWavelength();
    const double phi_i = beam.getPhi();

    for (size_t i = 0; i < mP_alpha_i_axis->size(); ++i) {
        // Incoming angle by convention defined as positive:
        double alpha_i = mP_alpha_i_axis->getBin(i).getMidPoint();
        double total_alpha = alpha_i;
        beam.setCentralK(wavelength, total_alpha, phi_i);
        auto sim_elements_i = generateSimulationElements(beam);
        m_sim_elements.insert(m_sim_elements.end(), std::make_move_iterator(sim_elements_i.begin()),
                              std::make_move_iterator(sim_elements_i.end()));
    }
    if (m_cache.empty())
        m_cache.resize(m_sim_elements.size(), 0.0);
}

void OffSpecSimulation::validateParametrization(const ParameterDistribution& par_distr) const
{
    const bool zero_mean = par_distr.getDistribution()->getMean() == 0.0;
    if (zero_mean)
        return;

    std::unique_ptr<ParameterPool> parameter_pool(createParameterTree());
    const std::vector<RealParameter*> names =
        parameter_pool->getMatchedParameters(par_distr.getMainParameterName());
    for (const auto par : names)
        if (par->getName().find("InclinationAngle") != std::string::npos && !zero_mean)
            throw std::runtime_error("Error in OffSpecSimulation: parameter distribution of "
                                     "beam inclination angle should have zero mean.");
}

void OffSpecSimulation::transferResultsToIntensityMap()
{
    checkInitialization();
    const IAxis& phi_axis = m_instrument.getDetectorAxis(0);
    size_t phi_f_size = phi_axis.size();
    if (phi_f_size * m_intensity_map.getAllocatedSize() != m_sim_elements.size())
        throw Exceptions::RuntimeErrorException(
            "OffSpecSimulation::transferResultsToIntensityMap: "
            "intensity map size does not conform to number of calculated intensities");
    for (size_t i = 0; i < mP_alpha_i_axis->size(); ++i)
        transferDetectorImage(i);
}

void OffSpecSimulation::updateIntensityMap()
{
    m_intensity_map.clear();
    if (mP_alpha_i_axis)
        m_intensity_map.addAxis(*mP_alpha_i_axis);
    size_t detector_dimension = m_instrument.getDetectorDimension();
    if (detector_dimension == 2)
        m_intensity_map.addAxis(m_instrument.getDetectorAxis(1));
    m_intensity_map.setAllTo(0.);
}

void OffSpecSimulation::transferDetectorImage(size_t index)
{
    OutputData<double> detector_image;
    size_t detector_dimension = m_instrument.getDetectorDimension();
    for (size_t dim = 0; dim < detector_dimension; ++dim)
        detector_image.addAxis(m_instrument.getDetectorAxis(dim));
    size_t detector_size = detector_image.getAllocatedSize();
    for (size_t i = 0; i < detector_size; ++i)
        detector_image[i] = m_sim_elements[index * detector_size + i].getIntensity();
    m_instrument.applyDetectorResolution(&detector_image);
    size_t y_axis_size = m_instrument.getDetectorAxis(1).size();
    for (size_t i = 0; i < detector_size; ++i)
        m_intensity_map[index * y_axis_size + i % y_axis_size] += detector_image[i];
}

void OffSpecSimulation::checkInitialization() const
{
    if (!mP_alpha_i_axis || mP_alpha_i_axis->size() < 1)
        throw Exceptions::ClassInitializationException("OffSpecSimulation::checkInitialization() "
                                                       "Incoming alpha range not configured.");
    if (m_instrument.getDetectorDimension() != 2)
        throw Exceptions::RuntimeErrorException(
            "OffSpecSimulation::checkInitialization: detector is not two-dimensional");
}

void OffSpecSimulation::initialize()
{
    setName("OffSpecSimulation");
}
