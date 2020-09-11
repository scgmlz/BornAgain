// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SampleBuilderNode.cpp
//! @brief     Implements class SampleBuilderNode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SampleBuilderNode.h"
#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Core/Multilayer/MultiLayer.h"
#include "Core/Parametrization/ParameterPool.h"
#include <stdexcept>

namespace
{
const std::string& default_name = "SampleBuilderNode";
}

SampleBuilderNode::SampleBuilderNode()
{
    setName(default_name);
}

SampleBuilderNode::SampleBuilderNode(const SampleBuilderNode& other)
    : m_sample_builder(other.m_sample_builder)
{
    setName(other.getName());
}

SampleBuilderNode& SampleBuilderNode::operator=(const SampleBuilderNode& other)
{
    if (this != &other) {
        m_sample_builder = other.m_sample_builder;
        setName(other.getName());
    }
    return *this;
}

//! Sets sample builder and borrows its parameters.

void SampleBuilderNode::setSampleBuilder(builder_t sample_builder)
{
    if (!sample_builder)
        throw std::runtime_error("SampleContainer::setSampleBuilder() -> Error. "
                                 "Attempt to set null sample builder.");

    m_sample_builder = sample_builder;
    setName(m_sample_builder->getName());
    borrow_builder_parameters();
}

//! Resets to initial state by removing builder and its borrowed parameters.

void SampleBuilderNode::reset()
{
    setName(default_name);
    parameterPool()->clear();
    m_sample_builder.reset();
}

//! Creates a multilayer using sample builder.

std::unique_ptr<MultiLayer> SampleBuilderNode::createMultiLayer()
{
    if (!m_sample_builder)
        throw std::runtime_error("SampleBuilderNode::createMultiLayer() -> Error. Absent builder");

    if (m_sample_builder->isPythonBuilder())
        return std::unique_ptr<MultiLayer>(m_sample_builder->buildSample()->clone());
    else
        return std::unique_ptr<MultiLayer>(m_sample_builder->buildSample());
}

//! Returns current sample builder.

SampleBuilderNode::builder_t SampleBuilderNode::builder() const
{
    return m_sample_builder;
}

//! Returns true if sample builder is set.

SampleBuilderNode::operator bool() const
{
    return m_sample_builder.get() != nullptr;
}

//! Fill local parameter pool with parameters from sample builder.

void SampleBuilderNode::borrow_builder_parameters()
{
    parameterPool()->clear();

    if (!m_sample_builder)
        return;

    m_sample_builder->parameterPool()->copyToExternalPool("", parameterPool());
}
