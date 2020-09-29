// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/ParticleInVacuumBuilder.h
//! @brief     Defines class ParticleInVacuumBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_PARTICLEINVACUUMBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_PARTICLEINVACUUMBUILDER_H

#include "Core/SampleBuilderEngine/ISampleBuilder.h"
#include <memory>

class IFormFactor;

//! The ParticleInVacuumBuilder class generates a multilayer with single vacuum layer
//! populated with particles of certain types.
//! Requires IComponentService which generates form factors, used for bulk form factors testing.
//! @ingroup standard_samples

class ParticleInVacuumBuilder : public ISampleBuilder
{
public:
    ParticleInVacuumBuilder();
    virtual MultiLayer* buildSample() const;

    MultiLayer* createSampleByIndex(size_t index);
    size_t size();

protected:
    std::unique_ptr<IFormFactor> m_ff;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_PARTICLEINVACUUMBUILDER_H
