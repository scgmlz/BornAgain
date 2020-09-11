// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Kernel/Parameters.cpp
//! @brief     Defines class Parameters.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Fit/Kernel/Parameters.h"
#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace Fit;

void Parameters::add(const Parameter& par)
{
    if (exists(par.name()))
        throw std::runtime_error("Parameters::add() -> Error. Parameter with the name '"
                                 + par.name() + "' already exists.");

    m_parameters.push_back(par);
}

Parameters::const_iterator Parameters::begin() const
{
    return m_parameters.begin();
}

Parameters::const_iterator Parameters::end() const
{
    return m_parameters.end();
}

Parameters::iterator Parameters::begin()
{
    return m_parameters.begin();
}

Parameters::iterator Parameters::end()
{
    return m_parameters.end();
}

size_t Parameters::size() const
{
    return m_parameters.size();
}

std::vector<double> Parameters::values() const
{
    std::vector<double> result;
    for (const auto& par : m_parameters)
        result.push_back(par.value());
    return result;
}

void Parameters::setValues(const std::vector<double>& values)
{
    check_array_size(values);

    size_t index = 0;
    for (auto& par : m_parameters) {
        if (std::isnan(values[index]))
            throw std::runtime_error("Parameters::setValues() -> Error."
                                     " Attempt to set nan '"
                                     + par.name() + "'.");
        if (std::isinf(values[index]))
            throw std::runtime_error("Parameters::setValues() -> Error. Attempt to set inf '"
                                     + par.name() + "'.");
        par.setValue(values[index]);
        ++index;
    }
}

std::vector<double> Parameters::errors() const
{
    std::vector<double> result;
    for (const auto& par : m_parameters)
        result.push_back(par.error());
    return result;
}

void Parameters::setErrors(const std::vector<double>& errors)
{
    check_array_size(errors);
    size_t index = 0;
    for (auto& par : m_parameters)
        par.setError(errors[index++]);
}

const Parameter& Parameters::operator[](const std::string& name) const
{
    for (const auto& par : m_parameters)
        if (par.name() == name)
            return par;

    std::ostringstream ostr;
    ostr << "Parameters::operator[] -> Error. No parameter with name '" << name << "'. ";
    ostr << "Existing names:\n";
    for (const auto& par : m_parameters)
        ostr << par.name() << "\n";
    throw std::runtime_error(ostr.str());
}

const Parameter& Parameters::operator[](size_t index) const
{
    return m_parameters[check_index(index)];
}

Parameters::corr_matrix_t Parameters::correlationMatrix() const
{
    return m_corr_matrix;
}

void Parameters::setCorrelationMatrix(const Parameters::corr_matrix_t& matrix)
{
    if (matrix.size() != size())
        throw std::runtime_error("Parameters::setCorrelationMatrix() -> Error. Wrong "
                                 "dimension of correlation matrix.");
    m_corr_matrix = matrix;
}

//! Returns number of free parameters.

size_t Parameters::freeParameterCount() const
{
    size_t result(0);
    for (const auto& par : m_parameters)
        if (!par.limits().isFixed())
            result++;
    return result;
}

bool Parameters::exists(const std::string& name) const
{
    for (const auto& par : m_parameters)
        if (par.name() == name)
            return true;
    return false;
}

void Parameters::check_array_size(const std::vector<double>& values) const
{
    if (values.size() != m_parameters.size()) {
        std::ostringstream ostr;
        ostr << "Parameters::check_array_size() -> Error. Size of input array " << values.size()
             << " doesn't mach number of fit parameters " << m_parameters.size() << "."
             << std::endl;
        throw std::runtime_error(ostr.str());
    }
}

size_t Parameters::check_index(size_t index) const
{
    if (index >= m_parameters.size())
        throw std::runtime_error("Parameters::check_index() -> Index out of bounds");
    return index;
}
