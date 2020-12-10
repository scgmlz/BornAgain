//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/PercusYevickBuilder.h
//! @brief     Defines classes of PercusYevickBuilder family.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_PERCUSYEVICKBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_PERCUSYEVICKBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! @ingroup standard_samples
//! Builds sample: cylinders with hard disk Percus-Yevick interference.

class HardDiskBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_PERCUSYEVICKBUILDER_H
#endif // USER_API
