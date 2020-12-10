//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/SampleBuilderFactory.h
//! @brief     Defines class SampleBuilderFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_SAMPLEBUILDERFACTORY_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_SAMPLEBUILDERFACTORY_H

#include "Base/Utils/IFactory.h"
#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

class MultiLayer;

//! Factory to create standard pre-defined samples
//! @ingroup standard_samples

class SampleBuilderFactory : public IFactory<std::string, ISampleBuilder> {
public:
    SampleBuilderFactory();
    MultiLayer* createSampleByName(const std::string& name);
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_SAMPLEBUILDERFACTORY_H
