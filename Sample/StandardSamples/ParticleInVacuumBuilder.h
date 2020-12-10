//  ************************************************************************************************
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Sample/StandardSamples/ParticleInVacuumBuilder.h
//! @brief     Defines class ParticleInVacuumBuilder.
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
#ifndef BORNAGAIN_SAMPLE_STANDARDSAMPLES_PARTICLEINVACUUMBUILDER_H
#define BORNAGAIN_SAMPLE_STANDARDSAMPLES_PARTICLEINVACUUMBUILDER_H

#include "Sample/SampleBuilderEngine/ISampleBuilder.h"
#include <memory>

class IFormFactor;

//! The ParticleInVacuumBuilder class generates a multilayer with single vacuum layer
//! populated with particles of certain types.
//! Requires IComponentService which generates form factors, used for bulk form factors testing.
//! @ingroup standard_samples

class ParticleInVacuumBuilder : public ISampleBuilder {
public:
    ParticleInVacuumBuilder();
    virtual MultiLayer* buildSample() const;

    MultiLayer* createSampleByIndex(size_t index);
    size_t size();

protected:
    std::unique_ptr<IFormFactor> m_ff;
};

#endif // BORNAGAIN_SAMPLE_STANDARDSAMPLES_PARTICLEINVACUUMBUILDER_H
#endif // USER_API
