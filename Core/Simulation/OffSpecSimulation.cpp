// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Simulation/OffSpecSimulation.cpp
//! @brief     Implements class OffSpecSimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "OffSpecSimulation.h"
#include "BornAgainNamespace.h"
#include "DWBAComputation.h"
#include "Histogram2D.h"
#include "IMultiLayerBuilder.h"
#include "MultiLayer.h"
#include "SimulationElement.h"

OffSpecSimulation::OffSpecSimulation()
    : mp_alpha_i_axis(nullptr)
{
    initialize();
}

OffSpecSimulation::OffSpecSimulation(const MultiLayer& p_sample)
    : Simulation(p_sample)
    , mp_alpha_i_axis(nullptr)
{
    initialize();
}

OffSpecSimulation::OffSpecSimulation(const std::shared_ptr<IMultiLayerBuilder> p_sample_builder)
    : Simulation(p_sample_builder)
    , mp_alpha_i_axis(nullptr)
{
    initialize();
}

void OffSpecSimulation::prepareSimulation()
{
    checkInitialization();
    Simulation::prepareSimulation();
}

size_t OffSpecSimulation::numberOfSimulationElements() const
{
    checkInitialization();
    return getInstrument().getDetector()->numberOfSimulationElements()*mp_alpha_i_axis->size();
}

Histogram2D* OffSpecSimulation::getIntensityData() const
{
    const std::unique_ptr<OutputData<double> > data(getDetectorIntensity());
    return new Histogram2D(*data);
}

void OffSpecSimulation::setBeamParameters(double lambda, const IAxis& alpha_axis, double phi_i)
{
    delete mp_alpha_i_axis;
    mp_alpha_i_axis = alpha_axis.clone();
    if (alpha_axis.size()<1)
        throw Exceptions::ClassInitializationException(
                "OffSpecSimulation::prepareSimulation() "
                "-> Error. Incoming alpha range size < 1.");
    double alpha_start = alpha_axis[0];
    m_instrument.setBeamParameters(lambda, alpha_start, phi_i);
    updateIntensityMap();
}

void OffSpecSimulation::setDetectorParameters(size_t n_x, double x_min, double x_max,
                                              size_t n_y, double y_min, double y_max)
{
    if (auto detector = m_instrument.detector2D())
        detector->setDetectorParameters(n_x, x_min, x_max, n_y, y_min, y_max);
    else
        throw std::runtime_error(
            "Error in OffSpecSimulation::setDetectorParameters: wrong detector type");
    updateIntensityMap();
}

std::unique_ptr<IComputation> OffSpecSimulation::generateSingleThreadedComputation(
        std::vector<SimulationElement>::iterator start,
        std::vector<SimulationElement>::iterator end)
{
    return std::make_unique<DWBAComputation>(*sample(), m_options, m_progress, start, end);
}

OffSpecSimulation::OffSpecSimulation(const OffSpecSimulation& other)
    : Simulation(other)
    , mp_alpha_i_axis(nullptr)
{
    if(other.mp_alpha_i_axis)
        mp_alpha_i_axis = other.mp_alpha_i_axis->clone();
    m_intensity_map.copyFrom(other.m_intensity_map);
    initialize();
}

void OffSpecSimulation::initSimulationElementVector()
{
    m_sim_elements.clear();
    Beam beam = m_instrument.getBeam();
    double wavelength = beam.getWavelength();
    double phi_i = beam.getPhi();
    checkInitialization();

    for (size_t iAlpha = 0; iAlpha < mp_alpha_i_axis->size(); ++iAlpha) {
        // Incoming angle by convention defined as positive:
        double alpha_i = mp_alpha_i_axis->getBin(iAlpha).getMidPoint();
        beam.setCentralK(wavelength, alpha_i, phi_i);
        m_instrument.setBeam(beam);
        std::vector<SimulationElement> sim_elements_alpha_i =
            m_instrument.createSimulationElements();
        m_sim_elements.insert(m_sim_elements.end(), sim_elements_alpha_i.begin(),
                              sim_elements_alpha_i.end());
    }
}

void OffSpecSimulation::transferResultsToIntensityMap()
{
    checkInitialization();
    const IAxis& phi_axis = m_instrument.getDetectorAxis(0);
    size_t phi_f_size = phi_axis.size();
    if (phi_f_size*m_intensity_map.getAllocatedSize()!=m_sim_elements.size())
        throw Exceptions::RuntimeErrorException(
            "OffSpecSimulation::transferResultsToIntensityMap: "
            "intensity map size does not conform to number of calculated intensities");
    for (size_t i=0; i<mp_alpha_i_axis->size(); ++i)
        transferDetectorImage(i);
}

void OffSpecSimulation::updateIntensityMap()
{
    m_intensity_map.clear();
    if (mp_alpha_i_axis)
        m_intensity_map.addAxis(*mp_alpha_i_axis);
    size_t detector_dimension = m_instrument.getDetectorDimension();
    if (detector_dimension==2)
        m_intensity_map.addAxis(m_instrument.getDetectorAxis(1));
    m_intensity_map.setAllTo(0.);
}

void OffSpecSimulation::transferDetectorImage(size_t index)
{
    OutputData<double> detector_image;
    size_t detector_dimension = m_instrument.getDetectorDimension();
    for (size_t dim=0; dim<detector_dimension; ++dim)
        detector_image.addAxis(m_instrument.getDetectorAxis(dim));
    size_t detector_size = detector_image.getAllocatedSize();
    for (size_t i=0; i<detector_size; ++i)
        detector_image[i] = m_sim_elements[index*detector_size + i].getIntensity();
    m_instrument.applyDetectorResolution(&detector_image);
    size_t y_axis_size = m_instrument.getDetectorAxis(1).size();
    for (size_t i=0; i<detector_size; ++i)
        m_intensity_map[index*y_axis_size + i%y_axis_size] += detector_image[i];
}

void OffSpecSimulation::checkInitialization() const
{
    if (!mp_alpha_i_axis || mp_alpha_i_axis->size()<1)
        throw Exceptions::ClassInitializationException(
                "OffSpecSimulation::checkInitialization() "
                "Incoming alpha range not configured.");
    if (m_instrument.getDetectorDimension()!=2)
        throw Exceptions::RuntimeErrorException(
            "OffSpecSimulation::checkInitialization: detector is not two-dimensional");
    const IAxis& phi_axis = m_instrument.getDetectorAxis(0);
    if (phi_axis.getName()!=BornAgain::PHI_AXIS_NAME)
        throw Exceptions::RuntimeErrorException(
            "OffSpecSimulation::checkInitialization: phi-axis is not correct");
    const IAxis& alpha_axis = m_instrument.getDetectorAxis(1);
    if (alpha_axis.getName()!=BornAgain::ALPHA_AXIS_NAME)
        throw Exceptions::RuntimeErrorException(
            "OffSpecSimulation::checkInitialization: alpha-axis is not correct");
}

void OffSpecSimulation::initialize()
{
    setName(BornAgain::OffSpecSimulationType);
}
