// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/SampleTreeIterator.cpp
//! @brief     Implements class SampleTreeIterator.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "SampleTreeIterator.h"


IteratorState::IteratorState(const ISample* single_element) : m_position(0)
{
    m_samples.push_back(single_element);
}

IteratorState::IteratorState(std::vector<const ISample*> samples)
    : m_samples(samples), m_position(0)
{
}
