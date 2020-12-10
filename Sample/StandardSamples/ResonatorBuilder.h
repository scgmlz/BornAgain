//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/ResonatorBuilder.h
//! @brief     Defines ResonatorBuilder class.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_RESONATORBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_RESONATORBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds sample: multilayer with Ti/Pt layers sequence.
//! @ingroup standard_samples

class ResonatorBuilder : public ISampleBuilder {
public:
    ResonatorBuilder();
    MultiLayer* buildSample() const;

private:
    double m_l_ti; // titanium layer thickness
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_RESONATORBUILDER_H
#endif // USER_API
