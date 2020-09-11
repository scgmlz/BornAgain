// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/IDetector.cpp
//! @brief     Implements common detector interface.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/IDetector.h"
#include "Core/Detector/ConvolutionDetectorResolution.h"
#include "Core/Detector/DetectorMask.h"
#include "Core/Detector/IDetectorResolution.h"
#include "Core/Detector/RegionOfInterest.h"
#include "Core/Detector/SimulationArea.h"
#include "Core/Intensity/OutputData.h"
#include "Core/SimulationElement/SimulationElement.h"

IDetector::IDetector()
{
    registerChild(&m_detection_properties);
}

IDetector::IDetector(const IDetector& other)
    : m_axes(other.m_axes), m_detection_properties(other.m_detection_properties)
{
    if (other.mP_detector_resolution)
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

std::unique_ptr<IAxis> IDetector::createAxis(size_t index, size_t n_bins, double min,
                                             double max) const
{
    if (max <= min)
        throw Exceptions::LogicErrorException("IDetector::createAxis() -> Error! max <= min");
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

void IDetector::applyDetectorResolution(OutputData<double>* p_intensity_map) const
{
    if (!p_intensity_map)
        throw std::runtime_error("IDetector::applyDetectorResolution() -> "
                                 "Error! Null pointer to intensity map");
    if (mP_detector_resolution) {
        mP_detector_resolution->applyDetectorResolution(p_intensity_map);
        if (detectorMask() && detectorMask()->hasMasks()) {
            // sets amplitude in masked areas to zero
            std::unique_ptr<OutputData<double>> buff(new OutputData<double>());
            buff->copyShapeFrom(*p_intensity_map);

            iterate([&](const_iterator it) {
                (*buff)[it.roiIndex()] = (*p_intensity_map)[it.roiIndex()];
            });
            p_intensity_map->setRawDataVector(buff->getRawDataVector());
        }
    }
}

void IDetector::removeDetectorResolution()
{
    mP_detector_resolution.reset();
}

const IDetectorResolution* IDetector::detectorResolution() const
{
    return mP_detector_resolution.get();
}

OutputData<double>*
IDetector::createDetectorIntensity(const std::vector<SimulationElement>& elements) const
{
    std::unique_ptr<OutputData<double>> detectorMap(createDetectorMap());
    if (!detectorMap)
        throw Exceptions::RuntimeErrorException("Instrument::createDetectorIntensity:"
                                                "can't create detector map.");

    setDataToDetectorMap(*detectorMap, elements);
    if (mP_detector_resolution)
        applyDetectorResolution(detectorMap.get());

    return detectorMap.release();
}

std::unique_ptr<OutputData<double>> IDetector::createDetectorMap() const
{
    const size_t dim = dimension();
    if (dim == 0)
        throw std::runtime_error(
            "Error in IDetector::createDetectorMap: dimensions of the detector are undefined");

    std::unique_ptr<OutputData<double>> result(new OutputData<double>);
    for (size_t i = 0; i < dim; ++i)
        if (auto roi = regionOfInterest())
            result->addAxis(*roi->clipAxisToRoi(i, getAxis(i)));
        else
            result->addAxis(getAxis(i));

    return result;
}

void IDetector::setDataToDetectorMap(OutputData<double>& detectorMap,
                                     const std::vector<SimulationElement>& elements) const
{
    if (elements.empty())
        return;
    iterate([&](const_iterator it) {
        detectorMap[it.roiIndex()] = elements[it.elementIndex()].getIntensity();
    });
}

size_t IDetector::numberOfSimulationElements() const
{
    size_t result(0);
    iterate([&result](const_iterator) { ++result; });
    return result;
}

std::vector<const INode*> IDetector::getChildren() const
{
    return std::vector<const INode*>() << &m_detection_properties << mP_detector_resolution;
}

void IDetector::iterate(std::function<void(IDetector::const_iterator)> func, bool visit_masks) const
{
    if (this->dimension() == 0)
        return;

    if (visit_masks) {
        SimulationRoiArea area(this);
        for (SimulationRoiArea::iterator it = area.begin(); it != area.end(); ++it)
            func(it);
    } else {
        SimulationArea area(this);
        for (SimulationArea::iterator it = area.begin(); it != area.end(); ++it)
            func(it);
    }
}
