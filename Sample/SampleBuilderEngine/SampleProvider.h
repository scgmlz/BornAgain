//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/SampleBuilderEngine/SampleProvider.h
//! @brief     Defines class SampleProvider.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_SAMPLEPROVIDER_H
#define BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_SAMPLEPROVIDER_H

#include "Sample/SampleBuilderEngine/SampleBuilderNode.h"

class MultiLayer;

//! Holds either a Sample, or a SampleBuilderNode (which holds an ISampleBuilder).
//! Used in ISimulation, which holds a SampleProvider member.

//! @ingroup simulation_internal

class SampleProvider : public INode {
public:
    SampleProvider();
    SampleProvider(const SampleProvider& other); // TODO ASAP can't we clone?
    SampleProvider& operator=(const SampleProvider& other);
    ~SampleProvider();

    void setSample(const MultiLayer& multilayer);

    void setBuilder(const std::shared_ptr<ISampleBuilder>& sample_builder);

    const MultiLayer* sample() const;

    void updateSample();

    std::vector<const INode*> getChildren() const override;

    void accept(INodeVisitor* visitor) const final { visitor->visit(this); }

    void setParent(const INode* newParent) override;

private:
    std::unique_ptr<MultiLayer> m_multilayer;
    SampleBuilderNode m_sample_builder;
};

#endif // BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_SAMPLEPROVIDER_H
#endif // USER_API
