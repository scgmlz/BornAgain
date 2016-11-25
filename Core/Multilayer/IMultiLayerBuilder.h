// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/IMultiLayerBuilder.h
//! @brief     Defines pure virtual base class IMultiLayerBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IMULTILAYERBUILDER_H
#define IMULTILAYERBUILDER_H

#include "IParameterized.h"

class MultiLayer;
class IFormFactor;
class IFTDistribution2D;

//! Interface to the class capable to build samples to simulate.
//! @ingroup simulation_internal

class BA_CORE_API_ IMultiLayerBuilder : public IParameterized
{
public:
    IMultiLayerBuilder() : IParameterized("SampleBuilder"), m_subtest_item(0) {}
    virtual ~IMultiLayerBuilder() {}

    virtual MultiLayer* buildSample() const = 0;

    void set_subtest(const IParameterized* subtest_item) { m_subtest_item = subtest_item; }
    const IParameterized* m_subtest_item;

    const IFormFactor* getFormFactor() const;
    const IFTDistribution2D* getFTDistribution2D() const;

    // this method is extended in the Python wrappers (needed to solve ownership issues with
    // the created sample in buildSample()
    static bool isPythonBuilder() { return false; }
};

#endif // IMULTILAYERBUILDER_H
