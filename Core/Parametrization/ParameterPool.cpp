// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterPool.cpp
//! @brief     Implements standard mix-in ParameterPool.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Parametrization/ParameterPool.h"
#include "Core/Basics/Assert.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Parametrization/RealParameter.h"
#include "Fit/Tools/RealLimits.h"
#include "Fit/Tools/StringUtils.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

//! Constructs an empty parameter pool.

ParameterPool::ParameterPool() {}

ParameterPool::~ParameterPool()
{
    clear();
}

//! Returns a literal clone.

ParameterPool* ParameterPool::clone() const
{
    auto result = new ParameterPool();
    for (auto par : m_params)
        result->addParameter(par->clone());
    return result;
}

//! Clears the parameter map.

void ParameterPool::clear()
{
    for (auto* par : m_params)
        delete par;
    m_params.clear();
}

//! Adds parameter to the pool, and returns reference to the input pointer.

//! Returning the input pointer allows us to concatenate function calls like
//! pool->addParameter( new RealParameter(...) ).setLimits(-1,+1).setFixed().setUnit("nm")

RealParameter& ParameterPool::addParameter(RealParameter* newPar)
{
    for (const auto* par : m_params)
        if (par->getName() == newPar->getName())
            throw Exceptions::RuntimeErrorException("ParameterPool::addParameter() -> Error. "
                                                    "Parameter '"
                                                    + newPar->getName()
                                                    + "' is already registered");
    m_params.push_back(newPar);
    return *newPar;
}

//! Copies parameters of given pool to _other_ pool, prepeding _prefix_ to the parameter names.

void ParameterPool::copyToExternalPool(const std::string& prefix, ParameterPool* other_pool) const
{
    for (const auto* par : m_params) {
        RealParameter* new_par = par->clone(prefix + par->getName());
        other_pool->addParameter(new_par);
    }
}

//! Returns parameter with given _name_.

const RealParameter* ParameterPool::parameter(const std::string& name) const
{
    for (const auto* par : m_params)
        if (par->getName() == name)
            return par;

    return nullptr;
}

//! Returns parameter with given _name_.

RealParameter* ParameterPool::parameter(const std::string& name)
{
    return const_cast<RealParameter*>(static_cast<const ParameterPool*>(this)->parameter(name));
}

//! Returns nonempty vector of parameters that match the _pattern_ ('*' allowed), or throws.

std::vector<RealParameter*> ParameterPool::getMatchedParameters(const std::string& pattern) const
{
    std::vector<RealParameter*> result;
    // loop over all parameters in the pool
    for (auto* par : m_params)
        if (StringUtils::matchesPattern(par->getName(), pattern))
            result.push_back(par);
    if (result.empty())
        report_find_matched_parameters_error(pattern);
    return result;
}

//! Returns the one parameter that matches the _pattern_ (wildcards '*' allowed), or throws.

RealParameter* ParameterPool::getUniqueMatch(const std::string& pattern) const
{
    std::vector<RealParameter*> matches = getMatchedParameters(pattern);
    if (matches.empty())
        throw Exceptions::RuntimeErrorException(
            "ParameterPool::getUniqueMatch: there is no match for '" + pattern + "'");
    if (matches.size() != 1)
        throw Exceptions::RuntimeErrorException("ParameterPool::getUniqueMatch: pattern '" + pattern
                                                + "' is not unique");
    return matches[0];
}

//! Sets parameter value.

void ParameterPool::setParameterValue(const std::string& name, double value)
{
    if (RealParameter* par = parameter(name)) {
        try {
            par->setValue(value);
        } catch (const std::runtime_error& e) {
            report_set_value_error(name, value, e.what());
        }
    } else {
        std::ostringstream message;
        message << "ParameterPool::getParameter() -> Warning. No parameter with name '" + name
                       + "'\n"
                << "Available parameters:" << *this;
        throw Exceptions::RuntimeErrorException(message.str());
    }
}

//! Sets value of the nonzero parameters that match _pattern_ ('*' allowed), or throws.

int ParameterPool::setMatchedParametersValue(const std::string& pattern, double value)
{
    int npars = 0;
    for (RealParameter* par : getMatchedParameters(pattern)) {
        try {
            par->setValue(value);
            npars++;
        } catch (const std::runtime_error& e) {
            report_set_value_error(par->getName(), value, e.what());
        }
    }
    if (npars == 0)
        report_find_matched_parameters_error(pattern);
    return npars;
}

//! Sets value of the one parameter that matches _pattern_ ('*' allowed), or throws.

void ParameterPool::setUniqueMatchValue(const std::string& pattern, double value)
{
    if (setMatchedParametersValue(pattern, value) != 1)
        throw Exceptions::RuntimeErrorException("ParameterPool::setUniqueMatchValue: pattern '"
                                                + pattern + "' is not unique");
}

std::vector<std::string> ParameterPool::parameterNames() const
{
    std::vector<std::string> result;
    for (const auto* par : m_params)
        result.push_back(par->getName());
    return result;
}

//! Removes parameter with given name from the pool.

void ParameterPool::removeParameter(const std::string& name)
{
    if (RealParameter* par = parameter(name)) {
        m_params.erase(std::remove(m_params.begin(), m_params.end(), par), m_params.end());
        delete par;
    }
}

const RealParameter* ParameterPool::operator[](size_t index) const
{
    return m_params[check_index(index)];
}

RealParameter* ParameterPool::operator[](size_t index)
{
    return const_cast<RealParameter*>(static_cast<const ParameterPool*>(this)->operator[](index));
}

void ParameterPool::print(std::ostream& ostr) const
{
    for (const auto* par : m_params)
        ostr << "'" << par->getName() << "'"
             << ":" << par->value() << "\n";
}

//! reports error while finding parameters matching given name.
void ParameterPool::report_find_matched_parameters_error(const std::string& pattern) const
{
    std::ostringstream ostr;
    ostr << "ParameterPool::find_matched_parameters_error() -> Error! ";
    ostr << "No parameters matching  pattern '" << pattern
         << "' have been found. Existing keys are:" << std::endl;
    for (const auto* par : m_params)
        ostr << "'" << par->getName() << "'\n";
    throw Exceptions::RuntimeErrorException(ostr.str());
}

//! Reports error while setting parname to given value.
void ParameterPool::report_set_value_error(const std::string& parname, double value,
                                           std::string message) const
{
    std::ostringstream ostr;
    ostr << "ParameterPool::set_value_error() -> Attempt to set value " << value;
    ostr << " for parameter '" << parname << "' failed.";
    ostr << " Parameter limits: '" << parameter(parname)->limits() << "'.\n";
    ostr << "Original exception message: " << message << std::endl;
    throw Exceptions::RuntimeErrorException(ostr.str());
}

size_t ParameterPool::check_index(size_t index) const
{
    if (index >= m_params.size())
        throw std::runtime_error("ParameterPool::check_index() -> Error. Index out of bounds");
    return index;
}
