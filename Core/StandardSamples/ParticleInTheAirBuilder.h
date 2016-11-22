// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParticleInTheAirBuilder.h
//! @brief     Defines class ParticleInTheAirBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef PARTICLEINTHEAIRBUILDER_H
#define PARTICLEINTHEAIRBUILDER_H

#include "IMultiLayerBuilder.h"

//! The ParticleInTheAirBuilder class generates a multilayer with single air layer
//! populated with particles of certain types.
//! Requires IComponentService which generates form factors, used for bulk form factors testing.
//! @ingroup standard_samples

class BA_CORE_API_ ParticleInTheAirBuilder : public IMultiLayerBuilder
{
public:
    ParticleInTheAirBuilder() {}
    virtual ~ParticleInTheAirBuilder() {}
    virtual MultiLayer* buildSample() const;
};

#endif // PARTICLEINTHEAIRBUILDER_H
