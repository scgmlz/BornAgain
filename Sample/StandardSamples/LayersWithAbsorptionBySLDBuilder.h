//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/LayersWithAbsorptionBySLDBuilder.h
//! @brief     Defines class LayersWithAbsorptionBySLDBuilder.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBYSLDBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBYSLDBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! The LayersWithAbsorptionBySLDBuilder class generates a multilayer with 3 layers with
//! absorption (refractive index has imaginary part). //! The middle layer is populated with
//! particles. MaterialBySLD is used to generate maaterials
//! @ingroup standard_samples

class LayersWithAbsorptionBySLDBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_LAYERSWITHABSORPTIONBYSLDBUILDER_H
#endif // USER_API
