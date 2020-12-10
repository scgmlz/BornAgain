//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/MinimizerResult.cpp
//! @brief     Implements class MinimizerResult.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Fit/Minimizer/MinimizerResult.h"
#include "Fit/Tools/MinimizerUtils.h"
#include <boost/format.hpp>
#include <sstream>

namespace {

std::string reportParameters(const mumufit::Parameters& parameters) {
    std::ostringstream result;

    result << mumufit::utils::sectionString("FitParameters");

    result << "Name                       StartValue  Limits                        FitValue"
           << "     Error" << std::endl;

    for (const auto& par : parameters) {
        result << boost::format("%-26.26s %-8.3e   %-28s  %-8.3e    %8.3e \n") % par.name()
                      % par.startValue() % par.limits().toString() % par.value() % par.error();
    }

    mumufit::Parameters::corr_matrix_t matrix = parameters.correlationMatrix();
    if (!matrix.empty()) {
        result << mumufit::utils::sectionString("Correlations");
        for (size_t i = 0; i < matrix.size(); ++i) {
            result << boost::format("#%-2d       ") % i;
            for (size_t j = 0; j < matrix[i].size(); ++j)
                result << boost::format("%_7.4f    ") % matrix[i][j];
            result << std::endl;
        }
    }

    return result.str();
}

} // namespace

//  ************************************************************************************************
//  class MinimizerResult
//  ************************************************************************************************

using namespace mumufit;

MinimizerResult::MinimizerResult()
    : m_min_value(0.0), m_number_of_calls(0), m_number_of_gradient_calls(0), m_duration(0.0) {}

void MinimizerResult::setParameters(const Parameters& parameters) {
    m_parameters = parameters;
}

Parameters MinimizerResult::parameters() const {
    return m_parameters;
}

void MinimizerResult::setMinValue(double value) {
    m_min_value = value;
}

//! Minimum value of objective function found by minimizer.

double MinimizerResult::minValue() const {
    return m_min_value;
}

//! Returns multi-line string representing minimization results.

std::string MinimizerResult::toString() const {
    std::ostringstream result;
    if (m_minimizer_report.empty()) {
        result << "Don't know anything about external minimizer. "
               << "Use minimizer API to get result of minimization.\n";

    } else {
        result << mumufit::utils::sectionString();
        result << "Run time (sec)           : " << m_duration << "\n";
        result << "Objective function calls : " << m_number_of_calls << "\n";
        result << "Gradient calls           : " << m_number_of_gradient_calls << "\n";
        result << m_minimizer_report;
        result << reportParameters(m_parameters);
    }

    return result.str();
}

void MinimizerResult::setReport(const std::string& value) {
    m_minimizer_report = value;
}

void MinimizerResult::setDuration(double value) {
    m_duration = value;
}

void MinimizerResult::setNumberOfCalls(int value) {
    m_number_of_calls = value;
}

void MinimizerResult::setNumberOfGradientCalls(int value) {
    m_number_of_gradient_calls = value;
}
