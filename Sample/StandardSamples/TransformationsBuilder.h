//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/TransformationsBuilder.h
//! @brief     Defines classes to build samples with different transformations.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_TRANSFORMATIONSBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_TRANSFORMATIONSBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Rotated box in 3 layers system.
//! @ingroup standard_samples

class TransformBoxBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_TRANSFORMATIONSBUILDER_H
#endif // USER_API
