//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/MultiLayerWithNCRoughnessBuilder.h
//! @brief     Defines class MultiLayerWithNCRoughnessBuilder.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_MULTILAYERWITHNCROUGHNESSBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_MULTILAYERWITHNCROUGHNESSBUILDER_H

#include "Sample/StandardSamples/MultiLayerWithRoughnessBuilder.h"

//! Builds sample: layers with correlated roughness.
//! @ingroup standard_samples

class MultiLayerWithNCRoughnessBuilder : public MultiLayerWithRoughnessBuilder {
public:
    MultiLayer* buildSample() const override;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_MULTILAYERWITHNCROUGHNESSBUILDER_H
#endif // USER_API
