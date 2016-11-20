// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IDetector2D.cpp
//! @brief     Implements shared functionality of interface IDetector2D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IDetector2D.h"
#include "Beam.h"
#include "IDetectorResolution.h"
#include "InfinitePlane.h"
#include "Logger.h"
#include "SimulationElement.h"
#include "SimulationArea.h"
#include "BornAgainNamespace.h"
#include "Units.h"
#include "RegionOfInterest.h"
#include "Exceptions.h"

IDetector2D::IDetector2D()
    : m_axes()
{
    init_parameters();
}

IDetector2D::IDetector2D(const IDetector2D &other)
    : IParameterized()
    , m_axes(other.m_axes)
    , m_detector_mask(other.m_detector_mask)
    , m_detection_properties(other.m_detection_properties)
{
    setName(other.getName());
    if (other.mP_detector_resolution)
        mP_detector_resolution.reset(other.mP_detector_resolution->clone());
    if(other.regionOfInterest())
        m_region_of_interest.reset(other.regionOfInterest()->clone());
    init_parameters();
}

IDetector2D::~IDetector2D() {}

const IAxis &IDetector2D::getAxis(size_t index) const
{
    if (isCorrectAxisIndex(index))
        return *m_axes[index];
    throw Exceptions::OutOfBoundsException("Not so many axes in this detector.");
}

void IDetector2D::setDetectorParameters(size_t n_x, double x_min, double x_max,
                                        size_t n_y, double y_min, double y_max)
{
    clear();
    const std::unique_ptr<IAxis> P_axis0(createAxis(0, n_x, x_min, x_max));
    const std::unique_ptr<IAxis> P_axis1(createAxis(1, n_y, y_min, y_max));
    addAxis(*P_axis0);
    addAxis(*P_axis1);
}

void IDetector2D::setDetectorAxes(const IAxis &axis0, const IAxis &axis1)
{
    clear();
    addAxis(axis0);
    addAxis(axis1);
}

void IDetector2D::applyDetectorResolution(OutputData<double> *p_intensity_map) const
{
    if (!p_intensity_map)
        throw Exceptions::NullPointerException("IDetector2D::applyDetectorResolution() -> "
                                   "Error! Null pointer to intensity map");
    if (mP_detector_resolution)
        mP_detector_resolution->applyDetectorResolution(p_intensity_map);
    else
        msglog(Logging::WARNING) << "IDetector2D::applyDetectorResolution() -> "
                                "No detector resolution function found";
}

void IDetector2D::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                        double total_transmission)
{
    m_detection_properties.setAnalyzerProperties(direction, efficiency, total_transmission);
}

std::string IDetector2D::addParametersToExternalPool(
    const std::string& path, ParameterPool *external_pool, int copy_number) const
{
    // add own parameters
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // add parameters of the resolution function
    if (mP_detector_resolution)
        mP_detector_resolution->addParametersToExternalPool(new_path, external_pool, -1);
    return new_path;
}

OutputData<double> *IDetector2D::createDetectorIntensity(
        const std::vector<SimulationElement> &elements,
        const Beam &beam, IDetector2D::EAxesUnits units_type) const
{
    std::unique_ptr<OutputData<double>> detectorMap(createDetectorMap(beam, units_type));
    if(!detectorMap)
        throw Exceptions::RuntimeErrorException("Instrument::getDetectorIntensity() -> Error."
                                    "Can't create detector map.");

    setDataToDetectorMap(*detectorMap.get(), elements);
    applyDetectorResolution(detectorMap.get());

    return detectorMap.release();
}

OutputData<double>* IDetector2D::createDetectorMap(const Beam& beam, EAxesUnits units) const
{
    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    result->addAxis(*constructAxis(BornAgain::X_AXIS_INDEX, beam, units));
    result->addAxis(*constructAxis(BornAgain::Y_AXIS_INDEX, beam, units));
    result->setAllTo(0.);
    return result.release();
}

