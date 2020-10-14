// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SampleBuilderEngine/SampleBuilderNode.h
//! @brief     Defines class SampleBuilderNode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SAMPLEBUILDERENGINE_SAMPLEBUILDERNODE_H
#define BORNAGAIN_CORE_SAMPLEBUILDERENGINE_SAMPLEBUILDERNODE_H

#include "Param/Node/INode.h"
#include <memory>

class ISampleBuilder;

//! Wraps an ISampleBuilder, and puts it in an INode tree.
//! Used by SampleProvider.
//! @ingroup simulation_internal

class SampleBuilderNode : public INode
{
public:
    SampleBuilderNode();
    SampleBuilderNode(const SampleBuilderNode& other);
    SampleBuilderNode& operator=(const SampleBuilderNode& other);

    void setSBN(const std::shared_ptr<ISampleBuilder>& sample_builder);

    void reset();

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    std::unique_ptr<MultiLayer> createMultiLayer();

    explicit operator bool() const;

    std::shared_ptr<ISampleBuilder> builder() const;

private:
    void borrow_builder_parameters();

    std::shared_ptr<ISampleBuilder> m_sample_builder;
};

#endif // BORNAGAIN_CORE_SAMPLEBUILDERENGINE_SAMPLEBUILDERNODE_H
