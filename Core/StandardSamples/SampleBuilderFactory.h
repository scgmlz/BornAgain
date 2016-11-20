// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SampleBuilderFactory.h
//! @brief     Defines class SampleBuilderFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SAMPLEBUILDERFACTORY_H
#define SAMPLEBUILDERFACTORY_H

#include "IFactory.h"
#include "IMultiLayerBuilder.h"

class MultiLayer;

//! Factory to create standard pre-defined samples
//! @ingroup standard_samples

class BA_CORE_API_ SampleBuilderFactory : public IFactory<std::string, IMultiLayerBuilder>
{
public:
    SampleBuilderFactory();
    MultiLayer* createSample(const std::string& name);
};

#endif // SAMPLEBUILDERFACTORY_H