void IDetector2D::initOutputData(OutputData<double> &data) const {
  data.clear();
  for (size_t i = 0; i < getDimension(); ++i)
      data.addAxis(getAxis(i));
  data.setAllTo(0.);
}

std::vector<IDetector2D::EAxesUnits> IDetector2D::getValidAxesUnits() const
{
    std::vector<EAxesUnits> result = {NBINS};
    return result;
}

const RegionOfInterest *IDetector2D::regionOfInterest() const
{
    return m_region_of_interest.get();
}

void IDetector2D::setRegionOfInterest(double xlow, double ylow, double xup, double yup)
{
    m_region_of_interest.reset(new RegionOfInterest(*this, xlow, ylow, xup, yup));
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::resetRegionOfInterest()
{
    m_region_of_interest.reset();
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::removeMasks()
{
    m_detector_mask.removeMasks();
}

void IDetector2D::addMask(const IShape2D &shape, bool mask_value)
{
    m_detector_mask.addMask(shape, mask_value);
    m_detector_mask.initMaskData(*this);
}

void IDetector2D::maskAll()
{
    if(m_axes.size() != 2) return;
    m_detector_mask.removeMasks();
    addMask(InfinitePlane(), true);
}

const DetectorMask *IDetector2D::getDetectorMask() const
{
    return &m_detector_mask;
}

size_t IDetector2D::numberOfMaskedChannels() const
{
    if (getDetectorMask()) {
        return getDetectorMask()->numberOfMaskedChannels();
    } else {
        return 0;
    }
}

bool IDetector2D::isMasked(size_t index) const
{
    return m_detector_mask.isMasked(index);
}

bool IDetector2D::hasMasks() const
{
    return m_detector_mask.hasMasks();
}

std::vector<SimulationElement> IDetector2D::createSimulationElements(const Beam &beam)
{
    std::vector<SimulationElement> result;

    double wavelength = beam.getWavelength();
    double alpha_i = - beam.getAlpha();  // Defined to be always positive in Beam
    double phi_i = beam.getPhi();
    Eigen::Matrix2cd beam_polarization = beam.getPolarization();
    Eigen::Matrix2cd analyzer_operator = m_detection_properties.analyzerOperator();

    if (!hasMasks())
        m_detector_mask.initMaskData(*this);
    size_t spec_index = getIndexOfSpecular(beam);

    SimulationArea area(this);
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it) {
        SimulationElement sim_element(wavelength, alpha_i, phi_i, std::unique_ptr<IPixelMap>(
                                          createPixelMap(it.detectorIndex())));
        sim_element.setPolarization(beam_polarization);
        sim_element.setAnalyzerOperator(analyzer_operator);
        if (it.index()==spec_index) {
            sim_element.setSpecular(true);
        }
        result.push_back(std::move(sim_element));
    }

    return result;
}

SimulationElement IDetector2D::getSimulationElement(size_t index, const Beam &beam) const
{
    double wavelength = beam.getWavelength();
    double alpha_i = - beam.getAlpha();  // Defined to be always positive in Beam
    double phi_i = beam.getPhi();
    return SimulationElement(wavelength, alpha_i, phi_i,
                             std::unique_ptr<IPixelMap>(createPixelMap(index)));
}

size_t IDetector2D::getAxisBinIndex(size_t index, size_t selected_axis) const
{
    size_t remainder(index);
    for (size_t i=0; i<getDimension(); ++i)
    {
        size_t i_axis = getDimension()-1-i;
        int result = remainder % m_axes[i_axis]->size();
        if(selected_axis == i_axis ) return result;
        remainder /= m_axes[i_axis]->size();
    }
    throw Exceptions::LogicErrorException("IDetector2D::getAxisBinIndex() -> "
                                          "Error! No axis with given number");
}

size_t IDetector2D::numberOfSimulationElements() const
{
    size_t result(0);
    SimulationArea area(this);
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it)
        ++result;
    return result;
}

