//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/RotatedPyramidsBuilder.h
//! @brief     Defines class RotatedPyramidsBuilder.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_ROTATEDPYRAMIDSBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_ROTATEDPYRAMIDSBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: Pyramids, rotated pyramids on top of substrate (IsGISAXS example #9)
//! @ingroup standard_samples

class RotatedPyramidsBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_ROTATEDPYRAMIDSBUILDER_H
#endif // USER_API
