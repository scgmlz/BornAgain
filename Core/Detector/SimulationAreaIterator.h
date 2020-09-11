// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Detector/SimulationAreaIterator.h
//! @brief     Defines class SimulationAreaIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_DETECTOR_SIMULATIONAREAITERATOR_H
#define BORNAGAIN_CORE_DETECTOR_SIMULATIONAREAITERATOR_H

#include "Wrap/WinDllMacros.h"
#include <cstdlib>
class SimulationArea;

//! An iterator for SimulationArea.
//! @ingroup detector

class BA_CORE_API_ SimulationAreaIterator
{
public:
    explicit SimulationAreaIterator(const SimulationArea* area, size_t start_at_index);

    size_t index() const { return m_index; }
    size_t elementIndex() const { return m_element_index; }
    size_t roiIndex() const;
    size_t detectorIndex() const;

    bool operator==(const SimulationAreaIterator& other) const;
    bool operator!=(const SimulationAreaIterator& other) const;

    //! prefix increment
    SimulationAreaIterator& operator++();

    //! postfix increment
    SimulationAreaIterator operator++(int);

private:
    size_t nextIndex(size_t currentIndex);
    const SimulationArea* m_area;
    size_t m_index;         //!< global index in detector plane defined by its axes
    size_t m_element_index; //!< sequential number for SimulationElementVector
};

inline bool SimulationAreaIterator::operator==(const SimulationAreaIterator& other) const
{
    return m_area == other.m_area && m_index == other.m_index;
}

inline bool SimulationAreaIterator::operator!=(const SimulationAreaIterator& right) const
{
    return !(*this == right);
}

#endif // BORNAGAIN_CORE_DETECTOR_SIMULATIONAREAITERATOR_H
