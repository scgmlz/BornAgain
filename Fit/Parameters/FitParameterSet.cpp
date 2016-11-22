// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Parameters/FitParameterSet.cpp
//! @brief     Implements class FitParameterSet.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitParameterSet.h"
#include "FitParameter.h"
#include "MinimizerUtils.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

FitParameterSet::~FitParameterSet()
{
    clear();
}

//! Clears all defined parameters.

void FitParameterSet::clear()
{
    for (auto par: m_parameters)
        delete par;
    m_parameters.clear();
}

//! Returns number of parameters.

size_t FitParameterSet::size() const
{
    return m_parameters.size();
}

//! Container iterators.

FitParameterSet::iterator FitParameterSet::begin()
{
    return m_parameters.begin();
}

FitParameterSet::const_iterator FitParameterSet::begin() const
{
    return m_parameters.begin();
}

FitParameterSet::iterator FitParameterSet::end()
{
    return m_parameters.end();
}

FitParameterSet::const_iterator FitParameterSet::end() const
{
    return m_parameters.end();
}

//! Adds fit parameter.

void FitParameterSet::addFitParameter(FitParameter* par)
{
    if(isExistingName(par->name()))
        throw std::runtime_error("FitParameterSet::addFitParameter() -> Error. Parameter with "
                                 "the name '"+par->name()+"' already exist.");

    for (auto fitPar: m_parameters)
        if(fitPar == par)
            throw std::runtime_error("FitParameterSet::addFitParameter() -> Error. Attempt to add "
                                     "same fit parameter twice.");
    m_parameters.push_back(par);
}

//! Returns fit parameter by given name.

const FitParameter* FitParameterSet::fitParameter(const std::string& name) const
{
    for (auto par: m_parameters)
        if (par->name() == name)
            return par;
    throw std::runtime_error("FitParameterSet::getFitParameter() -> "
                             "Error. No parameter with name '"+name+"'");
}

FitParameter* FitParameterSet::fitParameter(const std::string& name)
{
    return const_cast<FitParameter*>(static_cast<const FitParameterSet*>(this)
                                      ->fitParameter(name));
}

//! Indexed access to parameters.

const FitParameter* FitParameterSet::operator[](const std::string& name) const
{
    return fitParameter(name);
}

FitParameter* FitParameterSet::operator[](const std::string& name)
{
    return const_cast<FitParameter*>(static_cast<const FitParameterSet*>(this)
                                      ->operator[](name));
}

const FitParameter* FitParameterSet::operator[](size_t index) const
{
    return m_parameters[check_index(index)];
}

FitParameter* FitParameterSet::operator[](size_t index)
{
    return const_cast<FitParameter*>(static_cast<const FitParameterSet*>(this)
                                      ->operator[](index));
}

//! Returns values of all defined parameters.

std::vector<double> FitParameterSet::values() const
{
    std::vector<double> result;
    for (auto par: m_parameters)
        result.push_back(par->value());
    return result;
}

//! Sets values for all defined parameters.

void FitParameterSet::setValues(const std::vector<double>& pars_values)
{
    check_array_size(pars_values);

    int index = 0;
    for (auto par: m_parameters) {
        if (std::isnan(pars_values[index]))
            throw std::runtime_error("FitParameterSet::setValues() -> Error."
                                     " Attempt to set nan '"+par->name() + std::string("'."));
        if (std::isinf(pars_values[index]))
            throw std::runtime_error("FitParameterSet::setValues() -> Error. Attempt to set inf '"+
                                      par->name()  + std::string("'."));
        par->setValue(pars_values[index]);
        ++index;
    }
}

//! Returns true if parameters already have the given values.

bool FitParameterSet::valuesDifferFrom(const std::vector<double>& pars_values, double tol) const
{
    check_array_size(pars_values);

    for (size_t i=0; i<m_parameters.size(); ++i)
        if (MinimizerUtils::numbersDiffer(m_parameters[i]->value(), pars_values[i], tol))
            return true;
    return false;
}

//! Returns errors of all defined parameters.

std::vector<double> FitParameterSet::errors() const
{
    std::vector<double> result;
    for (auto par: m_parameters)
        result.push_back(par->error());
    return result;
}

//! Sets errors to all parameters.

void FitParameterSet::setErrors(const std::vector<double>& pars_errors)
{
    check_array_size(pars_errors);

    for (size_t i=0; i<m_parameters.size(); ++i)
        m_parameters[i]->setError(pars_errors[i]);
}

//! Returns number of free parameters.

size_t FitParameterSet::freeFitParameterCount() const
{
    size_t result(0);
    for (auto par: m_parameters)
        if (!par->limits().isFixed())
            result++;
    return result;
}

//! Fix all parameters.

void FitParameterSet::fixAll()
{
    for (auto par: m_parameters)
        par->limits().setFixed(true);
}

//! Release all parameters.

void FitParameterSet::releaseAll()
{
    for (auto par: m_parameters)
        par->limits().setFixed(false);
}

//! Set fixed flag for parameters from the list.

void FitParameterSet::setFixed(const std::vector<std::string>& pars, bool is_fixed)
{
    for (auto par: pars)
        fitParameter(par)->limits().setFixed(is_fixed);
}


std::string FitParameterSet::parametersToString() const
{
    std::ostringstream result;
    int npar = 0;
    for (auto par: m_parameters)
        result << "   # "<< npar++ << " " << par->toString() << "\n";
    return result.str();
}

void FitParameterSet::setCorrelationMatrix(const FitParameterSet::corr_matrix_t& matrix)
{
    if(matrix.size() != size())
        throw std::runtime_error("FitParameterSet::setCorrelationMatrix() -> Error. Wrong "
                                 "dimension of correlation matrix.");
    m_corr_matrix = matrix;
}

//! Returns true if parameter with such name exists.

bool FitParameterSet::isExistingName(const std::string& name) const
{
    for (auto par: m_parameters)
        if (par->name() == name)
            return true;
    return false;
}

//! Checks if index corresponds with the number of fit parameters.

size_t FitParameterSet::check_index(size_t index) const
{
    if (index >= m_parameters.size())
        throw std::runtime_error(
            "FitSuiteParameters::check_index() -> Index out of bounds");
    return index;
}

//! Checks if size of input array corresponds to number of fit parameters,
//! throws an exception if not.

void FitParameterSet::check_array_size(const std::vector<double>& values) const
{
    if (values.size() != m_parameters.size()) {
        std::ostringstream ostr;
        ostr << "FitParameterSet::check_array_size() -> Error. Size of inpout array "
             << values.size() << ", doesn't mach number of fit parameters "
             << m_parameters.size() << std::endl;
        throw std::runtime_error(ostr.str());
    }
}
