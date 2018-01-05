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

#include "SpecularSimulation.h"
#include "IMultiLayerBuilder.h"
#include "MultiLayer.h"
#include "SpecularMatrix.h"
#include "MaterialUtils.h"
#include "Histogram1D.h"
#include "OutputData.h"
#include "SpecularComputation.h"
#include "SpecularDetector1D.h"

SpecularSimulation::SpecularSimulation()
{
    initialize();
}

SpecularSimulation::SpecularSimulation(const MultiLayer& sample)
    : SimulationImpl(sample)
{
    initialize();
}

SpecularSimulation::SpecularSimulation(const std::shared_ptr<IMultiLayerBuilder> sample_builder)
    : SimulationImpl(sample_builder)
{
    initialize();
}

SpecularSimulation::SpecularSimulation(const SpecularSimulation& other)
    : SimulationImpl(other)
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
    return getInstrument().getDetector()->numberOfSimulationElements();
}

void SpecularSimulation::setBeamParameters(double lambda, const IAxis& alpha_axis, double phi_i)
{
    SpecularDetector1D detector(alpha_axis);
    m_instrument.setDetector(detector);
    m_instrument.setBeamParameters(lambda, alpha_axis[0], phi_i);
}

void SpecularSimulation::setBeamParameters(double lambda, int nbins, double alpha_i_min,
                                           double alpha_i_max, double phi_i)
{
    FixedBinAxis axis("alpha_i", nbins, alpha_i_min, alpha_i_max);
    setBeamParameters(lambda, axis, phi_i);
}

const IAxis* SpecularSimulation::getAlphaAxis() const
{
    return &m_instrument.getDetector()->getAxis(0);
}

std::vector<complex_t> SpecularSimulation::getData(size_t i_layer, DataGetter fn_ptr) const
{
    validityCheck(i_layer);
    std::vector<complex_t> result;
    const size_t data_size = m_sim_elements.size();
    result.resize(data_size);
    for (size_t i = 0; i < data_size; ++i) {
        const SpecularData* specular_data = m_sim_elements[i].specularData();
        result[i] = ((*specular_data)[i_layer].*fn_ptr)();
    }
    return result;
}

std::unique_ptr<OutputData<double>>
SpecularSimulation::getDataByAbsValue(size_t i_layer, DataGetter fn_ptr) const
{
    std::unique_ptr<OutputData<double>> output_ptr = std::make_unique<OutputData<double>>();
    output_ptr->addAxis(*getAlphaAxis());
    const std::vector<complex_t> complex_data = getData(i_layer, fn_ptr);
    OutputData<double>& output = *output_ptr.get();
    for (size_t i = 0; i < complex_data.size(); ++i)
        output[i] = std::norm(complex_data[i]);
    return output_ptr;
}

std::unique_ptr<IComputation>
SpecularSimulation::generateSingleThreadedComputation(SimIter start, SimIter end)
{
    return std::make_unique<SpecularComputation>(*sample(), m_options, m_progress, start, end);
}

OutputData<double>* SpecularSimulation::getDetectorIntensity(AxesUnits units_type) const
{
    const size_t i_layer = 0; // detector intensity is proportional to reflectivity from the zeroth layer
    validityCheck(i_layer);
    return m_instrument.createDetectorIntensity(m_sim_elements, units_type).release();
}

Histogram1D* SpecularSimulation::reflectivity() const
{
    return new Histogram1D(*getDataByAbsValue(0, &ILayerRTCoefficients::getScalarR));
}

Histogram1D* SpecularSimulation::transmissivity() const
{
    const MultiLayer* current_sample = sample();
    const size_t i_layer = current_sample ? static_cast<size_t>(current_sample->numberOfLayers() - 1) : 0;
    return new Histogram1D(*getDataByAbsValue(i_layer, &ILayerRTCoefficients::getScalarT));
}

std::vector<complex_t> SpecularSimulation::getScalarR(size_t i_layer) const
{
    return getData(i_layer, &ILayerRTCoefficients::getScalarR);
}

std::vector<complex_t> SpecularSimulation::getScalarT(size_t i_layer) const
{
    return getData(i_layer, &ILayerRTCoefficients::getScalarT);
}

std::vector<complex_t> SpecularSimulation::getScalarKz(size_t i_layer) const
{
    return getData(i_layer, &ILayerRTCoefficients::getScalarKz);
}

void SpecularSimulation::normalize(SimIter begin_it, SimIter end_it) const
{
    double beam_intensity = getBeamIntensity();
    if (beam_intensity==0.0)
        return; // no normalization when beam intensity is zero
    for(auto it=begin_it; it!=end_it; ++it) {
        it->setIntensity(it->getIntensity()*beam_intensity);
    }
}

void SpecularSimulation::validityCheck(size_t i_layer) const
{
    const MultiLayer* current_sample = sample();
    if (!current_sample)
        throw std::runtime_error(
            "Error in SpecularSimulation::validityCheck: no sample found in the simulation.");
    if (i_layer >= current_sample->numberOfLayers())
        throw std::runtime_error("Error in SpecularSimulation::validityCheck: passed layer number "
                                 "exceeds the number of layers in the sample.");

    const size_t data_size = m_sim_elements.size();
    if (data_size != getAlphaAxis()->size())
        throw std::runtime_error("Error in SpecularSimulation::validityCheck: length of simulation "
                                 "element vector is not equal to the length of detector axis");

    for (size_t i = 0; i < data_size; ++i) {
        const SpecularData* specular_data = m_sim_elements[i].specularData();
        if (!specular_data || !specular_data->isInited()) {
            std::ostringstream message;
            message << "Error in SpecularSimulation::validityCheck: simulation element " << i << "does not contain specular info";
            throw std::runtime_error(message.str());
        }
    }
}

void SpecularSimulation::initialize()
{
    setName(BornAgain::SpecularSimulationType);
}
