// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/MultiLayerWithNCRoughnessBuilder.h
//! @brief     Defines class MultiLayerWithNCRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_MULTILAYERWITHNCROUGHNESSBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_MULTILAYERWITHNCROUGHNESSBUILDER_H

#include "Core/StandardSamples/MultiLayerWithRoughnessBuilder.h"

//! Builds sample: layers with correlated roughness.
//! @ingroup standard_samples

class MultiLayerWithNCRoughnessBuilder : public MultiLayerWithRoughnessBuilder
{
public:
    MultiLayer* buildSample() const override;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_MULTILAYERWITHNCROUGHNESSBUILDER_H