std::unique_ptr<IAxis> IDetector2D::constructAxis(size_t axis_index, const Beam &beam,
                                                  IDetector2D::EAxesUnits units) const
{
    double amin(0), amax(0);
    calculateAxisRange(axis_index, beam, units, amin, amax);

    std::unique_ptr<IAxis> result(new FixedBinAxis(getAxisName(axis_index),
                                                   getAxis(axis_index).size(), amin, amax));

    if(m_region_of_interest) {
        return m_region_of_interest->clipAxisToRoi(axis_index, *result.get());
    } else {
        return result;
    }
}

void IDetector2D::calculateAxisRange(size_t axis_index, const Beam &beam,
        IDetector2D::EAxesUnits units, double &amin, double &amax) const
{
    amin = 0.0; amax=0.0;

    if(units == DEFAULT) {
        amin = getAxis(axis_index).getMin();
        amax = getAxis(axis_index).getMax();

    }else if(units == NBINS) {
        amin = 0.0;
        amax = static_cast<double>(getAxis(axis_index).size());

    } else if(units == QYQZ && axis_index == BornAgain::X_AXIS_INDEX) {
        const IAxis &aX = getAxis(BornAgain::X_AXIS_INDEX);
        SimulationElement el_left_bottom
            = getSimulationElement(getGlobalIndex(0, 0), beam);
        SimulationElement el_right_bottom
            = getSimulationElement(getGlobalIndex(aX.size()-1, 0), beam);
        amin = el_left_bottom.getQ(0.0, 0.0).y();
        amax = el_right_bottom.getQ(1.0, 0.0).y();

    } else if(units == QYQZ && axis_index == BornAgain::Y_AXIS_INDEX) {
        const IAxis &aX = getAxis(BornAgain::X_AXIS_INDEX);
        const IAxis &aY = getAxis(BornAgain::Y_AXIS_INDEX);
        SimulationElement el_center_bottom
            = getSimulationElement(getGlobalIndex(aX.size()/2, 0), beam);
        SimulationElement el_center_top
            = getSimulationElement(getGlobalIndex(aX.size()/2, aY.size()-1), beam);
        amin = -el_center_bottom.getQ(0.5, 0.0).z();
        amax = -el_center_top.getQ(0.5, 1.0).z();

    } else {
        throw Exceptions::RuntimeErrorException("IDetector2D::calculateAxisRange() -> Error. "
                                                "Unknown units " +std::to_string(units));
    }
}

size_t IDetector2D::getGlobalIndex(size_t x, size_t y) const
{
    if (getDimension()!=2) return getTotalSize();
    return x*m_axes[1]->size()+y;
}

size_t IDetector2D::getTotalSize() const
{
    if (getDimension()==0) return 0;
    size_t result = 1;
    for (size_t i_axis=0; i_axis<getDimension(); ++i_axis)
    {
        result *= m_axes[i_axis]->size();
    }
    return result;
}

void IDetector2D::setDataToDetectorMap(OutputData<double> &detectorMap,
                                       const std::vector<SimulationElement> &elements) const
{
    if(elements.empty())
        return;
    SimulationArea area(this);
    for(SimulationArea::iterator it = area.begin(); it!=area.end(); ++it)
        detectorMap[it.roiIndex()] = elements[it.elementIndex()].getIntensity();

}

void IDetector2D::addAxis(const IAxis& axis)
{
    m_axes.push_back(axis.clone());
}

size_t IDetector2D::getDimension() const
{
    return m_axes.size();
}

void IDetector2D::clear()
{
    m_axes.clear();
}

void IDetector2D::setDetectorResolution(IDetectorResolution* p_detector_resolution)
{
    if (mP_detector_resolution.get()!=p_detector_resolution) {
        mP_detector_resolution.reset(p_detector_resolution);
    }
}

const IDetectorResolution* IDetector2D::getDetectorResolutionFunction() const
{
    return mP_detector_resolution.get();
}

bool IDetector2D::isCorrectAxisIndex(size_t index) const
{
    return index < getDimension();
}
