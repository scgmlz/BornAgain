//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/SlicedCylindersBuilder.h
//! @brief     Defines classes for testing slicing machinery.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_SLICEDCYLINDERSBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_SLICEDCYLINDERSBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: cylinders on a silicon substrate
//! @ingroup standard_samples

class SlicedCylindersBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Provides exactly the same sample as SlicedCylindersBuilder, but with
//! sld-based materials. Assumed wavelength is 1.54 Angstrom.
//! @ingroup standard_samples

class SLDSlicedCylindersBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Provides exactly the same sample as SLDSlicedCylindersBuilder, but with
//! cylinders represented as homogeneous layers. SLD-based materials used.
//! Assumed wavelength is 1.54 Angstrom.
//! @ingroup standard_samples

class AveragedSlicedCylindersBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_SLICEDCYLINDERSBUILDER_H
#endif // USER_API
