// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/MinimizerResult.cpp
//! @brief     Implements class MinimizerResult.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Kernel/MinimizerResult.h"
#include "Fit/RootAdapter/MinimizerResultUtils.h"
#include "Fit/Tools/MinimizerUtils.h"
#include <sstream>

using namespace Fit;

MinimizerResult::MinimizerResult()
    : m_min_value(0.0), m_number_of_calls(0), m_number_of_gradient_calls(0), m_duration(0.0)
{
}

void MinimizerResult::setParameters(const Parameters& parameters)
{
    m_parameters = parameters;
}

Parameters MinimizerResult::parameters() const
{
    return m_parameters;
}

void MinimizerResult::setMinValue(double value)
{
    m_min_value = value;
}

//! Minimum value of objective function found by minimizer.

double MinimizerResult::minValue() const
{
    return m_min_value;
}

//! Returns multi-line string representing minimization results.

std::string MinimizerResult::toString() const
{
    std::ostringstream result;
    if (m_minimizer_report.empty()) {
        result << "Don't know anything about external minimizer. "
               << "Use minimizer API to get result of minimization.\n";

    } else {
        result << MinimizerUtils::sectionString();
        result << "Run time (sec)           : " << m_duration << "\n";
        result << "Objective function calls : " << m_number_of_calls << "\n";
        result << "Gradient calls           : " << m_number_of_gradient_calls << "\n";
        result << m_minimizer_report;
        result << MinimizerResultUtils::reportParameters(m_parameters);
    }

    return result.str();
}

void MinimizerResult::setReport(const std::string& value)
{
    m_minimizer_report = value;
}

void MinimizerResult::setDuration(double value)
{
    m_duration = value;
}

void MinimizerResult::setNumberOfCalls(int value)
{
    m_number_of_calls = value;
}

void MinimizerResult::setNumberOfGradientCalls(int value)
{
    m_number_of_gradient_calls = value;
}
