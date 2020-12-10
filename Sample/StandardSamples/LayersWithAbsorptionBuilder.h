//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/LayersWithAbsorptionBuilder.h
//! @brief     Defines class LayersWithAbsorptionBuilder.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"
#include <memory>

class IFormFactor;

//! The LayersWithAbsorptionBuilder class generates a multilayer with 3 layers with
//! absorption (refractive index has imaginary part).
//! @ingroup standard_samples

//! The middle layer is populated with particles.
//! Requires IComponentService which generates form factors, used for bulk form factors testing.

class LayersWithAbsorptionBuilder : public ISampleBuilder {
public:
    LayersWithAbsorptionBuilder();
    ~LayersWithAbsorptionBuilder();
    virtual MultiLayer* buildSample() const;

    MultiLayer* createSampleByIndex(size_t index);
    size_t size();

private:
    std::unique_ptr<IFormFactor> m_ff;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBUILDER_H
#endif // USER_API
