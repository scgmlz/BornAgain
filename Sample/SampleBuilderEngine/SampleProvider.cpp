//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/SampleBuilderEngine/SampleProvider.cpp
//! @brief     Implements class SampleProvider.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "Sample/SampleBuilderEngine/SampleProvider.h"
#include "Sample/Multilayer/MultiLayer.h"

SampleProvider::SampleProvider() = default;

SampleProvider::SampleProvider(const SampleProvider& other) : INode() {
    if (other.m_multilayer)
        setSample(*other.m_multilayer);

    if (other.m_sample_builder)
        setBuilder(other.m_sample_builder.builder());
}

SampleProvider& SampleProvider::operator=(const SampleProvider& other) {
    if (this != &other) {
        SampleProvider tmp(other);
        std::swap(m_multilayer, tmp.m_multilayer);
        std::swap(m_sample_builder, tmp.m_sample_builder);
    }
    return *this;
}

SampleProvider::~SampleProvider() = default;

void SampleProvider::setSample(const MultiLayer& multilayer) {
    m_multilayer.reset(multilayer.clone());
    m_multilayer->setParent(parent());
    m_sample_builder.reset();
}

void SampleProvider::setBuilder(const std::shared_ptr<ISampleBuilder>& sample_builder) {
    m_sample_builder.setSBN(sample_builder);
    m_sample_builder.setParent(parent());
    m_multilayer.reset();
}

//! Returns current sample.

const MultiLayer* SampleProvider::sample() const {
    return m_multilayer.get();
}

//! Generates new sample if sample builder defined.

void SampleProvider::updateSample() {
    if (m_sample_builder)
        m_multilayer = m_sample_builder.createMultiLayer();

    if (!m_multilayer)
        throw std::runtime_error(
            "SampleProvider::updateSample called before sample or builder was set");
}

std::vector<const INode*> SampleProvider::getChildren() const {
    if (m_sample_builder)
        return {&m_sample_builder};
    if (m_multilayer)
        return {m_multilayer.get()};
    return {};
}

void SampleProvider::setParent(const INode* newParent) {
    INode::setParent(newParent);
    if (m_sample_builder)
        m_sample_builder.setParent(parent());
    else if (m_multilayer)
        m_multilayer->setParent(parent());
}
