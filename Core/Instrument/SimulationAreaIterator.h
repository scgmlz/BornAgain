// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Instrument/SimulationAreaIterator.h
//! @brief     Defines class SimulationAreaIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONAREAITERATOR_H
#define SIMULATIONAREAITERATOR_H

#include "WinDllMacros.h"
#include <cstdlib>
class SimulationArea;

//! An iterator for SimulationArea.
//! @ingroup simulation

class BA_CORE_API_ SimulationAreaIterator
{
public:
    explicit SimulationAreaIterator(const SimulationArea *area, size_t start_at_index);

    size_t index() const { return m_index; }
    size_t elementIndex() const { return m_element_index;}
    int roiIndex() const;
    int detectorIndex() const;

    bool operator==(const SimulationAreaIterator &other) const;
    bool operator!=(const SimulationAreaIterator &other) const;

    //! prefix increment
    SimulationAreaIterator& operator++();

    //! postfix increment
    SimulationAreaIterator operator++(int);

private:
    size_t nextIndex(size_t currentIndex);
    const SimulationArea *m_area;
    size_t m_index;  //!< global index in detector plane defined by its axes
    size_t m_element_index; //!< sequential number for SimulationElementVector
};

inline bool SimulationAreaIterator::operator==(const SimulationAreaIterator &other) const
{
  return m_area == other.m_area && m_index == other.m_index;
}

inline bool SimulationAreaIterator::operator!=(const SimulationAreaIterator &right) const
{
    return !(*this == right);
}

#endif // SIMULATIONAREAITERATOR_H
