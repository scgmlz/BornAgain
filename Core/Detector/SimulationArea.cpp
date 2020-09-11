// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/SimulationArea.cpp
//! @brief     Implements class SimulationArea.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/SimulationArea.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Detector/DetectorMask.h"
#include "Core/Detector/IDetector.h"
#include "Core/Detector/RegionOfInterest.h"
#include "Core/Intensity/IntensityDataFunctions.h"
#include "Core/Mask/Rectangle.h"
#include <sstream>

SimulationArea::SimulationArea(const IDetector* detector) : m_detector(detector), m_max_index(0)
{
    if (m_detector == nullptr)
        throw std::runtime_error("SimulationArea::SimulationArea: null pointer passed"
                                 " as detector");

    if (m_detector->dimension() == 0)
        throw std::runtime_error(
            "SimulationArea::SimulationArea: detector of unspecified dimensionality");

    if (m_detector->regionOfInterest())
        m_max_index = m_detector->regionOfInterest()->roiSize();
    else
        m_max_index = m_detector->totalSize();
}

SimulationAreaIterator SimulationArea::begin()
{
    return SimulationAreaIterator(this, 0);
}

SimulationAreaIterator SimulationArea::end()
{
    return SimulationAreaIterator(this, totalSize());
}

bool SimulationArea::isMasked(size_t index) const
{
    auto masks = m_detector->detectorMask();
    return (masks && masks->hasMasks() && masks->isMasked(detectorIndex(index)));
}

size_t SimulationArea::roiIndex(size_t index) const
{
    return index;
}

size_t SimulationArea::detectorIndex(size_t index) const
{
    if (!m_detector->regionOfInterest())
        return index;

    return m_detector->regionOfInterest()->detectorIndex(index);
}

// --------------------------------------------------------------------------------------

SimulationRoiArea::SimulationRoiArea(const IDetector* detector) : SimulationArea(detector) {}

bool SimulationRoiArea::isMasked(size_t) const
{
    return false;
}
