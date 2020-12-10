//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/MagneticLayersBuilder.h
//! @brief    Defines class to build samples with magnetic layers
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_MAGNETICLAYERSBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_MAGNETICLAYERSBUILDER_H

#include "Sample/Multilayer/RoughnessModels.h"
#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: spheres in substrate layer with a zero magnetic field.
//! @ingroup standard_samples

class MagneticSubstrateZeroFieldBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Builds sample: ambient and one magnetized layer on a non-magnetized substrate.
//! @ingroup standard_samples

class SimpleMagneticLayerBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Builds sample: magnetic spheres in a magnetized layer on a non-magnetized substrate.
//! @ingroup standard_samples

class MagneticLayerBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Builds sample: magnetic layer on a magnetic substrate with the fields rotated by 90°
//! @ingroup standard_samples

class SimpleMagneticRotationBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const override;

    MultiLayer* createSampleByIndex(size_t index) override;
    size_t size() override;
};

//! Builds sample: rotated magnetic spheres in substrate layer with a unit magnetic field.
//! @ingroup standard_samples

class MagneticRotationBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_MAGNETICLAYERSBUILDER_H
#endif // USER_API
