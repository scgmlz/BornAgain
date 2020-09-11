// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SampleBuilderNode.h
//! @brief     Defines class SampleBuilderNode.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_MULTILAYER_SAMPLEBUILDERNODE_H
#define BORNAGAIN_CORE_MULTILAYER_SAMPLEBUILDERNODE_H

#include "Core/Parametrization/INode.h"
#include <memory>

class IMultiLayerBuilder;

//! Enfolds MultiLayerBuilder to have it in INode tree.
//! @ingroup simulation_internal

class BA_CORE_API_ SampleBuilderNode : public INode
{
public:
    using builder_t = std::shared_ptr<IMultiLayerBuilder>;

    SampleBuilderNode();
    SampleBuilderNode(const SampleBuilderNode& other);
    SampleBuilderNode& operator=(const SampleBuilderNode& other);

    void setSampleBuilder(builder_t sample_builder);

    void reset();

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    std::unique_ptr<MultiLayer> createMultiLayer();

    explicit operator bool() const;

    builder_t builder() const;

private:
    void borrow_builder_parameters();

    builder_t m_sample_builder;
};

#endif // BORNAGAIN_CORE_MULTILAYER_SAMPLEBUILDERNODE_H
