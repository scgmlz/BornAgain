// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/IMinimizer.cpp
//! @brief     Implements class IMinimizer.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IMinimizer.h"

double IMinimizer::minValue() const
{
    throw std::runtime_error("IMinimizer::minValue() -> Not implemented.");
}

void IMinimizer::propagateResults(FitParameterSet&)
{
    throw std::runtime_error("IMinimizer::propagateResults() -> Not implemented.");
}

void IMinimizer::setOptions(const std::string&)
{
    throw std::runtime_error("IMinimizer::setOptions() -> Not implemented.");
}
