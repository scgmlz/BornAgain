//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/CylindersAndPrismsBuilder.h
//! @brief     Defines class CylindersAndPrismsBuilder.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_CYLINDERSANDPRISMSBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_CYLINDERSANDPRISMSBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: mixture of cylinders and prisms without interference (IsGISAXS example #1).
//! @ingroup standard_samples

class CylindersAndPrismsBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_CYLINDERSANDPRISMSBUILDER_H
#endif // USER_API
