// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/SampleBuilderEngine/ISampleBuilder.h
//! @brief     Defines pure virtual base class ISampleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_SAMPLEBUILDERENGINE_ISAMPLEBUILDER_H
#define BORNAGAIN_CORE_SAMPLEBUILDERENGINE_ISAMPLEBUILDER_H

#include "Param/Base/IParameterized.h"

class MultiLayer;

//! Interface to the class capable to build samples to simulate.
//! @ingroup simulation_internal

class ISampleBuilder : public IParameterized
{
public:
    ISampleBuilder();
    virtual ~ISampleBuilder();

    virtual MultiLayer* buildSample() const = 0;

    virtual MultiLayer* createSampleByIndex(size_t) { return buildSample(); }
    virtual size_t size() { return 1; }
};

#endif // BORNAGAIN_CORE_SAMPLEBUILDERENGINE_ISAMPLEBUILDER_H
