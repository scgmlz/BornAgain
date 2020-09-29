// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ThickAbsorptiveSampleBuilder.h
//! @brief     Defines class to build thick highly-absorptive sample with roughness
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_THICKABSORPTIVESAMPLEBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_THICKABSORPTIVESAMPLEBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"

class ThickAbsorptiveSampleBuilder : public ISampleBuilder
{
public:
    MultiLayer* buildSample() const override;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_THICKABSORPTIVESAMPLEBUILDER_H
