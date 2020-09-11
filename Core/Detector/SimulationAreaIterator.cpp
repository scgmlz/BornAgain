// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/SimulationAreaIterator.cpp
//! @brief     Implements class SimulationAreaIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Detector/SimulationAreaIterator.h"
#include "Core/Detector/IDetector2D.h"
#include "Core/Detector/SimulationArea.h"

SimulationAreaIterator::SimulationAreaIterator(const SimulationArea* area, size_t start_at_index)
    : m_area(area), m_index(start_at_index), m_element_index(0)
{
    if (m_index > m_area->totalSize())
        throw Exceptions::RuntimeErrorException("SimulationAreaIterator::SimulationAreaIterator() "
                                                "-> Error. Invalid initial index");

    if (m_index != m_area->totalSize() && m_area->isMasked(m_index))
        m_index = nextIndex(m_index);
}

size_t SimulationAreaIterator::roiIndex() const
{
    return m_area->roiIndex(m_index);
}

size_t SimulationAreaIterator::detectorIndex() const
{
    return m_area->detectorIndex(m_index);
}

SimulationAreaIterator& SimulationAreaIterator::operator++()
{
    size_t index = nextIndex(m_index);
    if (index != m_index) {
        ++m_element_index;
        m_index = index;
    }
    return *this;
}

SimulationAreaIterator SimulationAreaIterator::operator++(int)
{
    SimulationAreaIterator result(*this);
    this->operator++();
    return result;
}

size_t SimulationAreaIterator::nextIndex(size_t currentIndex)
{
    size_t result = ++currentIndex;
    if (result < m_area->totalSize()) {
        while (m_area->isMasked(result)) {
            ++result;
            if (result == m_area->totalSize())
                break;
        }
    } else {
        return m_area->totalSize();
    }
    return result;
}
