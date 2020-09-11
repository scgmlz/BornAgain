// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SampleBuilderFactory.h
//! @brief     Defines class SampleBuilderFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_SAMPLEBUILDERFACTORY_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_SAMPLEBUILDERFACTORY_H

#include "Core/Multilayer/IMultiLayerBuilder.h"
#include "Fit/TestEngine/IFactory.h"

class MultiLayer;

//! Factory to create standard pre-defined samples
//! @ingroup standard_samples

class BA_CORE_API_ SampleBuilderFactory : public IFactory<std::string, IMultiLayerBuilder>
{
public:
    SampleBuilderFactory();
    MultiLayer* createSample(const std::string& name);
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_SAMPLEBUILDERFACTORY_H
