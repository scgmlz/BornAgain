// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/IDetector.cpp
//! @brief     Implements common detector interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ConvolutionDetectorResolution.h"
#include "IDetector.h"
#include "IDetectorResolution.h"
#include "RegionOfInterest.h"

IDetector::IDetector()
{
    registerChild(&m_detection_properties);
}

IDetector::IDetector(const IDetector& other)
    : ICloneable()
    , m_axes(other.m_axes)
    , m_detection_properties(other.m_detection_properties)
{
    if(other.mP_detector_resolution)
        setDetectorResolution(*other.mP_detector_resolution);
    setName(other.getName());
    registerChild(&m_detection_properties);
}

IDetector::~IDetector() = default;

void IDetector::addAxis(const IAxis& axis)
{
    m_axes.push_back(axis.clone());
}

const IAxis& IDetector::getAxis(size_t index) const
{
    if (index < dimension())
        return *m_axes[index];
    throw std::runtime_error("Error in IDetector::getAxis: not so many axes in this detector.");
}

size_t IDetector::axisBinIndex(size_t index, size_t selected_axis) const
{
    const size_t dim = dimension();
    size_t remainder(index);
    size_t i_axis = dim;
    for (size_t i = 0; i < dim; ++i) {
        --i_axis;
        if (selected_axis == i_axis)
            return remainder % m_axes[i_axis]->size();
        remainder /= m_axes[i_axis]->size();
    }
    throw std::runtime_error("IDetector::getAxisBinIndex() -> "
                             "Error! No axis with given number");
}

std::unique_ptr<IAxis> IDetector::translateAxisToUnits(size_t axis_index, const Beam &beam,
                                                  AxesUnits units) const
{
    double amin(0), amax(0);
    calculateAxisRange(axis_index, beam, units, amin, amax);

    std::unique_ptr<IAxis> result(new FixedBinAxis(axisName(axis_index),
                                                   getAxis(axis_index).size(), amin, amax));

    if (regionOfInterest())
        return regionOfInterest()->clipAxisToRoi(axis_index, *result);

    return result;
}

std::unique_ptr<IAxis> IDetector::createAxis(size_t index, size_t n_bins, double min, double max) const
{
    if (max <= min)
        throw Exceptions::LogicErrorException(
            "IDetector::createAxis() -> Error! max <= min");
    if (n_bins == 0)
        throw Exceptions::LogicErrorException(
            "IDetector::createAxis() -> Error! Number n_bins can't be zero.");
    return std::make_unique<FixedBinAxis>(axisName(index), n_bins, min, max);
}

size_t IDetector::totalSize() const
{
    const size_t dim = dimension();
    if (dim == 0)
        return 0;
    size_t result = 1;
    for (size_t i_axis = 0; i_axis < dim; ++i_axis) {
        result *= m_axes[i_axis]->size();
    }
    return result;
}

void IDetector::setAnalyzerProperties(const kvector_t direction, double efficiency,
                                        double total_transmission)
{
    m_detection_properties.setAnalyzerProperties(direction, efficiency, total_transmission);
}

void IDetector::setDetectorResolution(const IDetectorResolution& p_detector_resolution)
{
    mP_detector_resolution.reset(p_detector_resolution.clone());
    registerChild(mP_detector_resolution.get());
}

// TODO: pass dimension-independent argument to this function
void IDetector::setResolutionFunction(const IResolutionFunction2D& resFunc)
{
    ConvolutionDetectorResolution convFunc(resFunc);
    setDetectorResolution(convFunc);
}

void IDetector::applyDetectorResolution(OutputData<double> *p_intensity_map) const
{
    if (!p_intensity_map)
        throw std::runtime_error("IDetector::applyDetectorResolution() -> "
                                   "Error! Null pointer to intensity map");
    if (mP_detector_resolution)
        mP_detector_resolution->applyDetectorResolution(p_intensity_map);
}

void IDetector::removeDetectorResolution()
{
    mP_detector_resolution.reset();
}

const IDetectorResolution* IDetector::detectorResolution() const
{
    return mP_detector_resolution.get();
}

void IDetector::initOutputData(OutputData<double> &data) const {
  data.clear();
  for (size_t i = 0; i < dimension(); ++i)
      data.addAxis(getAxis(i));
  data.setAllTo(0.);
}

void IDetector::checkAxesUnits(AxesUnits units) const
{
    if(units == AxesUnits::DEFAULT)
        return;

    auto validUnits = validAxesUnits();
    if(std::find(validUnits.begin(), validUnits.end(), units) == validUnits.end()) {
        std::ostringstream message;
        message << "IDetector::createDetectorMap() -> Error. Unknown axes unit " << static_cast<int>(units) << "\n";
        message << "Available units for this detector type \n";
        for(size_t i=0; i<validUnits.size(); ++i)
        for(auto unit : validUnits)
            message << static_cast<int>(unit) << " ";
        message << "\n";
        throw std::runtime_error(message.str());
    }
}

void IDetector::calculateAxisRange(size_t axis_index, const Beam&, AxesUnits units,
                                   double& amin, double& amax) const
{
    if (units == AxesUnits::DEFAULT) {
        amin = getAxis(axis_index).getMin();
        amax = getAxis(axis_index).getMax();
    } else if (units == AxesUnits::NBINS) {
        amin = 0.0;
        amax = static_cast<double>(getAxis(axis_index).size());
    } else {
        throw std::runtime_error("IDetector::calculateAxisRange() -> Error. "
                                 "Unknown units "
                                 + std::to_string(static_cast<int>(units)));
    }
}

std::unique_ptr<OutputData<double>> IDetector::createDetectorMap(const Beam& beam,
                                                                 AxesUnits units) const
{
    checkAxesUnits(units);
    const size_t dim = dimension();
    if (dim == 0)
        throw std::runtime_error(
            "Error in IDetector::createDetectorMap: dimensions of the detector are undefined");

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    for (size_t i = 0; i < dim; ++i)
        result->addAxis(*translateAxisToUnits(i, beam, units));
    result->setAllTo(0.);
    return result;
}

size_t IDetector::numberOfSimulationElements() const
{
    size_t result(0);
    if (this->dimension() != 0) {
        SimulationArea area(this);
        for (SimulationArea::iterator it = area.begin(); it != area.end(); ++it)
            ++result;
    }
    return result;
}

std::vector<const INode*> IDetector::getChildren() const
{
    return std::vector<const INode*>() << &m_detection_properties << mP_detector_resolution;
}
