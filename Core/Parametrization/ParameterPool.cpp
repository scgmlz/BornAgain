// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/ParameterPool.cpp
//! @brief     Implements standard mix-in ParameterPool.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ParameterPool.h"
#include "RealLimits.h"
#include "RealParameter.h"
#include <stdexcept>
#include "StringUtils.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>

//! Constructs an empty parameter pool.

ParameterPool::ParameterPool(const std::string& name, const std::function<void()>& onChange)
    : m_name(name)
    , m_onChange(onChange)
{}

ParameterPool::~ParameterPool()
{
    clear();
}

//! Returns a literal clone.

ParameterPool* ParameterPool::clone() const
{
    ParameterPool* new_pool = new ParameterPool(m_name, m_onChange);
    new_pool->m_params = m_params;
    return new_pool;
}

//! Returns a clone with _prefix_ prepended to every parameter key.

ParameterPool* ParameterPool::cloneWithPrefix(const std::string& prefix) const
{
    ParameterPool* new_pool = new ParameterPool(m_name, m_onChange);
    copyToExternalPool( prefix, new_pool );
    return new_pool;
}

//! Clears the parameter map.

void ParameterPool::clear()
{
    for(auto* par: m_params)
        delete par;
    m_params.clear();
}

//! Adds parameter to the pool, and returns reference to the input pointer.

//! Returning the input pointer allows us to concatenate function calls like
//! pool->addParameter( new RealParameter(...) ).setLimits(-1,+1).setFixed().setUnit("nm")

RealParameter& ParameterPool::addParameter(RealParameter* newPar)
{
    for (const auto* par: m_params )
        if( par->getName()==newPar->getName() )
            throw std::runtime_error(
                "Bug in ParameterPool::addParameter(): "
                "Parameter '"+newPar->getName()+"' is already registered");
    m_params.push_back(newPar);
    return *newPar;
}

//! Copies parameters of given pool to _other_ pool, prepeding _prefix_ to the parameter names.

void ParameterPool::copyToExternalPool(const std::string& prefix, ParameterPool* other_pool) const
{
    for (const auto* par: m_params) {
        RealParameter* new_par = par->clone( prefix + par->getName() );
        other_pool->addParameter( new_par );
    }
}

//! Returns parameter with given _name_.

const RealParameter* ParameterPool::getParameter(const std::string& name) const
{
    for (const auto* par: m_params )
        if( par->getName()==name )
            return par;
    throw std::runtime_error(
        "ParameterPool::getParameter() -> Warning. No parameter with name '"+name+"'");
}

//! Returns parameter with given _name_.

RealParameter* ParameterPool::getParameter(const std::string& name)
{
    for (auto* par: m_params )
        if( par->getName()==name )
            return par;
    throw std::runtime_error(
        "ParameterPool::getParameter() -> Warning. No parameter with name '"+name+"'");
}

//! Returns vector of parameters that match the _pattern_ (wildcards '*' allowed).

std::vector<RealParameter*> ParameterPool::getMatchedParameters(const std::string& pattern) const
{
    std::vector<RealParameter*> selected_parameters;
    // loop over all parameters in the pool
    for (auto* par: m_params)
        if( StringUtils::matchesPattern( par->getName(), pattern ) )
            selected_parameters.push_back(par);
    if( selected_parameters.empty() )
        report_find_matched_parameters_error(pattern);
    return selected_parameters;
}

//! Sets parameter value.

void ParameterPool::setParameterValue(const std::string& name, double value)
{
    RealParameter* par = getParameter(name);
    if( par->isNull() )
        throw std::runtime_error(
            "ParameterPool::setParameterValue() -> Error! Unitialized parameter '"+name+"'.");
    try {
        par->setValue(value);
    } catch(std::runtime_error) {
        report_set_value_error(name, value);
    }
}

//! Sets parameter value.

int ParameterPool::setMatchedParametersValue(const std::string& pattern, double value)
{
    int npars(0);
    for (auto* par: m_params) {
        if( StringUtils::matchesPattern( par->getName(), pattern ) ) {
            try {
                par->setValue(value);
                npars++;
            } catch(std::runtime_error) {
                report_set_value_error(par->getName(), value);
            }
        }
    }
    if(npars == 0)
        report_find_matched_parameters_error(pattern);
    return npars;
}

std::vector<std::string> ParameterPool::getParameterNames() const
{
    std::vector<std::string> result;
    for (const auto* par: m_params)
        result.push_back(par->getName());
    return result;
}

void ParameterPool::print(std::ostream& ostr) const
{
    const size_t number_of_pars_in_line(12);
    if( m_params.size() ) {
        if(m_params.size() < number_of_pars_in_line) { // print in one line
            ostr << "POOL_" << m_params.size();
            ostr << "(";
            for (const auto* par: m_params)
                ostr << "'" << par->getName() << "'" << ":" << par->getValue() << " " ;
            ostr << ")";
        } else { // print in several lines
            for (const auto* par: m_params)
                ostr << "'" << par->getName() << "'" << ":" << par->getValue() << "\n";
        }
    } else {
        ostr << "POOL_0";
    }
}

//! reports error while finding parameters matching given name.
void ParameterPool::report_find_matched_parameters_error(const std::string& pattern) const
{
    std::ostringstream ostr;
    ostr << "ParameterPool::find_matched_parameters_error() -> Error! ";
    ostr << "No parameters matching  pattern '" << pattern
       << "' have been found. Existing keys are:" << std::endl;
    for (const auto* par: m_params)
        ostr << "'" << par->getName() << "'\n";
    throw std::runtime_error(ostr.str());
}

//! Reports error while setting parname to given value.
void ParameterPool::report_set_value_error(const std::string& parname, double value) const
{
    std::ostringstream ostr;
    ostr << "ParameterPool::set_value_error() -> Attempt to set value " << value;
    ostr << " for parameter '" << parname << "' failed. Out of bounds?";
    try {
        ostr << " Parameter limits " << getParameter(parname)->getLimits() << ".\n";
    } catch (...) {
        throw std::runtime_error("Bug de luxe in ParameterPool: cannot even report the error");
    }
    throw std::runtime_error(ostr.str());
}
