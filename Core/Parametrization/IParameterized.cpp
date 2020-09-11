// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/IParameterized.cpp
//! @brief     Implements class IParameterized.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Parametrization/IParameterized.h"
#include "Core/Basics/Exceptions.h"
#include "Core/Parametrization/ParameterPool.h"
#include "Core/Parametrization/RealParameter.h"
#include "Fit/Tools/RealLimits.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

IParameterized::IParameterized(const std::string& name) : m_name{name}, m_pool{new ParameterPool} {}

IParameterized::IParameterized(const IParameterized& other) : IParameterized(other.getName())
{
    if (other.parameterPool()->size())
        throw std::runtime_error("BUG: not prepared to copy parameters of " + getName());
}

IParameterized::~IParameterized() = default;

ParameterPool* IParameterized::createParameterTree() const
{
    std::unique_ptr<ParameterPool> result(new ParameterPool);
    m_pool->copyToExternalPool("/" + getName() + "/", result.get());
    return result.release();
}

std::string IParameterized::parametersToString() const
{
    std::ostringstream result;
    std::unique_ptr<ParameterPool> P_pool(createParameterTree());
    result << *P_pool << "\n";
    return result.str();
}

RealParameter& IParameterized::registerParameter(const std::string& name, double* data)
{
    return m_pool->addParameter(
        new RealParameter(name, data, getName(), [&]() -> void { onChange(); }));
}

void IParameterized::registerVector(const std::string& base_name, kvector_t* p_vec,
                                    const std::string& units)
{
    registerParameter(XComponentName(base_name), &((*p_vec)[0])).setUnit(units);
    registerParameter(YComponentName(base_name), &((*p_vec)[1])).setUnit(units);
    registerParameter(ZComponentName(base_name), &((*p_vec)[2])).setUnit(units);
}

void IParameterized::setParameterValue(const std::string& name, double value)
{
    if (name.find('*') == std::string::npos && name.find('/') == std::string::npos) {
        m_pool->setParameterValue(name, value);
    } else {
        std::unique_ptr<ParameterPool> P_pool{createParameterTree()};
        if (name.find('*') != std::string::npos)
            P_pool->setMatchedParametersValue(name, value);
        else
            P_pool->setParameterValue(name, value);
    }
}

void IParameterized::setVectorValue(const std::string& base_name, kvector_t value)
{
    setParameterValue(XComponentName(base_name), value.x());
    setParameterValue(YComponentName(base_name), value.y());
    setParameterValue(ZComponentName(base_name), value.z());
}

//! Returns parameter with given 'name'.
RealParameter* IParameterized::parameter(const std::string& name) const
{
    return m_pool->parameter(name);
}

void IParameterized::removeParameter(const std::string& name)
{
    m_pool->removeParameter(name);
}

void IParameterized::removeVector(const std::string& base_name)
{
    removeParameter(XComponentName(base_name));
    removeParameter(YComponentName(base_name));
    removeParameter(ZComponentName(base_name));
}

std::string IParameterized::XComponentName(const std::string& base_name)
{
    return base_name + "X";
}

std::string IParameterized::YComponentName(const std::string& base_name)
{
    return base_name + "Y";
}

std::string IParameterized::ZComponentName(const std::string& base_name)
{
    return base_name + "Z";
}
