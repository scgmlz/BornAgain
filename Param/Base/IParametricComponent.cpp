//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Param/Base/IParametricComponent.cpp
//! @brief     Implements interface IParametricComponent.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Param/Base/IParametricComponent.h"
#include "Param/Base/ParameterPool.h"
#include "Param/Base/RealParameter.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

IParametricComponent::IParametricComponent(const std::string& name)
    : m_name{name}, m_pool{new ParameterPool} {}

IParametricComponent::IParametricComponent(const IParametricComponent& other)
    : IParametricComponent(other.getName()) {
    if (!other.parameterPool()->empty())
        throw std::runtime_error("BUG: not prepared to copy parameters of " + getName());
}

IParametricComponent::~IParametricComponent() = default;

ParameterPool* IParametricComponent::createParameterTree() const {
    auto* result = new ParameterPool;
    m_pool->copyToExternalPool("/" + getName() + "/", result);
    return result;
}

std::string IParametricComponent::parametersToString() const {
    std::ostringstream result;
    std::unique_ptr<ParameterPool> P_pool(createParameterTree());
    result << *P_pool << "\n";
    return result.str();
}

RealParameter& IParametricComponent::registerParameter(const std::string& name, double* data) {
    return m_pool->addParameter(
        new RealParameter(name, data, getName(), [&]() -> void { onChange(); }));
}

void IParametricComponent::registerVector(const std::string& base_name, kvector_t* p_vec,
                                          const std::string& units) {
    registerParameter(XComponentName(base_name), &((*p_vec)[0])).setUnit(units);
    registerParameter(YComponentName(base_name), &((*p_vec)[1])).setUnit(units);
    registerParameter(ZComponentName(base_name), &((*p_vec)[2])).setUnit(units);
}

void IParametricComponent::setParameterValue(const std::string& name, double value) {
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

void IParametricComponent::setVectorValue(const std::string& base_name, kvector_t value) {
    setParameterValue(XComponentName(base_name), value.x());
    setParameterValue(YComponentName(base_name), value.y());
    setParameterValue(ZComponentName(base_name), value.z());
}

//! Returns parameter with given 'name'.
RealParameter* IParametricComponent::parameter(const std::string& name) const {
    return m_pool->parameter(name);
}

void IParametricComponent::removeParameter(const std::string& name) {
    m_pool->removeParameter(name);
}

void IParametricComponent::removeVector(const std::string& base_name) {
    removeParameter(XComponentName(base_name));
    removeParameter(YComponentName(base_name));
    removeParameter(ZComponentName(base_name));
}

std::string IParametricComponent::XComponentName(const std::string& base_name) {
    return base_name + "X";
}

std::string IParametricComponent::YComponentName(const std::string& base_name) {
    return base_name + "Y";
}

std::string IParametricComponent::ZComponentName(const std::string& base_name) {
    return base_name + "Z";
}
