//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/SampleBuilderEngine/ISampleBuilder.h
//! @brief     Defines interface ISampleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef USER_API
#ifndef BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_ISAMPLEBUILDER_H
#define BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_ISAMPLEBUILDER_H

#include "Param/Base/IParametricComponent.h"

class MultiLayer;

//! Interface to the class capable to build samples to simulate.
//! @ingroup simulation_internal

class ISampleBuilder : public IParametricComponent {
public:
    ISampleBuilder();
    virtual ~ISampleBuilder();

    virtual MultiLayer* buildSample() const = 0;

    virtual MultiLayer* createSampleByIndex(size_t) { return buildSample(); }
    virtual size_t size() { return 1; }
};

#endif // BORNAGAIN_SAMPLE_SAMPLEBUILDERENGINE_ISAMPLEBUILDER_H
#endif // USER_API
