// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/TwoLayerRoughnessBuilder.h
//! @brief     Defines class TwoLayerRoughnessBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_TWOLAYERROUGHNESSBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_TWOLAYERROUGHNESSBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: two layers with rough interface.
//! @ingroup standard_samples

class TwoLayerRoughnessBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_TWOLAYERROUGHNESSBUILDER_H
