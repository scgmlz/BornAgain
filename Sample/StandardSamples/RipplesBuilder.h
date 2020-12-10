//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/RipplesBuilder.h
//! @brief     Defines classes to build various ripples.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_RIPPLESBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_RIPPLESBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: cosine ripple within the 1D-paracrystal model.
//! @ingroup standard_samples

class CosineRippleBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

//! Builds sample: triangular ripple within the 1D-paracrystal model (from PRB 85, 235415, 2012).
//! @ingroup standard_samples

class TriangularRippleBuilder : public ISampleBuilder {
public:
    TriangularRippleBuilder();
    MultiLayer* buildSample() const;

private:
    double m_d;
};

class AsymRippleBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_RIPPLESBUILDER_H
#endif // USER_API
