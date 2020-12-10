//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/HomogeneousMultilayerBuilder.h
//! @brief     Defines class HomogeneousMultilayerBuilder.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_HOMOGENEOUSMULTILAYERBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_HOMOGENEOUSMULTILAYERBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"

//! Builds a sample with 10 interchanging homogeneous layers of Ti and Ni on silicone substrate.
//! Ti is 70 angstroms thick, Ni is 30 angstroms thick.
//! No absorption, no roughness, target wavelength is 1.54 angstroms.
//! @ingroup standard_samples

class HomogeneousMultilayerBuilder : public ISampleBuilder {
public:
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_HOMOGENEOUSMULTILAYERBUILDER_H
#endif // USER_API
