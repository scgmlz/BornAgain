// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputation.cpp
//! @brief     Implements interface IComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IComputation.h"
#include "ProgressHandler.h"
#include "SimulationElement.h"

IComputation::IComputation(ProgressHandler& progress,
                           const std::vector<SimulationElement>::iterator& start,
                           const std::vector<SimulationElement>::iterator& end)
    : m_progress(&progress)
    , m_begin_it(start)
    , m_end_it(end)
{}

IComputation::~IComputation() {}
