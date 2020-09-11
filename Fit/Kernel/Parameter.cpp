// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/Parameter.cpp
//! @brief     Implements class Parameter.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Kernel/Parameter.h"
#include <cmath>

namespace
{
const double default_step = 0.01;
const double step_factor = 0.01;

double step_for_value(double value)
{
    return value == 0.0 ? default_step : std::abs(value) * step_factor;
}
} // namespace

using namespace Fit;

Parameter::Parameter() : m_start_value(0.0), m_value(0.0), m_step(0.0), m_error(0.0) {}

Parameter::Parameter(const std::string& name, double value, const AttLimits& limits, double step)
    : m_name(name), m_start_value(value), m_value(value), m_step(step), m_error(0.0),
      m_limits(limits)
{
    if (step <= 0.0)
        m_step = step_for_value(value);
}

std::string Parameter::name() const
{
    return m_name;
}

double Parameter::startValue() const
{
    return m_start_value;
}

AttLimits Parameter::limits() const
{
    return m_limits;
}

double Parameter::value() const
{
    return m_value;
}

void Parameter::setValue(double value)
{
    m_value = value;
}

double Parameter::step() const
{
    return m_step;
}

double Parameter::error() const
{
    return m_error;
}

void Parameter::setError(double value)
{
    m_error = value;
}
