// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SampleProvider.cpp
//! @brief     Implements class SampleProvider.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Multilayer/SampleProvider.h"
#include "Core/Basics/Assert.h"
#include "Core/Multilayer/MultiLayer.h"

SampleProvider::SampleProvider() {}

SampleProvider::SampleProvider(const SampleProvider& other)
{
    if (other.m_multilayer)
        setSample(*other.m_multilayer);

    if (other.m_sample_builder)
        setSampleBuilder(other.m_sample_builder.builder());
}

SampleProvider& SampleProvider::operator=(const SampleProvider& other)
{
    if (this != &other) {
        SampleProvider tmp(other);
        tmp.swapContent(*this);
    }
    return *this;
}

SampleProvider::~SampleProvider() {}

void SampleProvider::setSample(const MultiLayer& multilayer)
{
    m_multilayer.reset(multilayer.clone());
    m_multilayer->setParent(parent());
    m_sample_builder.reset();
}

void SampleProvider::setSampleBuilder(const std::shared_ptr<IMultiLayerBuilder> sample_builder)
{
    m_sample_builder.setSampleBuilder(sample_builder);
    m_sample_builder.setParent(parent());
    m_multilayer.reset();
}

//! Returns current sample.

const MultiLayer* SampleProvider::sample() const
{
    return m_multilayer.get();
}

//! Generates new sample if sample builder defined.

void SampleProvider::updateSample()
{
    if (m_sample_builder)
        m_multilayer = m_sample_builder.createMultiLayer();

    if (!m_multilayer)
        throw std::runtime_error("SampleProvider::updateSample() -> Error. No sample.");
}

std::vector<const INode*> SampleProvider::getChildren() const
{
    std::vector<const INode*> result;
    if (m_sample_builder) {
        result.push_back(&m_sample_builder);
    } else {
        if (m_multilayer)
            result.push_back(m_multilayer.get());
    }
    return result;
}

void SampleProvider::setParent(const INode* newParent)
{
    INode::setParent(newParent);
    if (m_sample_builder) {
        m_sample_builder.setParent(parent());
    } else {
        if (m_multilayer)
            m_multilayer->setParent(parent());
    }
}

void SampleProvider::swapContent(SampleProvider& other)
{
    std::swap(m_multilayer, other.m_multilayer);
    std::swap(m_sample_builder, other.m_sample_builder);
}
