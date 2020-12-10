//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/FeNiBilayerBuilder.h
//! @brief     Defines various sample builder classes to
//!            test polarized specular computations
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifdef SWIG
#error no need to expose this header to Swig
#endif

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_FENIBILAYERBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_FENIBILAYERBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

class FeNiBilayerBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

class FeNiBilayerTanhBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

class FeNiBilayerNCBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

class FeNiBilayerSpinFlipBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

class FeNiBilayerSpinFlipTanhBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

class FeNiBilayerSpinFlipNCBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_FENIBILAYERBUILDER_H
#endif // USER_API
