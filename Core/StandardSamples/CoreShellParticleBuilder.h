// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/CoreShellParticleBuilder.h
//! @brief     Defines class CoreShellParticleBuilder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_STANDARDSAMPLES_CORESHELLPARTICLEBUILDER_H
#define BORNAGAIN_CORE_STANDARDSAMPLES_CORESHELLPARTICLEBUILDER_H

#include "Core/Multilayer/IMultiLayerBuilder.h"

class ISample;

//! Builds sample: Core Shell Nanoparticles (IsGISAXS example #11).
//! @ingroup standard_samples

class BA_CORE_API_ CoreShellParticleBuilder : public IMultiLayerBuilder
{
public:
    CoreShellParticleBuilder() {}
    MultiLayer* buildSample() const;
};

//! Rotation and translation of core shell box particle in 3 layers system.
//! @ingroup standard_samples

class BA_CORE_API_ CoreShellBoxRotateZandYBuilder : public IMultiLayerBuilder
{
public:
    CoreShellBoxRotateZandYBuilder() {}
    MultiLayer* buildSample() const;
};

#endif // BORNAGAIN_CORE_STANDARDSAMPLES_CORESHELLPARTICLEBUILDER_H
