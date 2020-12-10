//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/ThickAbsorptiveSampleBuilder.h
//! @brief     Defines class to build thick highly-absorptive sample with roughness
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_THICKABSORPTIVESAMPLEBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_THICKABSORPTIVESAMPLEBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

class ThickAbsorptiveSampleBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const override;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_THICKABSORPTIVESAMPLEBUILDER_H
#endif // USER_API
