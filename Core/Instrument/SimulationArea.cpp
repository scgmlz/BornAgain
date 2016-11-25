// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SimulationArea.cpp
//! @brief     Implements class SimulationArea.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SimulationArea.h"
#include "BornAgainNamespace.h"
#include "Exceptions.h"
#include "IDetector2D.h"
#include "IntensityDataFunctions.h"
#include "Rectangle.h"
#include "RegionOfInterest.h"
#include <sstream>

SimulationArea::SimulationArea(const IDetector2D* detector) : m_detector(detector), m_max_index(0)
{
    if (detector == nullptr)
        throw Exceptions::RuntimeErrorException("SimulationArea::SimulationArea -> Error. "
                                                "Detector nullptr.");

    if (m_detector->getDimension() != 2)
        throw Exceptions::RuntimeErrorException(
            "SimulationArea::SimulationArea: detector is not two-dimensional");

    if (m_detector->regionOfInterest())
        m_max_index = m_detector->regionOfInterest()->roiSize();
    else
        m_max_index = m_detector->getTotalSize();
}

SimulationAreaIterator SimulationArea::begin() { return SimulationAreaIterator(this, 0); }

SimulationAreaIterator SimulationArea::end() { return SimulationAreaIterator(this, totalSize()); }

bool SimulationArea::isMasked(size_t index) const
{
    if (index >= totalSize()) {
        std::ostringstream message;
        message << "SimulationArea::isActive() -> Error. Index " << index << " is out of range, "
                << "totalSize=" << totalSize();
        throw Exceptions::RuntimeErrorException(message.str());
    }

    return m_detector->getDetectorMask()->isMasked(detectorIndex(index));
}

size_t SimulationArea::roiIndex(size_t index) const { return index; }

size_t SimulationArea::detectorIndex(size_t index) const
{
    if (!m_detector->regionOfInterest())
        return index;

    return m_detector->regionOfInterest()->detectorIndex(index);
}

// --------------------------------------------------------------------------------------

SimulationRoiArea::SimulationRoiArea(const IDetector2D* detector) : SimulationArea(detector) {}

bool SimulationRoiArea::isMasked(size_t) const { return false; }
