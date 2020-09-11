// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Intensity/IIntensityFunction.cpp
//! @brief     Implements the classes IntensityFunctionLog, IntensityFunctionSqrt
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Intensity/IIntensityFunction.h"
#include <cmath>
#include <limits>

IIntensityFunction::~IIntensityFunction() = default;

IntensityFunctionLog* IntensityFunctionLog::clone() const
{
    return new IntensityFunctionLog;
}

double IntensityFunctionLog::evaluate(double value) const
{
    return value > 0 ? std::log(value) : std::numeric_limits<double>::lowest();
}

IntensityFunctionSqrt* IntensityFunctionSqrt::clone() const
{
    return new IntensityFunctionSqrt;
}

double IntensityFunctionSqrt::evaluate(double value) const
{
    return value > 0 ? std::sqrt(value) : std::numeric_limits<double>::lowest();
}
