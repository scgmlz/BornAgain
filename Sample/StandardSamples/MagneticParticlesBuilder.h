//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/MagneticParticlesBuilder.h
//! @brief    Defines class to build magnetic samples
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_MAGNETICPARTICLESBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_MAGNETICPARTICLESBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: cylinders with magnetic material and zero magnetic field.
//! @ingroup standard_samples

class MagneticParticleZeroFieldBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Builds sample: cylinders with magnetic material and non-zero magnetic field.
//! @ingroup standard_samples

class MagneticCylindersBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Builds sample: spheres with magnetization inside substrate.
//! @ingroup standard_samples

class MagneticSpheresBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_MAGNETICPARTICLESBUILDER_H
#endif // USER_API
