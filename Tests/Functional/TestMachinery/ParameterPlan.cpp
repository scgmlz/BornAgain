// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/ParameterPlan.cpp
//! @brief     Implements class ParameterPlan
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "ParameterPlan.h"

using namespace Fit;

ParameterPlan::ParameterPlan(const Parameter& param, double expected_value, double tolerance)
    : m_expected_value(expected_value), m_tolerance(tolerance), m_parameter(param)
{
}

Parameter ParameterPlan::fitParameter() const { return m_parameter; }
